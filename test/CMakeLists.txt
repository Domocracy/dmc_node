cmake_minimum_required (VERSION 2.6)
if(POLICY CMP0048)
	cmake_policy(SET CMP0048 OLD)
endif()
project(test)

# Adding Test types
add_subdirectory(unitTest)
add_subdirectory(integrationTest)