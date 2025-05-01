#pragma once

namespace isce {

  template <typename T>
  class Route {
  public:
    template <typename FUNCTION>
    static void get(std::string target, FUNCTION&& func) {
      static T t; 
      func_t wrapper = std::bind(std::forward<FUNCTION>(func), &t, std::placeholders::_1, std::placeholders::_2);

      isce::HttpFramework::registerMethod(
        std::move(wrapper),
        target,
        http::verb::get;
      );
    }

    template <typename FUNCTION>
    static void post(std::string target, FUNCTION&& func) {
      static T t;
      func_t wrapper = std::bind(std::forward<FUNCTION>(func), &t, std::placeholders::_1, std::placeholders::_2);

      isce::HttpFramework::registerMethod(
        std::move(wrapper),
        target,
        http::verb::post;
      );
    }

    template <typename FUNCTION>
    static void put(std::string target, FUNCTION&& func) {
      static T t;
      func_t wrapper = std::bind(std::forward<FUNCTION>(func), &t, std::placeholders::_1, std::placeholders::_2);

      isce::HttpFramework::registerMethod(
        std::move(wrapper),
        target,
        http::verb::put;
      );
    }

    template <typename FUNCTION>
    static void delete(std::string target, FUNCTION&& func) {
      static T t;
      func_t wrapper = std::bind(std::forward<FUNCTION>(func), &t, std::placeholders::_1, std::placeholders::_2);

      isce::HttpFramework::registerMethod(
        std::move(wrapper),
        target,
        http::verb::delete;
      );
    }


  };
}