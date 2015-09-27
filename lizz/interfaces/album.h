#ifndef LIZZ_INTERFACES_ALBUM_H_
#define LIZZ_INTERFACES_ALBUM_H_

#include <memory>
#include <list>
#include <system_error>
#include <string>

#include "interfaces/fwd.h"

namespace lizz {
  
class Album {
public:
  virtual ArtistList GetArtists(std::error_code& err) const = 0;
  virtual std::list<std::string> GetGenres(std::error_code& err) const = 0;
  virtual std::string GetName(std::error_code& err) const = 0;
  virtual std::string GetReleaseDate(std::error_code& err) const = 0;
  virtual TrackList GetTracks(std::error_code& err) const = 0;
};
  
}  // namespace lizz

#endif  // LIZZ_INTERFACES_ALBUM_H_
