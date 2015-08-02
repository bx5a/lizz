include_directories(${BOOST_INCLUDEDIR})

AddTarget(
  future_test
  TYPE executable
  SOURCES future_test.cc
  LINK
    gtest
    gtest_main
    lizz
)
