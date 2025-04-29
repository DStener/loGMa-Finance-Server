#pragma once

#include <functional>

#include <boost/core/type_name.hpp>

#include <isce/HttpFramework.h>
#include <string_view>


#define METHOD_LIST_BEGIN                                                 \
  static void init() {
#define METHOD_ADD(func, pattern, method)                                  \
    registerMethod(&func, pattern, method);  
#define METHOD_LIST_END                                                   \
    return;                                                               \
  }

namespace isce {
static std::string __service_name__;

/**
 * @brief The reflection base class template for Microservice
 *
 * @tparam T the type of the implementation class
 */
template <typename T>
class Microservice {
 protected:
  template <typename FUNCTION>
  static void registerMethod(
      FUNCTION&& func,
      std::string_view target,
      http::verb&& method) {

    static T t;
    func_t wrapper = std::bind(std::forward<FUNCTION>(func), &t, std::placeholders::_1, std::placeholders::_2);

    isce::HttpFramework::registerMethod(
        std::move(wrapper),
        target,
        std::move(method)
    );
  }

 private:
  class methodRegistrator {
    public:
      methodRegistrator() {   
        //instance = new this();  
        T::init(); 
      }
  };

  // use static value to register controller method in framework before
  // main();  
  //inline static T& instance = new T();
  static methodRegistrator registrator_;

  // Necessary to trick the compiler
  virtual void *touch() { return &registrator_; }
};
template <typename T>
typename Microservice<T>::methodRegistrator 
  Microservice<T>::registrator_;
} // namespace isce