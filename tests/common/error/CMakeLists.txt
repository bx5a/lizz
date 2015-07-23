include_directories(${BOOST_INCLUDEDIR})

add_executable(error_test
  error_test.cc)

target_link_libraries(error_test
  gtest
  gtest_main
  lizz
  ${Boost_LIBRARIES}
)