#ifndef LIZZ_SPOTIFY_SPOTIFY_OBJECT_H_
#define LIZZ_SPOTIFY_SPOTIFY_OBJECT_H_

#include <system_error>
#include <cstdint>
#include <list>

#include <boost/property_tree/ptree.hpp>

// TODO(bx5a): should inherit a common class. Spotify special: when error
// first try to query complete object before returning
namespace lizz {
namespace spotify {
  
class SpotifyObject {
 public:
  void Init(const std::string& json_info, std::error_code& err);
  void Init(const boost::property_tree::ptree& info);
  
  std::string GetString(const std::string& path, std::error_code& err) const;
  std::list<std::string> GetStringList(const std::string& path,
                                       std::error_code& err) const;
  
  bool GetBool(const std::string& path, std::error_code& err) const;
  
  uint8_t GetUInt8(const std::string& path, std::error_code& err) const;
  uint16_t GetUInt16(const std::string& path, std::error_code& err) const;
  
  std::shared_ptr<SpotifyObject> GetObject(const std::string& path,
                                    std::error_code& err) const;
  std::list<std::shared_ptr<SpotifyObject>>
      GetObjectList(const std::string& path,
                    std::error_code& err) const;

  
 private:
  boost::property_tree::ptree info_;
};
    
}  // namespace spotify
}  // namespace lizz

#endif  // LIZZ_SPOTIFY_SPOTIFY_OBJECT_H_
