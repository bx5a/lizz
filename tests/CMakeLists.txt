enable_testing()

include_directories(${GTEST_INCLUDE_DIR})
add_subdirectory(./spotify)
add_subdirectory(./common)
add_subdirectory(./common/error)
