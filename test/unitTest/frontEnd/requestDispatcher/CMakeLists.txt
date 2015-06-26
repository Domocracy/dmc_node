cmake_minimum_required (VERSION 2.6)

add_executable(testRequestDispatcher "main.cpp")

add_test(RequestDispatcherUnit testRequestDispatcher)