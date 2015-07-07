cmake_minimum_required (VERSION 2.6)

add_executable(testCommandDispatcher test.cpp ${CMAKE_SOURCE_DIR}/src/code/backEnd/RequestProcessors/CommandDispatcher.cpp)
target_include_directories(testCommandDispatcher PUBLIC ${CMAKE_SOURCE_DIR}/lib/poco/Net/include ${CMAKE_SOURCE_DIR}/lib/poco/Foundation/include ${CMAKE_SOURCE_DIR}/lib/cjson/src)
target_link_libraries(testCommandDispatcher LINK_PUBLIC cjson)

add_test(CommandDispatcherUnit testCommandDispatcher)