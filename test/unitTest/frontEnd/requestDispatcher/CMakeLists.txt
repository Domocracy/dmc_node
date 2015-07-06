cmake_minimum_required (VERSION 2.6)

add_executable(testRequestDispatcher "test.cpp" ${CMAKE_SOURCE_DIR}/src/code/frontEnd/RequestDispatcher.cpp)
target_include_directories(testRequestDispatcher PUBLIC ${CMAKE_SOURCE_DIR}/lib/poco/Net/include ${CMAKE_SOURCE_DIR}/lib/poco/Foundation/include)
target_link_libraries(testRequestDispatcher LINK_PUBLIC PocoNet PocoFoundation)

add_test(RequestDispatcherUnit testRequestDispatcher)