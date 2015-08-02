#ifndef LIZZ_COMMON_SEARCH_RESULT_H_
#define LIZZ_COMMON_SEARCH_RESULT_H_

namespace lizz {
  
class SearchResult {
 public:
  
  template <class T>
  void Add(std::shared_ptr<T> ptr) {}
  
  // TODO(bx5a): specify Add<TrackInterface> Add<AlbumInterface> etc...
  
//  template <class T>
//  const std::list<T>& Get() {}
};
  
}  // namespace lizz

#endif  // LIZZ_COMMON_SEARCH_RESULT_H_
