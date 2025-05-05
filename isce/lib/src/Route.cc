#include "Route.h"
#include <isce/Framework.h>


using namespace isce;

__object_ptr__ Route::get(uri_t&& uri, callback_t&& callback) {
  auto pRoute = std::make_shared<RouteObjet>();

  pRoute->get(std::move(uri), std::move(callback));
  app()->add(pRoute);

  return pRoute;
}

__object_ptr__ Route::post(uri_t&& uri, callback_t&& callback) {
  auto pRoute = std::make_shared<RouteObjet>();

  pRoute->post(std::move(uri), std::move(callback));
  app()->add(pRoute);

  return pRoute;
}

__object_ptr__ Route::put(uri_t&& uri, callback_t&& callback) {
  auto pRoute = std::make_shared<RouteObjet>();

  pRoute->put(std::move(uri), std::move(callback));
  app()->add(pRoute);

  return pRoute;
}

__object_ptr__ Route::patch(uri_t&& uri, callback_t&& callback) {
  auto pRoute = std::make_shared<RouteObjet>();

  pRoute->patch(std::move(uri), std::move(callback));
  app()->add(pRoute);

  return pRoute;
}

__object_ptr__ Route::delete_(uri_t&& uri, callback_t&& callback) {
  auto pRoute = std::make_shared<RouteObjet>();

  pRoute->delete_(std::move(uri), std::move(callback));
  app()->add(pRoute);

  return pRoute;
}

__object_ptr__ Route::options(uri_t&& uri, callback_t&& callback) {
  auto pRoute = std::make_shared<RouteObjet>();

  pRoute->options(std::move(uri), std::move(callback));
  app()->add(pRoute);

  return pRoute;
}

__object_ptr__ Route::any(uri_t&& uri, callback_t&& callback) {
  auto pRoute = std::make_shared<RouteObjet>();

  pRoute->any(std::move(uri), std::move(callback));
  app()->add(pRoute);

  return pRoute;
}

__group_ptr__ Route::prefix(std::string_view&& pref) {
  auto pRouteGroup = std::make_shared<RouteGroup>();
  return pRouteGroup->prefix(std::move(pref));
}

__group_ptr__ Route::middleware(middlewares_t&& middlewares) {
  auto pRouteGroup = std::make_shared<RouteGroup>();
  return pRouteGroup->middleware(std::move(middlewares));
}

__group_ptr__ Route::group(routes_t&& routes) {
  auto pRouteGroup = std::make_shared<RouteGroup>();
  return pRouteGroup->group(std::move(routes));
}
