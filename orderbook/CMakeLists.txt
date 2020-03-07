add_custom_command(
  OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/cmdline.h ${CMAKE_CURRENT_BINARY_DIR}/cmdline.c
  COMMAND /usr/local/bin/gengetopt < ${CMAKE_CURRENT_SOURCE_DIR}/orderbook.ggo
  DEPENDS orderbook.ggo
)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_executable(orderbook
  LobsterReader.cpp
  MessageReader.cpp
  OrderBook.cpp
  ${CMAKE_CURRENT_BINARY_DIR}/cmdline.c)

target_compile_features(orderbook PRIVATE cxx_std_17)

