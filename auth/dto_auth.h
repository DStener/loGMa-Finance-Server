#pragma once
#define SQL_STRUCT_DECLARING

#include <boost/fusion/adapted/struct.hpp>

#include <isce/sqlAttrib.h>

using namespace isce;

struct User {
  __sql__ username VARCHAR NOTNULL UNIQUE;
  __sql__ email VARCHAR NOTNULL UNIQUE;
  __sql__ password VARCHAR NOTNULL;
  __sql__ birthday TIMESTAMP NOTNULL;
};
BOOST_FUSION_ADAPT_STRUCT(User, username, email, password, birthday)

struct Token {
  __sql__ id_user SERIAL REFERENCES(User);
  __sql__ token VARCHAR NOTNULL;
  __sql__ time TIMESTAMP NOTNULL;
};
BOOST_FUSION_ADAPT_STRUCT(Token, id_user, token, time)



struct Login {
  std::string        username;
  std::string        password;
};
BOOST_FUSION_ADAPT_STRUCT(Login, username, password)

struct Register {
  std::string        username;
  std::string        email;
  std::string        password;
  std::string        c_password;
  posix_time::ptime  birthday;
};
BOOST_FUSION_ADAPT_STRUCT(Register, username, email, password, c_password,
                          birthday)


#undef SQL_STRUCT_DECLARING