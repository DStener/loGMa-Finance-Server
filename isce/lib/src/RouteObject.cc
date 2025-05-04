#include <isce/Route.h>

using namespace isce;

__object_ptr__ RouteObjet::get(uri_t&& uri, callback_t&& callback) {
  _methods.clear();

  _uri = std::move(uri);
  _callback = std::move(callback);
  _methods.insert(http::verb::get);

  return shared_from_this();
}
__object_ptr__ RouteObjet::post(uri_t&& uri, callback_t&& callback) {
  _methods.clear();

  _uri = std::move(uri);
  _callback = std::move(callback);
  _methods.insert(http::verb::post);

  return shared_from_this();
}
__object_ptr__ RouteObjet::put(uri_t&& uri, callback_t&& callback) {
  _methods.clear();

  _uri = std::move(uri);
  _callback = std::move(callback);
  _methods.insert(http::verb::put);

  return shared_from_this();
}
__object_ptr__ RouteObjet::patch(uri_t&& uri, callback_t&& callback) {
  _methods.clear();

  _uri = std::move(uri);
  _callback = std::move(callback);
  _methods.insert(http::verb::patch);

  return shared_from_this();
}
__object_ptr__ RouteObjet::delete_(uri_t&& uri, callback_t&& callback) {
  _methods.clear();

  _uri = std::move(uri);
  _callback = std::move(callback);
  _methods.insert(http::verb::delete_);

  return shared_from_this();
}
__object_ptr__ RouteObjet::options(uri_t&& uri, callback_t&& callback) {
  _methods.clear();

  _uri = std::move(uri);
  _callback = std::move(callback);
  _methods.insert(http::verb::options);

  return shared_from_this();
}

__object_ptr__ RouteObjet::any(uri_t&& uri, callback_t&& callback) {
  _uri = std::move(uri);
  _callback = std::move(callback);

  _methods.insert(http::verb::get);
  _methods.insert(http::verb::post);
  _methods.insert(http::verb::put);
  _methods.insert(http::verb::patch);
  _methods.insert(http::verb::delete_);
  _methods.insert(http::verb::options);

  return shared_from_this();
}


__object_ptr__ RouteObjet::match(methods_t&& methods, uri_t&& uri, callback_t&& callback) {
  _methods.clear();

  _uri = std::move(uri);
  _callback = std::move(callback);
  _methods.insert_range(methods);

  return shared_from_this();
}


__object_ptr__ RouteObjet::prefix(prefix_t&& pref) {
  _prefix = std::move(pref);
  return shared_from_this();
}

__object_ptr__ RouteObjet::middleware(middlewares_t&& middlewares) {
  _middlewares.append_range(std::move(middlewares));
  return shared_from_this();
}

