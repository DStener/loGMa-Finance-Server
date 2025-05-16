#include "Route.h"
#include <iterator>

using namespace isce;


RouteObjet::RouteObjet(route_t route) {
  _uri = route->_uri;
  _callback = route->_callback;
  _prefix = route->_prefix;

  _methods.insert(route->_methods.begin(), route->_methods.end());
  _middlewares.insert(route->_middlewares.begin(), route->_middlewares.back());
  std::copy(route->vars.begin(), route->vars.end(), std::back_inserter(vars));
}

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

__object_ptr__ RouteObjet::prefix(prefix_t&& pref) {
  _prefix = std::move(pref);
  return shared_from_this();
}

__object_ptr__ RouteObjet::middleware(middlewares_t&& middlewares) {
  std::move(middlewares.begin(), middlewares.end(), std::back_inserter(_middlewares));
  return shared_from_this();
}

response_t RouteObjet::call(request_t request) {
  return _callback(request);
}

bool RouteObjet::is_match(uri_t uri, http::verb method) {

  if (_methods.find(method) == _methods.end()) { return false; }

  vars.clear();

  // Make path 
  bool has_first_slash = _prefix.starts_with('/');
  bool has_center_slash = _prefix.ends_with('/') ||
                          _uri.starts_with('/');

  std::string path = std::format("{0}{2}{1}{3}",
                                 ((has_first_slash) ? "" : "/"),
                                 ((has_center_slash) ? "" : "/"),
                                 _prefix, _uri);

  // position
  size_t uri_start = 0;
  size_t path_start = 0;
  size_t offset = path.find('{');
    
  bool flag = true;

  if (offset == uri_t::npos) {
    if (!uri.starts_with(path)) { return false; }
    return uri.find('/', path.size()) == uri_t::npos;
  }

  // Check uri border 
  if (uri_start + offset >= uri.size()) {
    return false;
  }

  for(;;) {

    //std::cout << "===" << std::endl;

    const auto uri_pos = uri.begin() + uri_start;
    const auto path_pos = path.begin() + path_start;

    uri_t uri_part(uri_pos, uri_pos + offset);
    uri_t path_part(path_pos, path_pos + offset);
      

    // Compare strings and set flag
    flag &= uri_part.starts_with(path_part);
      

    // Calculate next step
    size_t offset_old = offset;

    uri_start = uri.find('/', uri_start + offset);
    path_start = path.find('/', path_start + offset);
    offset = path.find('{', path_start) - path_start;

    // Check border 
    const bool uri_npos = (uri_start == uri_t::npos);
    const bool path_npos = (path_start == uri_t::npos);

    const bool uri_within = (uri_start + offset < uri.size());
    const bool path_within = (path_start + offset < path.size());

    // Add regex var to vector
    if ((!uri_npos && !path_npos) || path.ends_with('}')) {
      auto uri_end = ((uri_npos) ? uri.end() : uri.begin() + uri_start);
      auto path_end = ((path_npos) ? path.end() : path.begin() + path_start);

      std::string field(path_pos + offset_old + 1, path_end - 1);
      std::string value(uri_pos + offset_old, uri_end);

      // If has parametr in path like "?test=true...", then delete 
      if (uri_end == uri.end() && value.find('?') != std::string_view::npos) {
        value = std::string(value.begin(), value.begin() + value.find('?'));
      }
      std::cout << field << ": " << value << std::endl;
      vars.push_back(std::make_pair(field, value));
    }

    // End check 
    if (uri_npos && path_npos) {
      break;
    }
      
    // If the check has not been completed
    if ((uri_npos != path_npos) || !uri_within || !path_within) {
      return false;
    }

    
  }
  return flag;
  
}