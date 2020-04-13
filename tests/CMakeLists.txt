#add_subdirectory("${PROJECT_SOURCE_DIR}/extern/googletest")

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

add_executable(lobsterreadertest LobsterReaderTest.cpp)

target_link_libraries(lobsterreadertest PUBLIC lob)
target_link_libraries(lobsterreadertest PUBLIC ${Boost_LIBRARIES} gmock gmock_main)

add_test(AllCallbacks lobsterreadertest "${PROJECT_SOURCE_DIR}/data/lobster")
