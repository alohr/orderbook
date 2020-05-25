#add_subdirectory("${PROJECT_SOURCE_DIR}/extern/googletest")

#
# SimpleOrderBook
#

add_executable(orderbooktest OrderBookTest.cpp)

target_link_libraries(orderbooktest PUBLIC lob)
target_link_libraries(orderbooktest PUBLIC gtest gtest_main)

gtest_discover_tests(orderbooktest
  # Set a working directory to your project root so that you can find
  # test data via paths relative to the project root.
  
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
  PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
  PROPERTIES FIXTURES_REQUIRED orderbooktest
  #PROPERTIES FIXTURES_SETUP orderbooktest
)

#
# LobsterReader
#

add_executable(lobsterreadertest LobsterReaderTest.cpp)

target_link_libraries(lobsterreadertest PUBLIC lob)
target_link_libraries(lobsterreadertest PUBLIC ${Boost_LIBRARIES} gmock gmock_main)

add_test(LobsterReaderTest.AllCallbacks lobsterreadertest "${PROJECT_SOURCE_DIR}/data/lobster")

#
# LobsterOrderBook
#

add_executable(lobstertest LobsterTest.cpp)

target_link_libraries(lobstertest PUBLIC lob ${Boost_LIBRARIES} gmock gmock_main)

gtest_discover_tests(lobstertest
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
  PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
  PROPERTIES FIXTURES_REQUIRED lobstertest
)
