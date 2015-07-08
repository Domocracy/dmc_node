cmake_minimum_required (VERSION 2.6)

add_executable(testDeviceFactory test.cpp ${CMAKE_SOURCE_DIR}/src/code/backEnd/DeviceFactory.cpp)
target_link_libraries(testDeviceFactory LINK_PUBLIC cjson)

add_test(DeviceFactoryUnit testDeviceFactory)