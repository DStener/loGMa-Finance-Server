#pragma once 

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/http/string_body.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/strand.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <string_view>

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

namespace sys {
class CBank : std::enable_shared_from_this<CBank> {
public:
  using ptr_t = std::shared_ptr<CBank>;

  const std::string host = "cbr.ru";
  const std::string port = "80";

  boost::property_tree::ptree currencies;


  ~CBank() = default;

private:
  CBank() {
    try {
        // The io_context is required for all I/O
        net::io_context ioc;

        // These objects perform our I/O
        tcp::resolver resolver(ioc);
        beast::tcp_stream stream(ioc);

        // Look up the domain name
        auto const results = resolver.resolve(host, port);

        // Make the connection on the IP address we get from a lookup
        stream.connect(results);

        // Set up an HTTP GET request message
        http::request<http::string_body> req{http::verb::get, "/scripts/XML_valFull.asp?d=0", 11};
        req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
        req.set(http::field::host, host);
        
        // Send the HTTP request to the remote host
        http::write(stream, req);

        // This buffer is used for reading and must be persisted
        beast::flat_buffer buffer;

        // Declare a container to hold the response
        http::response<http::string_body> res;

        // Receive the HTTP response
        http::read(stream, buffer, res);

        std::stringstream ss;
        ss << res.body();
        boost::property_tree::read_xml(ss, currencies);

        // Gracefully close the socket
        beast::error_code ec;
        stream.socket().shutdown(tcp::socket::shutdown_both, ec);

        // not_connected happens sometimes
        // so don't bother reporting it.
        //
        if (ec && ec != beast::errc::not_connected) {
          throw beast::system_error{ ec };
        }
    } catch(std::exception const& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
  }
  friend CBank::ptr_t cbank();
};

CBank::ptr_t cbank() {
  static std::once_flag flag;
  static CBank::ptr_t instance;
  std::call_once(flag, [&]() { instance.reset(new CBank()); });
  return instance;
}
} // namespace sys