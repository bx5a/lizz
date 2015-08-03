#include "spotify/artist.h"

#include "common/utils/property_tree.h"

namespace lizz {
namespace spotify {

Artist::Artist(const boost::property_tree::ptree& artist_info) :
  artist_info_(artist_info) {}

// GetExternalUrls
// GetFollowers
std::list<std::string> Artist::GetGenres(std::error_code& err) const {
  return GetListFromTree<std::string>(artist_info_, "genres", err);
}
std::string Artist::GetHref(std::error_code& err) const {
  return GetFromTree<std::string>(artist_info_, "href", err);
}
std::string Artist::GetId(std::error_code& err) const {
  return GetFromTree<std::string>(artist_info_, "id", err);
}
// GetImages
std::string Artist::GetName(std::error_code& err) const {
  return GetFromTree<std::string>(artist_info_, "name", err);
}
uint8_t Artist::GetPopularity(std::error_code& err) const {
  return GetFromTree<uint8_t>(artist_info_, "popularity", err);
}
std::string Artist::GetType(std::error_code& err) const {
  return GetFromTree<std::string>(artist_info_, "type", err);
}
std::string Artist::GetUri(std::error_code& err) const {
  return GetFromTree<std::string>(artist_info_, "uri", err);
}

}  // namespace spotify
}  // namespace lizz
