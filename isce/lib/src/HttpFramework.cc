#include "Framework.h"

using namespace isce;


void Framework::server_run() {
  net::io_context ioc;

  auto const address = net::ip::make_address("0.0.0.0");
  auto const port = static_cast<unsigned short>(5555);

  net::co_spawn(
    ioc,
    Framework::server_listen(net::ip::tcp::endpoint{ address, port }),
    [](std::exception_ptr e) {
      if (e) {
        try { std::rethrow_exception(e); }
        catch (std::exception const& e) { std::cerr << "Error: " << e.what() << std::endl; }
      }
    });
  ioc.run();
}

route_t Framework::get_route(uri_t&& uri, http::verb&& method) {
  auto it = std::find_if(_routes.begin(), _routes.end(), [&](route_t route){
    return route->is_match(uri, method);
  });
  if (it == _routes.end()) { return _bad_request; }

  return *it;
}


net::awaitable<void> Framework::server_listen(net::ip::tcp::endpoint endpoint) {

  auto executor = co_await net::this_coro::executor;
  auto acceptor = net::ip::tcp::acceptor{ executor, endpoint };

  for (;;)
  {
    net::co_spawn(
      executor,
      Framework::server_do_session(beast::tcp_stream{ co_await acceptor.async_accept() }),
      [](std::exception_ptr e) {
        if (e) {
          try { std::rethrow_exception(e); }
          catch (std::exception const& e) { std::cerr << "Error in session: " << e.what() << "\n"; }
        }
      });
  }
}


net::awaitable<void> Framework::server_do_session(beast::tcp_stream stream)
{
  // This buffer is required to persist across reads
  beast::flat_buffer buffer;

  for (;;) {
    // Set the timeout.
    stream.expires_after(std::chrono::seconds(30));

    // Read a request
    Request::boost_t boost_request;
    co_await http::async_read(stream, buffer, boost_request);
    //const bool keep_alive = boost_request.keep_alive();
    const bool keep_alive = false;
    
    route_t route = get_route(boost_request.target(), boost_request.method());

    ////////////////
    /*for (const auto& var : route->vars) {
      std::cout << "------------------------------------" << std::endl;
    }*/

    ////////////////


    Request::ptr_t request(new Request(std::move(boost_request), route->vars));
    Response::ptr_t response = route->call(request);

    if (request->is_shutdown()) { break; }

    http::message_generator message = response->make(keep_alive);
    co_await beast::async_write(stream, std::move(message));

    if (!keep_alive){ break; }
  }
    
  // Send a TCP shutdown
  stream.socket().shutdown(net::ip::tcp::socket::shutdown_send);
}