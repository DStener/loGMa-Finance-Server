#ifndef _ISCE_ROUTE_
#define _ISCE_ROUTE_

#include <algorithm>
#include <boost/beast/http/verb.hpp>
#include <memory>
#include <string_view>
#include <utility>
#include <vector>
#include <set>

#ifndef _ISCE_HTTP_FRAMEWORK_
#include <isce/HttpFramework.h>
#endif

namespace beast	=	boost::beast;
namespace http	=	beast::http;
namespace net		=	boost::asio;

namespace isce {

  class RouteObjet;
  class RouteGroup;
  class Route;

  using uri_t = std::string_view;
  using prefix_t = std::string_view;
  using methods_t = std::set<http::verb>;
  using middlewares_t = std::vector<std::string_view>;
  using routes_t = std::vector<std::shared_ptr<RouteObjet>>;

class RouteObjet : public std::enable_shared_from_this<RouteObjet> {
  public:
    ~RouteObjet() = default;

    auto prefix(prefix_t&& pref) {
      _prefix = std::move(pref);
      return shared_from_this();
    }

    auto middleware(middlewares_t&& middlewares) {
      _middlewares.append_range(std::move(middlewares));
      return shared_from_this();
    }

  private: 
    uri_t _uri;
    callback_t _callback;
    prefix_t _prefix;
    methods_t _methods;
    middlewares_t _middlewares;

    RouteObjet() = default;

    friend RouteGroup;
    friend Route;
};

class RouteGroup : public std::enable_shared_from_this<RouteGroup> {
 public:
  auto prefix(std::string_view&& pref) {
    _prefix = std::move(pref);
    this->update();
    return shared_from_this();
  }

  auto middleware(middlewares_t&& middlewares) {
    _middlewares.append_range(std::move(middlewares));
    this->update();
    return shared_from_this();
  }

  auto group(routes_t&& routes) {
    _routes = {};
    for(auto& pRoute : routes) {
      _routes.push_back(std::move(pRoute));
    }
    this->update();
    return shared_from_this();
  }

 private:
  routes_t _routes;
  prefix_t _prefix;
  middlewares_t _middlewares;

  void update() {
    for(auto& pRoute : _routes) {
      pRoute->_prefix = _prefix;
      pRoute->_middlewares.append_range(_middlewares);
    }
  }
};

class Route {
 public:
  static auto get(uri_t&& uri, callback_t&& callback) {
    std::shared_ptr<RouteObjet> pRoute;
    pRoute.reset(new RouteObjet());

    pRoute->_uri = std::move(uri);
    pRoute->_callback = std::move(callback);
    pRoute->_methods.insert(http::verb::get);

    HttpFramework::addRoute(pRoute);
    return pRoute;
  }

  static auto post(uri_t&& uri, callback_t&& callback) {
    std::shared_ptr<RouteObjet> pRoute;
    pRoute.reset(new RouteObjet());

    pRoute->_uri = std::move(uri);
    pRoute->_callback = std::move(callback);
    pRoute->_methods.insert(http::verb::post);

    HttpFramework::addRoute(pRoute);
    return pRoute;
  }
  
  static auto put(uri_t&& uri, callback_t&& callback) {
    std::shared_ptr<RouteObjet> pRoute;
    pRoute.reset(new RouteObjet());

    pRoute->_uri = std::move(uri);
    pRoute->_callback = std::move(callback);
    pRoute->_methods.insert(http::verb::put);

    HttpFramework::addRoute(pRoute);
    return pRoute;
  }

  static auto patch(uri_t&& uri, callback_t&& callback) {
    std::shared_ptr<RouteObjet> pRoute;
    pRoute.reset(new RouteObjet());

    pRoute->_uri = std::move(uri);
    pRoute->_callback = std::move(callback);
    pRoute->_methods.insert(http::verb::patch);

    HttpFramework::addRoute(pRoute);
    return pRoute;
  }

  static auto delete_(uri_t&& uri, callback_t&& callback) {
    std::shared_ptr<RouteObjet> pRoute;
    pRoute.reset(new RouteObjet());

    pRoute->_uri = std::move(uri);
    pRoute->_callback = std::move(callback);
    pRoute->_methods.insert(http::verb::delete_);

    HttpFramework::addRoute(pRoute);
    return pRoute;
  }

  static auto options(uri_t&& uri, callback_t&& callback) {
    std::shared_ptr<RouteObjet> pRoute;
    pRoute.reset(new RouteObjet());

    pRoute->_uri = std::move(uri);
    pRoute->_callback = std::move(callback);
    pRoute->_methods.insert(http::verb::options);

    HttpFramework::addRoute(pRoute);
    return pRoute;
  }

  static auto any(uri_t&& uri, callback_t&& callback) {
    std::shared_ptr<RouteObjet> pRoute;
    pRoute.reset(new RouteObjet());

    pRoute->_uri = std::move(uri);
    pRoute->_callback = std::move(callback);

    pRoute->_methods.insert(http::verb::get);
    pRoute->_methods.insert(http::verb::post);
    pRoute->_methods.insert(http::verb::put);
    pRoute->_methods.insert(http::verb::patch);
    pRoute->_methods.insert(http::verb::delete_);
    pRoute->_methods.insert(http::verb::options);

    HttpFramework::addRoute(pRoute);
    return pRoute;
  }

  static auto match(methods_t&& methods, uri_t&& uri, callback_t&& callback) {
    std::shared_ptr<RouteObjet> pRoute;
    pRoute.reset(new RouteObjet());
    
    pRoute->_uri = std::move(uri);
    pRoute->_callback = std::move(callback);
    pRoute->_methods.insert_range(methods);

    HttpFramework::addRoute(pRoute);
    return pRoute;
  }


  static auto prefix(std::string_view&& pref) {
    auto pRouteGroup = std::make_shared<RouteGroup>();
    return pRouteGroup->prefix(std::move(pref));
  }
  
  static auto middleware(middlewares_t&& middlewares) {
    auto pRouteGroup = std::make_shared<RouteGroup>();
    return pRouteGroup->middleware(std::move(middlewares));
  }

  static auto group(routes_t&& routes) {
    auto pRouteGroup = std::make_shared<RouteGroup>();
    return pRouteGroup->group(std::move(routes));
  }

 private:
  Route() = delete;
  ~Route() = delete;
};
} // namespace isce
#endif 