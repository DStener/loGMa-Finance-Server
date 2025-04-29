#pragma once 

#include <string>

#include <boost/uuid/detail/md5.hpp>
#include <boost/algorithm/hex.hpp>

using boost::uuids::detail::md5;

namespace isce {
class Utils{
 public:
  static std::string getMd5(const std::string& value) {
    md5 hash;
    md5::digest_type digest;

    hash.process_bytes(value.data(), value.size());
    hash.get_digest(digest);

    const auto intDigest = reinterpret_cast<const int*>(&digest);
    std::string result;
    boost::algorithm::hex(intDigest, intDigest + (sizeof(md5::digest_type)/sizeof(int)), std::back_inserter(result));

    return result;
  }
};
} // namespace isce