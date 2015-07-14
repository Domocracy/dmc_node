cmake_minimum_required (VERSION 2.6)

add_executable(testHueDriver test.cpp ${CMAKE_SOURCE_DIR}/src/code/backEnd/deviceDrivers/HueDriver.cpp)
target_include_directories(testHueDriver PUBLIC ${CMAKE_SOURCE_DIR}/lib/poco/Net/include
													${CMAKE_SOURCE_DIR}/lib/poco/Foundation/include
													${CMAKE_SOURCE_DIR}/lib/cjson/src)
target_link_libraries(testHueDriver LINK_PUBLIC cjson PocoNet PocoFoundation)

add_test(HueDriverUnit testHueDriver)