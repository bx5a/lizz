include_directories(${BOOST_INCLUDEDIR})

add_executable(future_test
  future_test.cc)

target_link_libraries(future_test
  gtest
  gtest_main
  lizz
)