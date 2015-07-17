cmake_minimum_required (VERSION 2.6)
if(POLICY CMP0048)
	cmake_policy(SET CMP0048 OLD)
endif()
project(toolHueAttack)

add_executable(toolHueAttack main.cpp)
target_include_directories(toolHueAttack PUBLIC ${PROJECT_SOURCE_DIR}/../../lib/poco/Net/include)
target_include_directories(toolHueAttack PUBLIC ${PROJECT_SOURCE_DIR}/../../lib/poco/Util/include)
target_include_directories(toolHueAttack PUBLIC ${PROJECT_SOURCE_DIR}/../../lib/cjson/src)

target_link_libraries(toolHueAttack LINK_PUBLIC PocoNet)
target_link_libraries(toolHueAttack LINK_PUBLIC PocoUtil)
target_link_libraries(toolHueAttack LINK_PUBLIC cjson)
