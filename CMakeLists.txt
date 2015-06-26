cmake_minimum_required (VERSION 2.6)
project(dmcNode)
enable_testing()

# Child projects
add_subdirectory(src)

# Used libraries
add_subdirectory(lib/cjson/src)
add_subdirectory(lib/poco)

# Add tests
add_subdirectory(test)