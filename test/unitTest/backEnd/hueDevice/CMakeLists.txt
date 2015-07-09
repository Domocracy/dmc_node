cmake_minimum_required (VERSION 2.6)

add_executable(testHueDevice test.cpp ${CMAKE_SOURCE_DIR}/src/code/backEnd/devices/HueDevice.cpp)

add_test(HueDeviceUnit testHueDevice)