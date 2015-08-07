#ifndef LIZZ_ARTIST_INTERFACE_H_
#define LIZZ_ARTIST_INTERFACE_H_

#include <string>
#include <list>

namespace lizz {
class ArtistInterface {
 public:
  virtual std::string GetName(std::error_code& err) const = 0;
  virtual std::list<std::string> GetGenres(std::error_code& err) const = 0;
};
}  // namespace lizz

#endif  // LIZZ_ARTIST_INTERFACE_H_
