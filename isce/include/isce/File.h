#pragma once 

#include <string>
#include <string_view>
#include <fstream>
#include <filesystem>

namespace isce {
class File {
public:

  File() = default;
  ~File() = default;

  File(std::string&& name, std::string&& data, std::string&& filename)
    : _name(std::move(name)), _data(std::move(data)), _filename(std::move(filename)) {};
  

  std::string_view data() const { return std::string_view(_data); }
  std::string_view name() const { return std::string_view(_name); }
  std::string filename() const {
    return std::filesystem::path(_filename).filename().string();
  }

  void save(std::string file) const {
    std::ofstream ostrm(file, std::ios::binary);
    ostrm << _data;
  }


private:
  std::string _data;
  std::string _name;
  std::string _filename;
};
} // namespace isce