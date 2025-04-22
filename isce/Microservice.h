#pragma once

#define METHOD_LIST_BEGIN         \
  static void init() \
  {
#define METHOD_ADD(method, pattern, ...) \
    registerMethod(&method, pattern, {__VA_ARGS__}, true, #method)
#define ADD_METHOD_TO(method, path_pattern, ...) \
    registerMethod(&method, path_pattern, {__VA_ARGS__}, false, #method)
#define ADD_METHOD_VIA_REGEX(method, regex, ...) \
    registerMethodViaRegex(&method, regex, {__VA_ARGS__}, #method)
#define METHOD_LIST_END \
    return;             \
  }
//#include_next

namespace isce {
template <typename T>
class Microservice {
  protected:

  private:
    class methodRegistrator {
      public:
        methodRegistrator() { T::init(); }
    };

    // use static value to register controller method in framework before
    // main();
    static methodRegistrator registrator_;

    // Necessary to trick the compiler
    virtual void *touch() { return &registrator_; }
};

template <typename T>
typename Microservice<T>::methodRegistrator 
  Microservice<T>::registrator_;
} // namespace isce