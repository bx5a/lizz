include_directories(${BOOST_INCLUDEDIR})

add_executable(light_http_server_test
  light_http_server_test.cc)

target_link_libraries(light_http_server_test
  gtest
  gtest_main
  lizz
)

add_subdirectory(future)
