add_executable(spotify_test
  spotify_test.cc)

target_link_libraries(spotify_test
  gtest gtest_main cpprest)
