cmake_minimum_required (VERSION 2.6)

add_executable(testHueDevice test.cpp ${CMAKE_SOURCE_DIR}/src/code/backEnd/devices/HueDevice.cpp)
target_include_directories(testHueDevice ${CMAKE_SOURCE_DIR}/lib/cjson/src)
target_link_libraries(testHueDevice LINK_PUBLIC cjson)
add_test(HueDeviceUnit testHueDevice)