#ifndef LIZZ_ARTIST_H_
#define LIZZ_ARTIST_H_

#include <string>
#include <list>

namespace lizz {
class Artist {
 public:
  virtual std::string GetName(std::error_code& err) const = 0;
  virtual std::list<std::string> GetGenres(std::error_code& err) const = 0;
};
}  // namespace lizz

#endif  // LIZZ_ARTIST_H_
