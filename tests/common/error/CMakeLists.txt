include_directories(${BOOST_INCLUDEDIR})

AddTarget(
  error_test
  TYPE
    executable
  SOURCES
    error_test.cc
  LINK
    gtest
    gtest_main
    lizz
    ${Boost_LIBRARIES}
)
