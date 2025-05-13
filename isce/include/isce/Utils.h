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

  static std::string generate_token(size_t len = 32) {

    std::string out;
    std::srand(std::time({}));
    
    for (size_t i = 0; i < len; ++i) {
      // 62 = len(0..9) + len(A..Z) + len(a..z)
      // 48 = '0' in ASCII
      char value = std::rand() % 62 + 48; 

      if (value > 57) { value += 8; } // A..Z
      if (value > 90) { value += 7; } // a..z

      out += value;
    }
   
    return out;
  }
};
} // namespace isce