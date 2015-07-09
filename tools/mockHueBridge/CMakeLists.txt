cmake_minimum_required (VERSION 2.6)
if(POLICY CMP0048)
	cmake_policy(SET CMP0048 OLD)
endif()
project(mockHueBridge)

# Collect all sources
file(GLOB_RECURSE MOCKHUEBRIDGE_SOURCE_FILES "code/*.cpp" "code/*.h" "code/*.inl")

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

GroupSources(code)

add_executable(mockHueBridge ${MOCKHUEBRIDGE_SOURCE_FILES})

# Compiler specific options
if(MSVC)
	add_definitions(-DNOMINMAX)
	target_link_libraries(mockHueBridge LINK_PUBLIC Ws2_32 Mswsock)
endif(MSVC)
if(CMAKE_COMPILER_IS_GNUCXX)
    add_definitions(-std=c++11)
endif()

target_include_directories(mockHueBridge PUBLIC ${PROJECT_SOURCE_DIR}/code)
target_include_directories(mockHueBridge PUBLIC ${PROJECT_SOURCE_DIR}/../../lib/cjson/src)
target_include_directories(mockHueBridge PUBLIC ${PROJECT_SOURCE_DIR}/../../lib/poco/Net/include)
target_include_directories(mockHueBridge PUBLIC ${PROJECT_SOURCE_DIR}/../../lib/poco/Util/include)

target_link_libraries(mockHueBridge LINK_PUBLIC cjson)
target_link_libraries(mockHueBridge LINK_PUBLIC PocoNet)
target_link_libraries(mockHueBridge LINK_PUBLIC PocoUtil)