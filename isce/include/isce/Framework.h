#pragma once 

#include <memory>
#include <filesystem>



namespace isce {
  class  RouteObjet;
class Framework : public std::enable_shared_from_this<Framework> {
public:
  using path_t = std::filesystem::path;
  using framework_t = std::shared_ptr<Framework>;
  using route_t = std::shared_ptr<RouteObjet>;

  void run();
  framework_t add(route_t route);
  framework_t config(path_t path);
};
Framework::framework_t app();
}