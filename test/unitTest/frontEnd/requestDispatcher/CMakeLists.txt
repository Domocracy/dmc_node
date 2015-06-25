cmake_minimum_required (VERSION 2.6)

add_executable(requestDispatcher "main.cpp")

add_test(RequestDispatcherUnit requestDispatcher)