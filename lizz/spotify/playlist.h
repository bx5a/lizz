#ifndef LIZZ_SPOTIFY_PLAYLIST_H_
#define LIZZ_SPOTIFY_PLAYLIST_H_

#include <memory>
#include <system_error>
#include <string>
#include <list>

#include <boost/property_tree/ptree.hpp>

#include "interfaces/playlist_interface.h"

namespace lizz {
class TrackInterface;
namespace spotify {
class Object;
class Playlist : public PlaylistInterface {
 public:
  static constexpr const char* kTypeName = "playlist";
  static constexpr const char* kPathInJson = "playlists.items";
  
  Playlist(const boost::property_tree::ptree& playlist_info);
  Playlist(std::shared_ptr<Object> p_obj);
  
  bool GetCollaborative(std::error_code& err) const;
  std::string GetDescription(std::error_code& err) const;
  // GetExternalUrls
  // GetFollowers
  std::string GetHref(std::error_code& err) const;
  std::string GetId(std::error_code& err) const;
  // GetImages
  std::string GetName(std::error_code& err) const;
  // GetOwner
  bool GetPublic(std::error_code& err) const;
  std::string GetSnapshotId(std::error_code& err) const;
  std::list<std::shared_ptr<TrackInterface>> GetTracks(std::error_code& err) const;
  std::string GetType(std::error_code& err) const;
  std::string GetUri(std::error_code& err) const;
  
 private:
  std::shared_ptr<Object> p_object_;
};
}  // namespace spotify
}  // namespace lizz

#endif  // LIZZ_SPOTIFY_PLAYLIST_H_
