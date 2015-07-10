cmake_minimum_required (VERSION 2.6)
if(POLICY CMP0048)
	cmake_policy(SET CMP0048 OLD)
endif()

# Adding Test types
add_subdirectory(mockHueBridge)