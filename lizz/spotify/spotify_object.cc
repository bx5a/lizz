#include "spotify/spotify_object.h"

#include <sstream>

#include <boost/property_tree/json_parser.hpp>

namespace lizz {
namespace spotify {
  
void SpotifyObject::Init(const std::string& json_info, std::error_code& err) {
  try {
    std::stringstream ss;
    ss << json_info;
    boost::property_tree::read_json(ss, info_);
  } catch(...) {
    err = std::make_error_code(std::errc::bad_message);
    return;
  }
}

void SpotifyObject::Init(const boost::property_tree::ptree& info) {
  info_ = info;
}

std::string SpotifyObject::GetString(const std::string& path,
                              std::error_code& err) const {
  auto val = info_.get_optional<std::string>(path);
  if (!val) {
    err = std::make_error_code(std::errc::bad_message);
  }
  return val.get();
}
  
std::list<std::string> SpotifyObject::GetStringList(const std::string& path,
                                             std::error_code& err) const {
  std::list<std::string> ret;
  auto child = info_.get_child_optional(path);
  if (!child) {
    err = std::make_error_code(std::errc::bad_message);
    return ret;
  }
  for (const auto& entry: info_.get_child(path)) {
    auto val = entry.second.get_optional<std::string>("");
    if (val) {
      ret.push_back(val.get());
    }
  }
  return ret;
}
  
bool SpotifyObject::GetBool(const std::string& path,
                     std::error_code& err) const {
  auto val = info_.get_optional<bool>(path);
  if (!val) {
    err = std::make_error_code(std::errc::bad_message);
  }
  return val.get();
}
  
uint8_t SpotifyObject::GetUInt8(const std::string& path,
                         std::error_code& err) const {
  
  auto val = info_.get_optional<uint8_t>(path);
  if (!val) {
    err = std::make_error_code(std::errc::bad_message);
  }
  return val.get();
}
  
uint16_t SpotifyObject::GetUInt16(const std::string& path,
                           std::error_code& err) const {
  
  auto val = info_.get_optional<uint16_t>(path);
  if (!val) {
    err = std::make_error_code(std::errc::bad_message);
  }
  return val.get();
}
  
std::shared_ptr<SpotifyObject> SpotifyObject::GetObject(const std::string& path,
                                          std::error_code& err) const {
  auto child = info_.get_child_optional(path);
  if (!child) {
    err = std::make_error_code(std::errc::bad_message);
    return std::shared_ptr<SpotifyObject>(nullptr);
  }
  auto ret = std::make_shared<SpotifyObject>();
  ret->Init(child.get());
  return ret;
}
  
std::list<std::shared_ptr<SpotifyObject>>
  SpotifyObject::GetObjectList(const std::string& path,
                        std::error_code& err) const {
    
  std::list<std::shared_ptr<SpotifyObject>> ret;
  auto child = info_.get_child_optional(path);
  if (!child) {
    err = std::make_error_code(std::errc::bad_message);
    return ret;
  }
  for (const auto& entry: info_.get_child(path)) {
    auto val = std::make_shared<SpotifyObject>();
    val->Init(entry.second);
    ret.push_back(val);
  }
  return ret;
}
 
  
}  // namespace spotify
}  // namespace lizz