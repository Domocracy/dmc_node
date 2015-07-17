cmake_minimum_required (VERSION 2.6)
if(POLICY CMP0048)
	cmake_policy(SET CMP0048 OLD)
endif()
project(mockHueAttackBlock)

add_executable(mockHueAttackBlock main.cpp)
target_include_directories(mockHueAttackBlock PUBLIC ${PROJECT_SOURCE_DIR}/../../lib/poco/Net/include)
target_include_directories(mockHueAttackBlock PUBLIC ${PROJECT_SOURCE_DIR}/../../lib/poco/Util/include)

target_link_libraries(mockHueAttackBlock LINK_PUBLIC PocoNet)
target_link_libraries(mockHueAttackBlock LINK_PUBLIC PocoUtil)