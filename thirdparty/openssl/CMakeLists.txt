cmake_minimum_required(VERSION 3.1)

# extract the archive in the build directory

# create sources folder
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/thirdparty_sources)
# extract
set(openssl_source_dir ${CMAKE_BINARY_DIR}/thirdparty_sources/openssl)

Unpack(
  SOURCE
    https://www.openssl.org/source/openssl-1.0.2d.tar.gz
  DESTINATION 
    ${openssl_source_dir}
  DOWNLOAD
)

# Return source directory
set(openssl_source_dir ${openssl_source_dir}/openssl-1.0.2d PARENT_SCOPE)
