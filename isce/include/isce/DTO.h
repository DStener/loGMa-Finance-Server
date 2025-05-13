#pragma once 

#include <string>
#include <format>

#include <boost/pfr.hpp>
#include <boost/json/object.hpp>

namespace json = boost::json;

template <typename T>
using row_tt = std::pair<size_t, T>;

template <typename T>
using resp_vec_t = std::vector<row_tt<T>>;

namespace isce {
class DTO {
public:
  template <typename T, typename Func>
  static void for_each(T& t, Func&& f)
  {
    using size = boost::pfr::tuple_size<T>;
    DTO::FOREACH(t, std::move(f), std::make_index_sequence<size::value>());
  }

  template <typename T>
  static json::object to_json(const T& t) {
    json::object out;

    DTO::for_each(t, [&](std::string_view&& name, auto& field) {
      using field_t = std::remove_cvref_t<decltype(field)>;

      out[name] = field;
    });

    return out;
  }

  template <typename T>
  static json::object to_json(const row_tt<T>& row) {
    json::object out = DTO::to_json(row.second);
    out["id"] = std::to_string(row.first);
    return out;
  }

  template <typename T>
  static json::array to_json(const resp_vec_t<T>& vec) {
    json::array out;
    
    for (const auto& row : vec) {
      out.emplace_back(DTO::to_json(row));
    }

    return out;
  }

  template <typename T>
  static std::string to_string(const T& value) {
    using value_t = std::remove_cvref_t<decltype(value)>;

    if constexpr (std::is_same_v<value_t, size_t> || 
                  std::is_same_v<value_t, int>) {
      return std::to_string(value);
    } else {
      return std::format("'{}'", value);
    }
  }

private:
  DTO() = delete;
  ~DTO() = delete;

  template <typename T, typename Func, std::size_t... I>
  static constexpr void FOREACH(T& t, Func&& f, std::index_sequence<I...>) {
    (f(std::move(boost::pfr::get_name<I, T>()), boost::pfr::get<I>(t)), ...);
  }
};
} // namespace isce