#pragma once

#include <isce/HttpFramework.h>

#define METHOD_LIST_BEGIN                                                 \
  static void init() {
#define METHOD_ADD(func, pattern, method)                                  \
    isce::HttpFramework::registerMethod(&func, pattern, method);  
#define METHOD_LIST_END                                                   \
    return;                                                               \
  }

//#define 

namespace isce {
template <typename T>
class Microservice {
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