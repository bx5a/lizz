include_directories(${BOOST_INCLUDEDIR})

AddTarget(
  light_http_server_test
  TYPE executable
  SOURCES light_http_server_test.cc
  LINK
    gtest
    gtest_main
    lizz
)
