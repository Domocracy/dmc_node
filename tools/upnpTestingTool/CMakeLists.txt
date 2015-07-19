cmake_minimum_required (VERSION 2.6)
if(POLICY CMP0048)
	cmake_policy(SET CMP0048 OLD)
endif()
project(upnpTestingTool)

# Collect all sources
file(GLOB_RECURSE UPNPTESTING_SOURCE_FILES "src/*.cpp" "src/*.h" "src/*.inl")

# Clasify sources according to folder structure.
# This creates a nice layout for the project in visual studio
# This macro is courtesy of http://www.cmake.org/pipermail/cmake/2013-November/056336.html
macro(GroupSources curdir)
	file(GLOB children RELATIVE ${PROJECT_SOURCE_DIR}/${curdir}
		${PROJECT_SOURCE_DIR}/${curdir}/*)
	foreach(child ${children})
		if(IS_DIRECTORY ${PROJECT_SOURCE_DIR}/${curdir}/${child})
			GroupSources(${curdir}/${child})
		else()
			string(REPLACE "/" "\\" groupname ${curdir})
			source_group(${groupname} FILES ${PROJECT_SOURCE_DIR}/${curdir}/${child})
		endif()
	endforeach()
endmacro()

GroupSources(src)
source_group(dmc_node FILES ${NODE_SOURCES})
add_executable(upnpTestingTool ${UPNPTESTING_SOURCE_FILES})

# Compiler specific options
if(MSVC)
	add_definitions(-DNOMINMAX)
	target_link_libraries(upnpTestingTool LINK_PUBLIC Ws2_32 Mswsock)
endif(MSVC)
if(CMAKE_COMPILER_IS_GNUCXX)
    add_definitions(-std=c++11)
endif()

target_include_directories(upnpTestingTool PUBLIC ${PROJECT_SOURCE_DIR}/src)
target_include_directories(upnpTestingTool PUBLIC ${PROJECT_SOURCE_DIR}/../../lib/poco/Net/include)
target_include_directories(upnpTestingTool PUBLIC ${PROJECT_SOURCE_DIR}/../../lib/poco/Util/include)

target_link_libraries(upnpTestingTool LINK_PUBLIC PocoNet)
target_link_libraries(upnpTestingTool LINK_PUBLIC PocoUtil)