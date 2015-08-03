#ifndef LIZZ_COMMON_UTILS_PROPERTY_TREE_H_
#define LIZZ_COMMON_UTILS_PROPERTY_TREE_H_

#include <list>
#include <string>
#include <system_error>
#include <functional>

#include <boost/property_tree/ptree.hpp>

namespace lizz {
  
template <typename T>
T GetFromTree(const boost::property_tree::ptree& tree,
              const std::string& key,
              std::error_code& err) {
  auto res = tree.get_optional<T>(key);
  if (!res) {
    err = std::make_error_code(std::errc::invalid_seek);
  }
  return res.get();
}
  
  
template <class FuncType>
void RunOnChilds(const boost::property_tree::ptree& tree,
                 const std::string& key,
                 FuncType fn,
                 std::error_code& err) {
  std::list<std::string> res;
  auto child = tree.get_child_optional(key);
  if (!child) {
    err = std::make_error_code(std::errc::invalid_seek);
    return;
  }
  for (const auto& child : tree.get_child(key)) {
    fn(child.second);
  }
}
  
template <typename T>
std::list<T> GetListFromTree(const boost::property_tree::ptree& tree,
                             const std::string& key,
                             std::error_code& err) {
  std::list<T> res;
  auto to_run = [&res](const boost::property_tree::ptree& child){
    auto val = child.get_optional<T>("");
    if (val) {
      res.push_back(val.get());
    }
  };
  RunOnChilds(tree, key, to_run, err);
  return res;
}
  
}  // namespace lizz


#endif  // LIZZ_COMMON_UTILS_PROPERTY_TREE_H_
