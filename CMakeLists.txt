cmake_minimum_required (VERSION 2.6)
# dmc_node configuration
set(DMC_NODE_VERSION 0.1.0)

if(POLICY CMP0048)
	cmake_policy(SET CMP0048 OLD)
endif()
project(dmcNode)
set(PROJECT_VERSION ${DMC_NODE_VERSION})

# Generate doxygen documentation if doxygen is available
find_package(Doxygen)
if(DOXYGEN_FOUND)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
add_custom_target(doc ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
	COMMENT "Generating API documentation with Doxygen" VERBATIM)
endif(DOXYGEN_FOUND)

# Actual node project
add_subdirectory(src)
# Used libraries
add_subdirectory(lib/cjson/src)

# Configure POCO build options
set(ENABLE_XML ON)
set(ENABLE_JSON ON)
set(ENABLE_MONGODB OFF)
set(ENABLE_PDF OFF)
set(ENABLE_UTIL ON)
set(ENABLE_NET ON)
set(ENABLE_NETSSL OFF)
set(ENABLE_NETSSL_WIN OFF)
set(ENABLE_CRYPTO OFF)
set(ENABLE_DATA OFF)
set(ENABLE_DATA_SQLITE OFF)
set(ENABLE_DATA_MYSQL OFF)
set(ENABLE_DATA_ODBC OFF)
set(ENABLE_SEVENZIP OFF)
set(ENABLE_ZIP OFF)
set(ENABLE_APACHECOFFNECTOR OFF)
set(ENABLE_CPPPARSER OFF)
set(ENABLE_POCODOC OFF)
set(ENABLE_PAGECOMPILER OFF)
set(ENABLE_PAGECOMPILER_FILE2PAGE OFF)
set(FORCE_OPENSSL OFF)
set(ENABLE_TESTS OFF)
set(POCO_STATIC ON)
set(POCO_UNBUNDLED OFF)
add_subdirectory(lib/poco)

add_definitions( -DPOCO_STATIC -DPOCO_NO_AUTOMATIC_LIBS)
set( LIB_MODE STATIC )
	
# Add tests
enable_testing()
include_directories(src/code)
add_subdirectory(test)