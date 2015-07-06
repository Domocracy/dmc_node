cmake_minimum_required (VERSION 2.6)

add_executable(testLocalServer test.cpp ${CMAKE_SOURCE_DIR}/src/code/frontEnd/RequestDispatcher.cpp)
target_include_directories(testLocalServer PUBLIC ${CMAKE_SOURCE_DIR}/lib/poco/Net/include ${CMAKE_SOURCE_DIR}/lib/poco/Foundation/include)
target_link_libraries(testLocalServer LINK_PUBLIC PocoNet PocoFoundation)

add_test(LocalServerUnit testLocalServer)