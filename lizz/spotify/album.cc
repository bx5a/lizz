#include "spotify/album.h"
#include "spotify/track.h"
#include "spotify/artist.h"

#include "common/utils/property_tree.h"

namespace lizz {
namespace spotify {
  
Album::Album(const boost::property_tree::ptree& album_info) :
    album_info_(album_info) {}

std::string Album::GetAlbumType(std::error_code& err) const {
  return GetFromTree<std::string>(album_info_, "album_type", err);
}

std::list<std::shared_ptr<ArtistInterface>>
    Album::GetArtists(std::error_code& err) const {
  std::list<std::shared_ptr<ArtistInterface>> ret;
  auto to_run = [&ret](const boost::property_tree::ptree& tree){
    ret.push_back(std::make_shared<Artist>(tree));
  };
  RunOnChilds(album_info_, "artists", to_run, err);
  return ret;
}

std::list<std::string> Album::GetAvailableMarkets(std::error_code& err) const {
  return GetListFromTree<std::string>(album_info_, "available_markets", err);
}

// GetCopyrights
// GetExternalIds
// GetExternalUrls

std::list<std::string> Album::GetGenres(std::error_code& err) const {
  return GetListFromTree<std::string>(album_info_, "genres", err);
}

std::string Album::GetHref(std::error_code& err) const {
  return GetFromTree<std::string>(album_info_, "href", err);
}

std::string Album::GetId(std::error_code& err) const {
  return GetFromTree<std::string>(album_info_, "id", err);
}

// GetImages

std::string Album::GetName(std::error_code& err) const {
  return GetFromTree<std::string>(album_info_, "name", err);
}

uint8_t Album::GetPopularity(std::error_code& err) const {
  return GetFromTree<uint8_t>(album_info_, "popularity", err);
}

// TOOD(bx5a): should be a unique function for release date and return chrono
std::string Album::GetReleaseDate(std::error_code& err) const {
  return GetFromTree<std::string>(album_info_, "release_date", err);
}

std::string Album::GetReleaseDatePrecision(std::error_code& err) const {
  return GetFromTree<std::string>(album_info_, "release_date_precision", err);    
}

std::list<std::shared_ptr<TrackInterface>>
    Album::GetTracks(std::error_code& err) const {
  std::list<std::shared_ptr<TrackInterface>> ret;
  auto to_run = [&ret](const boost::property_tree::ptree& tree){
    ret.push_back(std::make_shared<Track>(tree));
  };
  RunOnChilds(album_info_, "tracks", to_run, err);
  return ret;
}

std::string Album::GetType(std::error_code& err) const {
  return GetFromTree<std::string>(album_info_, "type", err);
}

std::string Album::GetUri(std::error_code& err) const {
  return GetFromTree<std::string>(album_info_, "uri", err);
}
  
}  // namespace spotify
}  // namespace lizz