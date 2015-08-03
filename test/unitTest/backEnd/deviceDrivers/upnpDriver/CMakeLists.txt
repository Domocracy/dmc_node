cmake_minimum_required (VERSION 2.6)

add_executable(testUpnpDriver test.cpp ${CMAKE_SOURCE_DIR}/src/code/backEnd/deviceDrivers/UpnpDriver.cpp)

add_test(UpnpDriverUnit testUpnpDriver)