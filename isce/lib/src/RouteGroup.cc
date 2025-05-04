#include <isce/Route.h>

using namespace isce;

__group_ptr__ RouteGroup::prefix(std::string_view&& pref) {
  _prefix = std::move(pref);
  this->update();
  return shared_from_this();
}

__group_ptr__ RouteGroup::middleware(middlewares_t&& middlewares) {
  _middlewares.append_range(std::move(middlewares));
  this->update();
  return shared_from_this();
}

__group_ptr__ RouteGroup::group(routes_t&& routes) {
  _routes = {};
  for (auto& pRoute : routes) {
    _routes.push_back(std::move(pRoute));
  }
  this->update();
  return shared_from_this();
}

void RouteGroup::update() {
  for (auto& pRoute : _routes) {
    pRoute->_prefix = _prefix;
    pRoute->_middlewares.append_range(_middlewares);
  }
}