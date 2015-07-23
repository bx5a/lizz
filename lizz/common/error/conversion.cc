#include "common/error/conversion.h"

namespace lizz {
  
void ToBoostError(const std::error_code& std_err,
                  boost::system::error_code& boost_err) {
  namespace bse = boost::system::errc;
  auto boost_errc = static_cast<bse::errc_t>(std_err.value());
  boost_err = boost::system::errc::make_error_code(boost_errc);
}
  
void FromBoostError(const boost::system::error_code& boost_err,
                    std::error_code& std_err) {
  std_err = std::make_error_code(static_cast<std::errc>(boost_err.value()));
}
  
}  // namespace lizz
