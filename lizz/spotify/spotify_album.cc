#include "spotify/spotify_object.h"

#include "spotify/spotify_album.h"
#include "spotify/spotify_track.h"
#include "spotify/spotify_artist.h"

namespace lizz {
  
SpotifyAlbum::SpotifyAlbum(const boost::property_tree::ptree& album_info) :
    p_object_(std::make_shared<SpotifyObject>()) {
  p_object_->Init(album_info);
}
  
SpotifyAlbum::SpotifyAlbum(std::shared_ptr<SpotifyObject> p_obj) : p_object_(p_obj) {}
  
std::string SpotifyAlbum::GetAlbumType(std::error_code& err) const {
  return p_object_->GetString("album_type", err);
}

ArtistList SpotifyAlbum::GetArtists(std::error_code& err) const {
  ArtistList ret;
  auto artists = p_object_->GetObjectList("artists", err);
  for (const auto& artist: artists) {
    ret.push_back(std::make_shared<SpotifyArtist>(artist));
  }
  return ret;
}

std::list<std::string> SpotifyAlbum::GetAvailableMarkets(std::error_code& err) const {
  return p_object_->GetStringList("available_markets", err);
}

// GetCopyrights
// GetExternalIds
// GetExternalUrls

std::list<std::string> SpotifyAlbum::GetGenres(std::error_code& err) const {
  return p_object_->GetStringList("genres", err);
}

std::string SpotifyAlbum::GetHref(std::error_code& err) const {
  return p_object_->GetString("href", err);
}

std::string SpotifyAlbum::GetId(std::error_code& err) const {
  return p_object_->GetString("id", err);
}

// GetImages

std::string SpotifyAlbum::GetName(std::error_code& err) const {
  return p_object_->GetString("name", err);
}

uint8_t SpotifyAlbum::GetPopularity(std::error_code& err) const {
  return p_object_->GetUInt8("popularity", err);
}

// TOOD(bx5a): should be a unique function for release date and return chrono
std::string SpotifyAlbum::GetReleaseDate(std::error_code& err) const {
  return p_object_->GetString("release_date", err);
}

std::string SpotifyAlbum::GetReleaseDatePrecision(std::error_code& err) const {
  return p_object_->GetString("release_date_precision", err);
}

TrackList SpotifyAlbum::GetTracks(std::error_code& err) const {
  TrackList ret;
  auto tracks = p_object_->GetObjectList("tracks", err);
  for (const auto& track: tracks) {
    ret.push_back(std::make_shared<SpotifyTrack>(track));
  }
  return ret;
}

std::string SpotifyAlbum::GetType(std::error_code& err) const {
  return p_object_->GetString("type", err);
}

std::string SpotifyAlbum::GetUri(std::error_code& err) const {
  return p_object_->GetString("uri", err);
}
  
}  // namespace lizz