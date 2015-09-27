#ifndef LIZZ_CLIENT_H_
#define LIZZ_CLIENT_H_

#include <memory>

#include "interfaces/fwd.h"

namespace lizz {
class SearchEngine;

class Client {
 public:
  virtual SearchEnginePtr GetSearchEngine() = 0;
};
 
}  // namespace lizz

#endif  // LIZZ_CLIENT_H_
