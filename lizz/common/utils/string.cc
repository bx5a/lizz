#include "common/utils/string.h"

namespace lizz {
void RemoveFirstAndLastCharacters(std::string* p_str, char if_char_equal) {
  if (p_str->size() >= 2) {
    if ((*p_str)[0] == if_char_equal &&
        (*p_str)[p_str->size() - 1] == if_char_equal) {
      *p_str = p_str->substr(1, p_str->size() - 2);
    }
  }
}
}  // namespace lizz

