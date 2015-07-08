cmake_minimum_required (VERSION 2.6)

add_executable(testDeviceManager test.cpp ${CMAKE_SOURCE_DIR}/src/code/backEnd/DeviceManager.cpp)

add_test(DeviceManagerUnit testDeviceManager)