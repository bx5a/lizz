cmake_minimum_required(VERSION 3.1)

# create sources folder
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/thirdparty_sources)

# extract
set(boost_source_dir ${CMAKE_BINARY_DIR}/thirdparty_sources/boost)

Unpack(
  SOURCE
    http://sourceforge.net/projects/boost/files/boost/1.57.0/boost_1_57_0.tar.gz 
  DESTINATION 
    ${boost_source_dir}
  DOWNLOAD
)

# Return source directory
set(boost_source_dir ${boost_source_dir}/boost_1_57_0 PARENT_SCOPE)
