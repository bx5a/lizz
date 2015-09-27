#include "spotify/spotify_object.h"
#include "spotify/spotify_playlist.h"
#include "spotify/spotify_track.h"

namespace lizz {
  
SpotifyPlaylist::SpotifyPlaylist(const boost::property_tree::ptree& playlist_info) :
    p_object_(std::make_shared<SpotifyObject>()) {
  p_object_->Init(playlist_info);
}
  
SpotifyPlaylist::SpotifyPlaylist(std::shared_ptr<SpotifyObject> p_obj) : p_object_(p_obj) {}

bool SpotifyPlaylist::GetCollaborative(std::error_code& err) const {
  return p_object_->GetBool("collaborative", err);
}
std::string SpotifyPlaylist::GetDescription(std::error_code& err) const {
  return p_object_->GetString("description", err);
}
// GetExternalUrls
// GetFollowers
std::string SpotifyPlaylist::GetHref(std::error_code& err) const {
  return p_object_->GetString("href", err);
}
std::string SpotifyPlaylist::GetId(std::error_code& err) const {
  return p_object_->GetString("id", err);
}
// GetImages
std::string SpotifyPlaylist::GetName(std::error_code& err) const {
  return p_object_->GetString("name", err);
}
// GetOwner
bool SpotifyPlaylist::GetPublic(std::error_code& err) const {
  return p_object_->GetBool("public", err);
}
std::string SpotifyPlaylist::GetSnapshotId(std::error_code& err) const {
  return p_object_->GetString("snapshot_id", err);
}
  
std::list<std::shared_ptr<Track>>
    SpotifyPlaylist::GetTracks(std::error_code& err) const {
  std::list<std::shared_ptr<Track>> ret;
  auto tracks = p_object_->GetObjectList("tracks", err);
  for (const auto& track: tracks) {
    ret.push_back(std::make_shared<SpotifyTrack>(track));
  }
  return ret;
}
  
std::string SpotifyPlaylist::GetType(std::error_code& err) const {
  return p_object_->GetString("type", err);
}
std::string SpotifyPlaylist::GetUri(std::error_code& err) const {
  return p_object_->GetString("uri", err);
}


}  // namespace lizz