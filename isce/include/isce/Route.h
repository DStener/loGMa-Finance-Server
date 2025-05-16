#pragma once

#include <memory>
#include <string_view>
#include <vector>
#include <set>

#include <isce/Request.h>
#include <isce/Response.h>

namespace http	=	beast::http;

namespace isce {

class RouteObjet;
class RouteGroup;

using uri_t = std::string_view;
using prefix_t = std::string_view;
using middlewares_t = std::vector<std::string_view>;
using routes_t = std::vector<std::shared_ptr<RouteObjet>>;

using __object_ptr__ = std::shared_ptr<RouteObjet>;
using __group_ptr__ = std::shared_ptr<RouteGroup>;

using callback_t = std::function<response_t(request_t)>;

namespace Route {
  // User logic
  void up();

  __object_ptr__ get(uri_t&& uri, callback_t&& callback);
  __object_ptr__ post(uri_t&& uri, callback_t&& callback);
  __object_ptr__ put(uri_t&& uri, callback_t&& callback);
  __object_ptr__ patch(uri_t&& uri, callback_t&& callback);
  __object_ptr__ delete_(uri_t&& uri, callback_t&& callback);
  __object_ptr__ options(uri_t&& uri, callback_t&& callback);

  __object_ptr__ any(uri_t&& uri, callback_t&& callback);

  __group_ptr__ prefix(std::string_view&& pref);
  __group_ptr__ middleware(middlewares_t&& middlewares);
  __group_ptr__ group(routes_t&& routes);
}

class RouteObjet : public std::enable_shared_from_this<RouteObjet> {
 public:
  ~RouteObjet() = default;
  RouteObjet() = default;

  __object_ptr__ get(uri_t&& uri, callback_t&& callback);
  __object_ptr__ post(uri_t&& uri, callback_t&& callback);
  __object_ptr__ put(uri_t&& uri, callback_t&& callback);
  __object_ptr__ patch(uri_t&& uri, callback_t&& callback);
  __object_ptr__ delete_(uri_t&& uri, callback_t&& callback);
  __object_ptr__ options(uri_t&& uri, callback_t&& callback);

  __object_ptr__ any(uri_t&& uri, callback_t&& callback);

  __object_ptr__ prefix(prefix_t&& pref);
  __object_ptr__ middleware(middlewares_t&& middlewares);
};


class RouteGroup : public std::enable_shared_from_this<RouteGroup> {
 public:
  __group_ptr__ prefix(std::string_view&& pref);
  __group_ptr__ middleware(middlewares_t&& middlewares);
  __group_ptr__ group(routes_t&& routes);
};
} // namespace isce