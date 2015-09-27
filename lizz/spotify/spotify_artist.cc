#include "spotify/spotify_object.h"
#include "spotify/spotify_artist.h"

namespace lizz {

SpotifyArtist::SpotifyArtist(const boost::property_tree::ptree& artist_info) :
    p_object_(std::make_shared<SpotifyObject>()) {
  p_object_->Init(artist_info);
}
  
SpotifyArtist::SpotifyArtist(std::shared_ptr<SpotifyObject> p_obj) : p_object_(p_obj) {}
  
// GetExternalUrls
// GetFollowers
std::list<std::string> SpotifyArtist::GetGenres(std::error_code& err) const {
  return p_object_->GetStringList("genres", err);
}
std::string SpotifyArtist::GetHref(std::error_code& err) const {
  return p_object_->GetString("href", err);
}
std::string SpotifyArtist::GetId(std::error_code& err) const {
  return p_object_->GetString("id", err);
}
// GetImages
std::string SpotifyArtist::GetName(std::error_code& err) const {
  return p_object_->GetString("name", err);
}
uint8_t SpotifyArtist::GetPopularity(std::error_code& err) const {
  return p_object_->GetUInt8("popularity", err);
}
std::string SpotifyArtist::GetType(std::error_code& err) const {
  return p_object_->GetString("type", err);
}
std::string SpotifyArtist::GetUri(std::error_code& err) const {
  return p_object_->GetString("uri", err);
}

}  // namespace lizz
