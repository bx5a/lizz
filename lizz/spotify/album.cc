#include "spotify/object.h"

#include "spotify/album.h"
#include "spotify/track.h"
#include "spotify/artist.h"

#include "common/utils/property_tree.h"

namespace lizz {
namespace spotify {
  
Album::Album(const boost::property_tree::ptree& album_info) :
    p_object_(std::make_shared<Object>()) {
  p_object_->Init(album_info);
}
  
Album::Album(std::shared_ptr<Object> p_obj) : p_object_(p_obj) {}
  
std::string Album::GetAlbumType(std::error_code& err) const {
  return p_object_->GetString("album_type", err);
}

std::list<std::shared_ptr<ArtistInterface>>
    Album::GetArtists(std::error_code& err) const {
  std::list<std::shared_ptr<ArtistInterface>> ret;
  auto artists = p_object_->GetObjectList("artists", err);
  for (const auto& artist: artists) {
    ret.push_back(std::make_shared<Artist>(artist));
  }
  return ret;
}

std::list<std::string> Album::GetAvailableMarkets(std::error_code& err) const {
  return p_object_->GetStringList("available_markets", err);
}

// GetCopyrights
// GetExternalIds
// GetExternalUrls

std::list<std::string> Album::GetGenres(std::error_code& err) const {
  return p_object_->GetStringList("genres", err);
}

std::string Album::GetHref(std::error_code& err) const {
  return p_object_->GetString("href", err);
}

std::string Album::GetId(std::error_code& err) const {
  return p_object_->GetString("id", err);
}

// GetImages

std::string Album::GetName(std::error_code& err) const {
  return p_object_->GetString("name", err);
}

uint8_t Album::GetPopularity(std::error_code& err) const {
  return p_object_->GetUInt8("popularity", err);
}

// TOOD(bx5a): should be a unique function for release date and return chrono
std::string Album::GetReleaseDate(std::error_code& err) const {
  return p_object_->GetString("release_date", err);
}

std::string Album::GetReleaseDatePrecision(std::error_code& err) const {
  return p_object_->GetString("release_date_precision", err);
}

std::list<std::shared_ptr<TrackInterface>>
    Album::GetTracks(std::error_code& err) const {
      
  std::list<std::shared_ptr<TrackInterface>> ret;
  auto tracks = p_object_->GetObjectList("tracks", err);
  for (const auto& track: tracks) {
    ret.push_back(std::make_shared<Track>(track));
  }
  return ret;
}

std::string Album::GetType(std::error_code& err) const {
  return p_object_->GetString("type", err);
}

std::string Album::GetUri(std::error_code& err) const {
  return p_object_->GetString("uri", err);
}
  
}  // namespace spotify
}  // namespace lizz