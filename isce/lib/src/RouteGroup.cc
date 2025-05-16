#include "Route.h"
#include <iterator>

using namespace isce;

__group_ptr__ RouteGroup::prefix(std::string_view&& pref) {
  _prefix = std::move(pref);
  this->update();
  return shared_from_this();
}

__group_ptr__ RouteGroup::middleware(middlewares_t&& middlewares) {
  std::move(middlewares.begin(), middlewares.end(), std::back_inserter(_middlewares));

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
    std::copy(_middlewares.begin(), _middlewares.end(), std::back_inserter(pRoute->_middlewares));
  }
}