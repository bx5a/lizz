#include "spotify/object.h"
#include "spotify/playlist.h"
#include "spotify/track.h"

namespace lizz {
namespace spotify {
Playlist::Playlist(const boost::property_tree::ptree& playlist_info) :
    p_object_(std::make_shared<Object>()) {
  p_object_->Init(playlist_info);
}
  
Playlist::Playlist(std::shared_ptr<Object> p_obj) : p_object_(p_obj) {}

bool Playlist::GetCollaborative(std::error_code& err) const {
  return p_object_->GetBool("collaborative", err);
}
std::string Playlist::GetDescription(std::error_code& err) const {
  return p_object_->GetString("description", err);
}
// GetExternalUrls
// GetFollowers
std::string Playlist::GetHref(std::error_code& err) const {
  return p_object_->GetString("href", err);
}
std::string Playlist::GetId(std::error_code& err) const {
  return p_object_->GetString("id", err);
}
// GetImages
std::string Playlist::GetName(std::error_code& err) const {
  return p_object_->GetString("name", err);
}
// GetOwner
bool Playlist::GetPublic(std::error_code& err) const {
  return p_object_->GetBool("public", err);
}
std::string Playlist::GetSnapshotId(std::error_code& err) const {
  return p_object_->GetString("snapshot_id", err);
}
  
std::list<std::shared_ptr<TrackInterface>>
    Playlist::GetTracks(std::error_code& err) const {
  std::list<std::shared_ptr<TrackInterface>> ret;
  auto tracks = p_object_->GetObjectList("tracks", err);
  for (const auto& track: tracks) {
    ret.push_back(std::make_shared<Track>(track));
  }
  return ret;
}
  
std::string Playlist::GetType(std::error_code& err) const {
  return p_object_->GetString("type", err);
}
std::string Playlist::GetUri(std::error_code& err) const {
  return p_object_->GetString("uri", err);
}



}  // namespace spotify
}  // namespace lizz