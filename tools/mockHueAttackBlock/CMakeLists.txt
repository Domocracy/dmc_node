cmake_minimum_required (VERSION 2.6)
if(POLICY CMP0048)
	cmake_policy(SET CMP0048 OLD)
endif()
project(mockHueAttackBlock)

add_executable(mockHueAttackBlock main.cpp
					${PROJECT_SOURCE_DIR}/../../src/code/backend/deviceDrivers/hueDriver.cpp)
configure_file(config.json ${CMAKE_CURRENT_BINARY_DIR}/config.json COPYONLY)
target_include_directories(mockHueAttackBlock PUBLIC ${PROJECT_SOURCE_DIR}/../../src/code)
target_include_directories(mockHueAttackBlock PUBLIC ${PROJECT_SOURCE_DIR}/../../lib/poco/Net/include)
target_include_directories(mockHueAttackBlock PUBLIC ${PROJECT_SOURCE_DIR}/../../lib/poco/Util/include)
target_include_directories(mockHueAttackBlock PUBLIC ${CMAKE_SOURCE_DIR}/lib/cjson/src)

target_link_libraries(mockHueAttackBlock LINK_PUBLIC PocoNet PocoUtil cjson)