cmake_minimum_required (VERSION 2.6)

add_executable(testRequestDispatcher "main.cpp" ${CMAKE_SOURCE_DIR}/src/code/frontEnd/RequestDispatcher.cpp)

add_test(RequestDispatcherUnit testRequestDispatcher)