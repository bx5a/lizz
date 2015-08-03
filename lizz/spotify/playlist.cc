#include "spotify/playlist.h"

#include "common/utils/property_tree.h"
#include "spotify/track.h"

namespace lizz {
namespace spotify {
Playlist::Playlist(const boost::property_tree::ptree& playlist_info) :
  playlist_info_(playlist_info) {}

bool Playlist::GetCollaborative(std::error_code& err) const {
  return GetFromTree<bool>(playlist_info_, "collaborative", err);
}
std::string Playlist::GetDescription(std::error_code& err) const {
  return GetFromTree<std::string>(playlist_info_, "description", err);
}
// GetExternalUrls
// GetFollowers
std::string Playlist::GetHref(std::error_code& err) const {
  return GetFromTree<std::string>(playlist_info_, "href", err);
}
std::string Playlist::GetId(std::error_code& err) const {
  return GetFromTree<std::string>(playlist_info_, "id", err);
}
// GetImages
std::string Playlist::GetName(std::error_code& err) const {
  return GetFromTree<std::string>(playlist_info_, "name", err);
}
// GetOwner
bool Playlist::GetPublic(std::error_code& err) const {
  return GetFromTree<bool>(playlist_info_, "public", err);
}
std::string Playlist::GetSnapshotId(std::error_code& err) const {
  return GetFromTree<std::string>(playlist_info_, "snapshot_id", err);
}
std::list<std::shared_ptr<TrackInterface>>
    Playlist::GetTracks(std::error_code& err) const {
  std::list<std::shared_ptr<TrackInterface>> ret;
  auto to_run = [&ret](const boost::property_tree::ptree& tree){
    ret.push_back(std::make_shared<Track>(tree));
  };
  RunOnChilds(playlist_info_, "tracks", to_run, err);
  return ret;
}
std::string Playlist::GetType(std::error_code& err) const {
  return GetFromTree<std::string>(playlist_info_, "type", err);
}
std::string Playlist::GetUri(std::error_code& err) const {
  return GetFromTree<std::string>(playlist_info_, "uri", err);
}



}  // namespace spotify
}  // namespace lizz