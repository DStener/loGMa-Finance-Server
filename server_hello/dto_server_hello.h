#pragma once
#include <boost/date_time/posix_time/ptime.hpp>
#define SQL_STRUCT_DECLARING

#include <isce/sqlAttrib.h>

using namespace isce;

struct UserTest2 {
  __sql__ name VARCHAR PRIMARY KEY UNIQUE;
};
