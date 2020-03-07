cmake_minimum_required(VERSION 3.14)

project(orderbook)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wall -Wextra -Wpedantic)

add_library(lob
  src/LobsterReader.cpp
  src/MessageReader.cpp
  src/OrderBook.cpp)

target_include_directories(lob PUBLIC include)
target_include_directories(lob PRIVATE src)

# dependencies
#target_link_libraries(orderbook PUBLiC abc)
#target_link_libraries(orderbook PRIVATE def)

#
# main program
#

add_custom_command(
  OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/cmdline.h ${CMAKE_CURRENT_BINARY_DIR}/cmdline.c
  COMMAND /usr/local/bin/gengetopt < ${CMAKE_CURRENT_SOURCE_DIR}/orderbook/orderbook.ggo
  DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/orderbook/orderbook.ggo
)

add_executable(orderbook orderbook/orderbook.cpp ${CMAKE_CURRENT_BINARY_DIR}/cmdline.c)

target_include_directories(orderbook PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(orderbook PUBLIC lob)

#
# testing
#

include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.10.0
)

FetchContent_GetProperties(googletest)
if (NOT googletest_POPULATED)
  FetchContent_Populate(googletest)
  add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
endif()

option(PACKAGE_TESTS "Build the tests" ON)

if (PACKAGE_TESTS)
  enable_testing()
  include(GoogleTest)
  add_subdirectory(test)
endif()
