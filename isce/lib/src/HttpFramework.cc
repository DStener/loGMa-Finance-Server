#include "Framework.h"
#include "isce/fields_alloc.hpp"
#include <list>

using namespace isce;

class HTTPWorker {
public:
  // HTTPWorker() = delete;
  HTTPWorker(HTTPWorker const&) = delete;
  HTTPWorker& operator=(HTTPWorker const&) = delete;

  // ~HTTPWorker() = default;

  HTTPWorker(tcp::acceptor& acceptor) : acceptor_(acceptor) {};

  void start() {
    accept();
    // check_deadline();
  } 

private:
  using alloc_t = fields_alloc<char>;
  using request_body_t = http::string_body;

  // The acceptor used to listen for incoming connections.
  tcp::acceptor& acceptor_;

  // The socket for the currently connected client.
  tcp::socket socket_{acceptor_.get_executor()};

  // The buffer for performing reads
  beast::flat_static_buffer<8192> buffer_;

  // The allocator used for the fields in the request and reply.
  alloc_t alloc_{8192};

  // The parser for reading the requests
  boost::optional<http::request_parser<request_body_t, alloc_t>> parser_;

  // The timer putting a time limit on requests.
  net::steady_timer request_deadline_{
    acceptor_.get_executor(), (std::chrono::steady_clock::time_point::max)()};

  
  // The string-based response message.
  boost::optional<http::response<http::string_body, http::basic_fields<alloc_t>>> string_response_;

  // The string-based response serializer.
  boost::optional<http::response_serializer<http::string_body, http::basic_fields<alloc_t>>> string_serializer_;

  // The file-based response message.
  boost::optional<http::response<http::file_body, http::basic_fields<alloc_t>>> file_response_;

  // The file-based response serializer.
  boost::optional<http::response_serializer<http::file_body, http::basic_fields<alloc_t>>> file_serializer_;


  void accept()
    {

        // std::cout << "POLKA" << std::endl;
        // Clean up any previous connection.
        beast::error_code ec;
        socket_.close(ec);
        buffer_.consume(buffer_.size());

        acceptor_.async_accept(
            socket_,
            [this](beast::error_code ec)
            {
                if (ec)
                {
                    accept();
                }
                else
                {
                    // Request must be fully processed within 60 seconds.
                    request_deadline_.expires_after(
                        std::chrono::seconds(60));

                    read_request();
                }
            });
    }

    void read_request()
    {
        // On each read the parser needs to be destroyed and
        // recreated. We store it in a boost::optional to
        // achieve that.
        //
        // Arguments passed to the parser constructor are
        // forwarded to the message object. A single argument
        // is forwarded to the body constructor.
        //
        // We construct the dynamic body with a 1MB limit
        // to prevent vulnerability to buffer attacks.
        //
        parser_.emplace(
            std::piecewise_construct,
            std::make_tuple(),
            std::make_tuple(alloc_));
        
        http::async_read(
            socket_,
            buffer_,
            *parser_,
            [this](beast::error_code ec, std::size_t)
            {
                if (ec)
                    accept();
                else {
                    process_request(parser_->get());
                }
            });
    }
    
    void process_request(const http::request<request_body_t, http::basic_fields<alloc_t>>& req)
    {
      route_t route = app()->get_route(req.target(), req.method());

      Request::ptr_t request(new Request(req, route->vars));
      Response::ptr_t response = route->call(request);

      if (request->is_shutdown()) { return; }


      if(response->is_file_response()) {

        file_response_.emplace(
          std::piecewise_construct,
          std::make_tuple(),
          std::make_tuple(alloc_));

        response->make_file_body(file_response_);
        file_serializer_.emplace(*file_response_);

        http::async_write(
            socket_,
            *file_serializer_,
            [this](beast::error_code ec, std::size_t)
            {
                socket_.shutdown(tcp::socket::shutdown_send, ec);
                file_serializer_.reset();
                file_response_.reset();
                accept();
            });
      } else {

        string_response_.emplace(
          std::piecewise_construct,
          std::make_tuple(),
          std::make_tuple(alloc_));

        response->make_string_body(string_response_);
        string_serializer_.emplace(*string_response_);
        
        http::async_write(
          socket_,
          *string_serializer_,
          [this](beast::error_code ec, std::size_t)
          {
              socket_.shutdown(tcp::socket::shutdown_send, ec);
              string_serializer_.reset();
              string_response_.reset();
              accept();
          });
      }
    }
};


void Framework::server_run() {

  auto const address = net::ip::make_address("0.0.0.0");
  auto const port = static_cast<unsigned short>(5555);


  net::io_context ioc{1};
  // tcp::acceptor acceptor{ioc, {Framework::address(), Framework::port()}};
  tcp::acceptor acceptor{ioc, {address, port}};

  std::list<HTTPWorker> workers;
  for (int i = 0; i < Framework::workers(); ++i)
  {
      workers.emplace_back(acceptor);
      workers.back().start();
  }

  for (;;) ioc.poll();
}

route_t Framework::get_route(uri_t&& uri, http::verb&& method) {
  auto it = std::find_if(_routes.begin(), _routes.end(), [&](route_t route){
    return route->is_match(uri, method);
  });
  if (it == _routes.end()) { return _default_request; }

  return *it;
}