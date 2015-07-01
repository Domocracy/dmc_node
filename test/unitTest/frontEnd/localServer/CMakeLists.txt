cmake_minimum_required (VERSION 2.6)

add_executable(testLocalServer "test.cpp")

add_test(LocalServerUnit testLocalServer)