#ifndef LIZZ_SEARCH_ENGINE_H_
#define LIZZ_SEARCH_ENGINE_H_

#include <future>
#include <cstdint>
#include <string>

#include "common/future.h"
#include "common/search_result.h"

namespace lizz {
  
class SearchEngine {
 public:
  virtual Future<SearchResult> Run(const std::string& query,
                                   uint16_t track_number,
                                   uint16_t album_number,
                                   uint16_t artist_number,
                                   uint16_t playlist_number) = 0;
};
  
}  // namespace lizz

#endif  // LIZZ_SEARCH_ENGINE_H_
