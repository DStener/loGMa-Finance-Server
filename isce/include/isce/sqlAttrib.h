#pragma once

#include <cstdint>
#include <string_view>
#include <type_traits>
#include <utility>
#include <string>
#include <variant>
#include <iostream>
#include <vector>

#include "boost/date_time/posix_time/posix_time.hpp" 


namespace isce {
// https://www.boost.org/doc/libs/master/doc/html/date_time.html
namespace posix_time = boost::posix_time;



// PostgreSQL basic datatype
// https://www.postgresql.org/docs/current/datatype.html
#define SQL_INTEGER           int32_t
#define SQL_SERIAL            uint32_t
#define SQL_REAL              float
#define SQL_BIGINT            int64_t
#define SQL_BIGSERIAL         uint64_t
#define SQL_VARCHAR           std::string
#define SQL_TEXT              std::string
#define SQL_TIMESTAMP         posix_time::ptime
// PostgreSQL basic constraints
// https://www.postgresql.org/docs/current/ddl-constraints.html
#define SQL_KEY
#define SQL_CHECK             __sql_constraint__(0b00000001)
#define SQL_NOTNULL           __sql_constraint__(0b00000010)
#define SQL_UNIQUE            __sql_constraint__(0b00000100)
#define SQL_PRIMARY           __sql_constraint__(0b00001000)
#define SQL_REFERENCES        __sql_constraint__(0b00010000)
#define SQL_DEFAULT           __sql_constraint__(0b00100000) 

// For DTO declaration, like at
// "__sql__ name VARCHAR NOTNULL UNIQUE"
#define INTEGER               =  __sql__(SQL_INTEGER{})
#define SERIAL                =  __sql__(SQL_SERIAL{})
#define REAL                  =  __sql__(SQL_REAL{})
#define BIGINT                =  __sql__(SQL_BIGINT{})
#define BIGSERIAL             =  __sql__(SQL_BIGSERIAL{})
#define VARCHAR               =  __sql__(SQL_VARCHAR{})
#define TEXT                  =  __sql__(SQL_TEXT{})
#define TIMESTAMP             =  __sql__(SQL_TIMESTAMP{})

#define KEY               
#define CHECK(condition)      +  __sql_constraint__(0b00000001, #condition)
#define NOTNULL               +  __sql_constraint__(0b00000010)
#define UNIQUE                +  __sql_constraint__(0b00000100)
#define PRIMARY               +  __sql_constraint__(0b00001000)
#define REFERENCES(ref)       +  __sql_constraint__(0b00010000, #ref)
#define DEFAULT(value)        +  __sql_constraint__(0b00100000, #value)




template <typename T>
concept sql_type =\
  std::is_same_v<T, int32_t>   ||        // INTEGER
  std::is_same_v<T, uint32_t>  ||        // SERIAL
  std::is_same_v<T, float>     ||        // REAL
  std::is_same_v<T, int64_t>   ||        // BIGINT
  std::is_same_v<T, uint64_t>  ||        // BIGSERIAL
  std::is_same_v<T, std::string>  ||     // VARCHAR, TEXT
  std::is_same_v<T, posix_time::ptime>;  // TIMESTAMP

using sql_type_t = std::variant<
    int32_t,             // INTEGER
    uint32_t,            // SERIAL
    float,               // REAL   
    int64_t,             // BIGINT
    uint64_t,            // BIGSERIAL
    std::string,         // VARCHAR, TEXT
    posix_time::ptime>;  // TIMESTAMP 

struct __sql_constraint__ {
  uint8_t flag;
  std::string_view value = "";
};

// Basic class
class __sql__ {
 public:
  sql_type_t value;
  
  template <sql_type T> 
  constexpr __sql__(const T& t) : value(t) {}
  template <sql_type T> 
  constexpr __sql__(T&& t) : value(std::move(t)) {}


  constexpr __sql_constraint__ getConstraint(__sql_constraint__&& target) {
    auto it = std::find_if(constraints.begin(), constraints.end(), 
                           [&](const __sql_constraint__& constr){
                            return target.flag == constr.flag;});
    
    return *it;
  }
  constexpr bool hasConstraint(__sql_constraint__&& target) {
    auto it = std::find_if(constraints.begin(), constraints.end(), 
                           [&](const __sql_constraint__& constr){
                            return target.flag == constr.flag;});
    
    return it != constraints.end();
  }



  template <sql_type T>
  constexpr __sql__ operator= (const __sql__& t) {
    value = t.value;
    return *this;
  }
  template <sql_type T>
  constexpr __sql__ operator= (__sql__&& t) {
    value = std::move(t.value);
    return *this;
  }
  template <sql_type T>
  constexpr __sql__ operator= (const T& t) {
    value = t;
    return *this;
  }
  template <sql_type T>
  constexpr __sql__ operator= (T&& t) {
    value = std::move(t);
    return *this;
  }
  

  constexpr __sql__ operator+ (__sql_constraint__ c) {
    constraints.push_back(c);
    return *this;
  }

 private:
  std::vector<__sql_constraint__> constraints;
};



} // namespace isce
