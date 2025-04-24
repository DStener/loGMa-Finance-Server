#ifndef ISCE_HTTP_FRAMEWORK_H
#define ISCE_HTTP_FRAMEWORK_H

#include <isce/Configure.h>

#include <boost/asio/awaitable.hpp>
#include <boost/asio/co_spawn.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/config.hpp>
#include <boost/function.hpp>

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <vector>
#include <functional>

namespace beast	=	boost::beast;
namespace http	=	beast::http;
namespace net		=	boost::asio;
  

using request_t = http::request<http::string_body>;
using response_t = http::response<http::string_body>;

typedef std::function<void (response_t&&)> callback_t;
typedef std::function<void (const request_t&, callback_t&&)> func_t;


using route_t = std::tuple<func_t, std::string_view, http::verb>;

namespace isce {
class HttpFramework {
	public:
		static void run() {
      net::io_context ioc;

      auto const address = net::ip::make_address("0.0.0.0");
      auto const port = static_cast<unsigned short>(5555);

      net::co_spawn(
        ioc,
        HttpFramework::do_listen(net::ip::tcp::endpoint{ address, port }),
        [](std::exception_ptr e)  {
          if (e) {
            try { std::rethrow_exception(e); }
            catch (std::exception const& e) { std::cerr << "Error: " << e.what() << std::endl;}
          }
        });
      ioc.run();
		}

    static void registerMethod(
        func_t &&func, 
        std::string_view target,
        http::verb &&method) {

      route_t route = std::make_tuple(
          std::move(func),
          target,
          std::move(method));

      routes.push_back(std::move(route));
    }

	private:
    inline static std::vector<route_t> routes = {};

    static std::optional<func_t> getRouteFunc(
        std::string_view target,
        http::verb &&method) {

      auto route_it = std::find_if(routes.begin(), routes.end(), [&](const route_t& route) {
                                     return std::get<1>(route) == target &&
                                            std::get<2>(route) == method;
                                   });

      if (route_it == routes.end()) { return {}; }

      return std::get<0>(*route_it);
    }


    // Accepts incoming connections and launches the sessions
    static net::awaitable<void> do_listen(net::ip::tcp::endpoint endpoint)
    {
      auto executor = co_await net::this_coro::executor;
      auto acceptor = net::ip::tcp::acceptor{ executor, endpoint };

      for (;;)
      {
        net::co_spawn(
          executor,
          HttpFramework::do_session(beast::tcp_stream{ co_await acceptor.async_accept() }),
          [](std::exception_ptr e) {
            if (e) {
              try { std::rethrow_exception(e); }
              catch (std::exception const& e) { std::cerr << "Error in session: " << e.what() << "\n"; }
            }
          });
      }
    }

    // Handles an HTTP server connection
    static net::awaitable<void> do_session(beast::tcp_stream stream)
    {
      // This buffer is required to persist across reads
      beast::flat_buffer buffer;

      for (;;) {
        // Set the timeout.
        stream.expires_after(std::chrono::seconds(30));

        // Read a request
        http::request<http::string_body> req;
        co_await http::async_read(stream, buffer, req);

        // Get route function
        auto func = getRouteFunc(req.target(), req.method());
        if (!func.has_value()) { break; }

        std::optional<http::message_generator> message;

        // Callback lambda-function
        callback_t callback = [&](response_t&& resp) {

          // Set MIME value, if is not set;
          if (resp.find(http::field::content_type) == resp.end()) {
            resp.set(http::field::content_type, "text/html");
          }

          resp.keep_alive(req.keep_alive());
          resp.prepare_payload();

          message.emplace(http::message_generator(std::move(resp)));
        };

        // Call function
        func.value()(req, std::move(callback));
        if (!message.has_value()) { break; }

        // Determine if we should close the connection
        bool keep_alive = message.value().keep_alive();

        // Send the response
        co_await beast::async_write(stream, std::move(message.value()));

        if (!keep_alive)
        {
          // This means we should close the connection, usually because
          // the response indicated the "Connection: close" semantic.
          break;
        }
      }

      // Send a TCP shutdown
      stream.socket().shutdown(net::ip::tcp::socket::shutdown_send);
    }
};
} // namespace isce
#endif