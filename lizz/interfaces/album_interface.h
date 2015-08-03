#ifndef LIZZ_ALBUM_INTERFACE_H_
#define LIZZ_ALBUM_INTERFACE_H_

#include <memory>
#include <list>
#include <system_error>
#include <string>

namespace lizz {
class TrackInterface;
class ArtistInterface;
class AlbumInterface {
public:
  virtual std::list<std::shared_ptr<ArtistInterface>>
      GetArtists(std::error_code& err) const = 0;
  virtual std::list<std::string> GetGenres(std::error_code& err) const = 0;
  virtual std::string GetName(std::error_code& err) const = 0;
  virtual std::string GetReleaseDate(std::error_code& err) const = 0;
  virtual std::list<std::shared_ptr<TrackInterface>>
      GetTracks(std::error_code& err) const = 0;
  
};
}  // namespace lizz

#endif  // LIZZ_ALBUM_INTERFACE_H_
