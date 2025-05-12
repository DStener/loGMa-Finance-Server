#pragma once

#include <format>
#include <string>
#include <string_view>
#include <utility>

#include <libpq-fe.h>

#include <boost/json.hpp>
#include <boost/fusion/adapted.hpp>
#include <boost/fusion/sequence.hpp>
#include <boost/fusion/mpl.hpp>
#include <boost/core/type_name.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string/join.hpp>
#include <boost/date_time/posix_time/time_formatters.hpp>
#include <boost/date_time/posix_time/time_parsers.hpp>
#include <boost/json/object.hpp>
#include <boost/json/parse_into.hpp>

#include <isce/sqlAttrib.h>
#include <vector>

namespace fs = std::filesystem;
namespace json = boost::json;

template <typename T>
using _DTORow = std::pair<SQL_SERIAL,T>;
template <typename T>
using ResponseVec = std::vector<_DTORow<T>>;

namespace isce {
class _DTO {
 public:
  template <typename T, typename Func>
  static void for_each(T& t, Func f)
  {
      using size = boost::fusion::extension::struct_size<T>;
      _DTO::FOREACH(t, f, std::make_index_sequence<size::value>());
  }

  template <typename T>
  static constexpr std::string getName() {
    return boost::core::type_name<T>();
  }

  template <typename T>
  static T fromJson(const json::object& json) {
    T t{};
    _DTO::for_each(t, [&](std::string_view name, auto& field) {
        using type_dec = std::remove_cvref_t<decltype(field)>;

        const auto it = json.find(name);

        if(it != json.end()){
          if constexpr (std::is_same_v<type_dec, SQL_INTEGER>) {
            field = static_cast<SQL_INTEGER>(it->value().as_int64());
          } else if constexpr (std::is_same_v<type_dec, SQL_SERIAL>) {
            field = static_cast<SQL_SERIAL>(it->value().as_uint64());
          } else if constexpr (std::is_same_v<type_dec, SQL_REAL>) {
            field = static_cast<SQL_REAL>(it->value().as_double());
          } else if constexpr (std::is_same_v<type_dec, SQL_BIGINT>) {
            field = static_cast<SQL_BIGINT>(it->value().as_int64());
          } else if constexpr (std::is_same_v<type_dec, SQL_BIGSERIAL>) {
            field = static_cast<SQL_BIGSERIAL>(it->value().as_uint64());
          } else if constexpr (std::is_same_v<type_dec, SQL_VARCHAR>) {
            field = static_cast<SQL_VARCHAR>(it->value().as_string());
          } else if constexpr (std::is_same_v<type_dec, SQL_TEXT>) {
            field = static_cast<SQL_TEXT>(it->value().as_string());
          } else if constexpr (std::is_same_v<type_dec, SQL_TIMESTAMP>) {
            field = posix_time::time_from_string(it->value().as_string().data());
          } else {
            field = it->value().as_string().c_str();
          }
        }
    });

    return t;
  }

  template <typename T>
  static json::object toJson(T& t) {
    json::object json{};

    _DTO::for_each(t, [&](std::string_view name, auto& field) {
      using type_dec = std::remove_cvref_t<decltype(field)>;
      if constexpr (std::is_same_v<type_dec, SQL_INTEGER>) {
        json[name] = static_cast<SQL_INTEGER>(field);
      } else if constexpr (std::is_same_v<type_dec, SQL_SERIAL>) {
        json[name] = static_cast<SQL_SERIAL>(field);
      } else if constexpr (std::is_same_v<type_dec, SQL_REAL>) {
        json[name] = static_cast<SQL_REAL>(field);
      } else if constexpr (std::is_same_v<type_dec, SQL_BIGINT>) {
        json[name] = static_cast<SQL_BIGINT>(field);
      } else if constexpr (std::is_same_v<type_dec, SQL_BIGSERIAL>) {
        json[name] = static_cast<SQL_BIGSERIAL>(field);
      } else if constexpr (std::is_same_v<type_dec, SQL_VARCHAR>) {
        json[name] = static_cast<SQL_VARCHAR>(field);
      } else if constexpr (std::is_same_v<type_dec, SQL_TEXT>) {
        json[name] = static_cast<SQL_TEXT>(field);
      } else if constexpr (std::is_same_v<type_dec, SQL_TIMESTAMP>) {
        json[name] = posix_time::to_simple_string(field);
      } else {
        json[name] = std::to_string(field);
      }
    });

    return json;
  }

  //template <typename T>
  //static T fromRequest(const request_t& req) {

  //  // const auto it = req.find(http::field::content_type);

  //  // // If not found content_type return empty struct
  //  // if(it == req.end()) { return T{}; }

  //  // const std::string_view body = req.body().c_str();

  //  // if(it->value().starts_with("application/json")) {
  //  //   return _DTO::fromJson<T>(json::parse(body).as_object());
  //  // }
  //  return T{};
  //}

  template <typename T>
  static ResponseVec<T> fromSQL(PGresult* res) {
    if(res == nullptr) { return {}; }

    ResponseVec<T> vec{};
    int rows = PQntuples(res); 
		int cols = PQnfields(res);

    for(int i = 0; i < rows; ++i) {
      T t;
      
      _DTO::for_each(t, [&](std::string_view name, auto& field) {
        int index = PQfnumber(res, name.data());
        if(index == -1) { return; } // if not found

        const auto value = PQgetvalue(res, i, index);

        if (std::holds_alternative<SQL_INTEGER>(field.value)) {
          field = std::stoi(value);
        } else if (std::holds_alternative<SQL_SERIAL>(field.value)) {
          field = static_cast<SQL_SERIAL>(std::stol(value));
        } else if (std::holds_alternative<SQL_REAL>(field.value)) {
          field = std::stof(value);
        } else if (std::holds_alternative<SQL_BIGINT>(field.value)) {
          field = static_cast<SQL_BIGINT>(std::stol(value));
        } else if (std::holds_alternative<SQL_BIGSERIAL>(field.value)) {
          field = static_cast<SQL_BIGSERIAL>(std::stoul(value));
        } else if (std::holds_alternative<SQL_VARCHAR>(field.value)) {
          field = std::string(value);
        } else if (std::holds_alternative<SQL_TEXT>(field.value)) {
          field = std::string(value);
        } else if (std::holds_alternative<SQL_TIMESTAMP>(field.value)) {
          field = posix_time::time_from_string(value);
        }
      });

      vec.push_back(std::make_pair(i, std::move(t)));
    }
    return vec;
  }

  template <typename T>
  static std::string sqlInsert(T& t) {
    std::vector<std::string> fields;
    std::vector<std::string> unique_fields;
    std::vector<std::string> values;

    _DTO::for_each(t, [&](std::string_view name, auto& field) {
      fields.push_back(name.data());

      if (field.hasConstraint(SQL_UNIQUE)){
        unique_fields.push_back(name.data());
      }

      if (std::holds_alternative<SQL_INTEGER>(field.value)) {
        auto value = std::get<SQL_INTEGER>(field.value);
        values.push_back(std::to_string(value));
      } else if (std::holds_alternative<SQL_SERIAL>(field.value)) {
        auto value = std::get<SQL_SERIAL>(field.value);
        values.push_back(std::to_string(value));
      } else if (std::holds_alternative<SQL_REAL>(field.value)) {
        auto value = std::get<SQL_REAL>(field.value);
        values.push_back(std::to_string(value));
      } else if (std::holds_alternative<SQL_BIGINT>(field.value)) {
        auto value = std::get<SQL_BIGINT>(field.value);
        values.push_back(std::to_string(value));
      } else if (std::holds_alternative<SQL_BIGSERIAL>(field.value)) {
        auto value = std::get<SQL_BIGSERIAL>(field.value);
        values.push_back(std::to_string(value));
      } else if (std::holds_alternative<SQL_VARCHAR>(field.value)) {
        auto value = std::get<SQL_VARCHAR>(field.value);
        values.push_back(std::format("'{}'", value));
      } else if (std::holds_alternative<SQL_TEXT>(field.value)) {
        auto value = std::get<SQL_TEXT>(field.value);
        values.push_back(std::format("'{}'", value));
      } else if (std::holds_alternative<SQL_TIMESTAMP>(field.value)) {
        auto value = std::get<SQL_TIMESTAMP>(field.value);
        values.push_back(std::format("'{}'", posix_time::to_simple_string(value)));
      }
    });

    if (!unique_fields.empty()) {
      // std::cout << "REJFKLEKLFBJLEBFJEJEGF" << std::endl;
      // return std::format("INSERT INTO \"{}\"({}) VALUES({}) "
      //                  "ON CONFLICT({}) DO NOTHING "
      //                  "RETURNING id;",
      //                  _DTO::getName<T>(), 
      //                  boost::join(fields, ", "),
      //                  boost::join(values, ", "),
      //                  boost::join(unique_fields, ", "));

      return std::format("INSERT INTO \"{0}\"({1}) VALUES({2}) "
                         "ON CONFLICT ON CONSTRAINT \"{0}_pkey\" DO NOTHING "
                         "RETURNING id;",
                         _DTO::getName<T>(), 
                         boost::join(fields, ", "),
                         boost::join(values, ", "));
    }

    return std::format("INSERT INTO \"{0}\"({1}) VALUES({2}) "
                       "RETURNING id;",
                       _DTO::getName<T>(), 
                       boost::join(fields, ", "),
                       boost::join(values, ", "));
  }

  template <typename T>
  static std::string sqlCreateTable(){
    T t;

    std::vector<std::string> fields;

    _DTO::for_each(t, [&](std::string_view name, auto& field) {

      std::vector<std::string> field_construct{name.data()};

      if (std::holds_alternative<SQL_INTEGER>(field.value)) {
        field_construct.push_back("INTEGER");
      } else if (std::holds_alternative<SQL_SERIAL>(field.value)) {
        field_construct.push_back("SERIAL");
      } else if (std::holds_alternative<SQL_REAL>(field.value)) {
        field_construct.push_back("REAL");
      } else if (std::holds_alternative<SQL_BIGINT>(field.value)) {
        field_construct.push_back("BIGINT");
      } else if (std::holds_alternative<SQL_BIGSERIAL>(field.value)) {
        field_construct.push_back("BIGSERIAL");
      } else if (std::holds_alternative<SQL_VARCHAR>(field.value)) {
        field_construct.push_back("VARCHAR");
      } else if (std::holds_alternative<SQL_TEXT>(field.value)) {
        field_construct.push_back("TEXT");
      } else if (std::holds_alternative<SQL_TIMESTAMP>(field.value)) {
        field_construct.push_back("TIMESTAMP");
      }

      if (field.hasConstraint(SQL_NOTNULL)) {
        field_construct.push_back("NOT NULL");
      }
      if (field.hasConstraint(SQL_UNIQUE)){
        field_construct.push_back("UNIQUE");
      }
      if (field.hasConstraint(SQL_PRIMARY)){
        field_construct.push_back("PRIMARY KEY");
      }
      if (field.hasConstraint(SQL_REFERENCES)){
        auto constr = field.getConstraint(SQL_REFERENCES);
        field_construct.push_back(std::format("REFERENCES \"{}\" (id)", constr.value));
      }
      if (field.hasConstraint(SQL_DEFAULT)){
        auto constr = field.getConstraint(SQL_DEFAULT);
        field_construct.push_back(std::format("DEFAULT {}", constr.value));
      }
      if (field.hasConstraint(SQL_CHECK)){
        auto constr = field.getConstraint(SQL_CHECK);
        field_construct.push_back(std::format("CHECK({})", constr.value));
      }

      fields.push_back(boost::join(field_construct," "));
    });

    return std::format("CREATE TABLE IF NOT EXISTS \"{}\""
                       "(" 
                         "id SERIAL PRIMARY KEY,"
                         "{}" 
                       ");",
                       _DTO::getName<T>(), 
                       boost::join(fields, ", "));
  }

 private:
  template <typename T, typename Func, std::size_t... I>
  static constexpr void FOREACH(T& t, Func f, std::index_sequence<I...>) {
      (
          f(boost::fusion::extension::struct_member_name<T, I>::call(),
            boost::fusion::at_c<I>(t)),
      ...);

  }
  template <typename T, typename Func, std::size_t... I>
  static constexpr void FOREACH_TWO(T& t1, T& t2, Func f, std::index_sequence<I...>) {
      (
          f(boost::fusion::extension::struct_member_name<T, I>::call(),
            boost::fusion::at_c<I>(t1), boost::fusion::at_c<I>(t2)),
      ...);
  }
};
} // namespae isce