#include <isce/Request.h>

using namespace isce;

request_t isce::request() {
  return std::make_shared<Request>();
}

void Request::input(std::string& data) {

}

void Request::shutdown() {
  _is_shutdown = true;
}
bool Request::is_shutdown() {
  return _is_shutdown;
}