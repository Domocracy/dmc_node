cmake_minimum_required (VERSION 2.4)
project(dmcNode)
enable_testing()

# Child projects
add_subdirectory(src)

# Used libraries
add_subdirectory(lib/cjson/src)