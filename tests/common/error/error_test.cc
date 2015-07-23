#include "gtest/gtest.h"
#include "common/error/conversion.h"

TEST(ErrorTest, Conversion) {
  auto std_error = std::make_error_code(std::errc::broken_pipe);
  auto boost_error = boost::system::errc::make_error_code(boost::system::errc::errc_t::broken_pipe);
  
  std::error_code uninit_std;
  boost::system::error_code uninit_boost;
  
  lizz::FromBoostError(boost_error, uninit_std);
  EXPECT_EQ(uninit_std, std_error);
  
  
  lizz::ToBoostError(std_error, uninit_boost);
  EXPECT_EQ(uninit_boost, boost_error);
}
