# POCO_BUILD_TYPE
# POCO_STATIC
# POCO_UNBUNDLED
# POCO_NO_LOCALE
#
# ENABLE_{COMPONENT}
# ENABLE_TESTS

project(Poco)

cmake_minimum_required(VERSION 3.0.0)

file(STRINGS "${CMAKE_CURRENT_SOURCE_DIR}/libversion" SHARED_LIBRARY_VERSION)

# Read the version information from the VERSION file
file (STRINGS "${CMAKE_CURRENT_SOURCE_DIR}/VERSION" PACKAGE_VERSION )
message(STATUS "Poco package version: ${PACKAGE_VERSION}")
string(REGEX REPLACE "([0-9]+)\\.[0-9]+\\.[0-9]+" "\\1" CPACK_PACKAGE_VERSION_MAJOR ${PACKAGE_VERSION})
string(REGEX REPLACE "[0-9]+\\.([0-9])+\\.[0-9]+" "\\1" CPACK_PACKAGE_VERSION_MINOR ${PACKAGE_VERSION})
string(REGEX REPLACE "[0-9]+\\.[0-9]+\\.([0-9]+)" "\\1" CPACK_PACKAGE_VERSION_PATCH ${PACKAGE_VERSION})

set(COMPLETE_VERSION ${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH})
set(RELEASE_NAME "Unstable-trunk")
set(PROJECT_VERSION ${COMPLETE_VERSION})

# Put the libaries and binaries that get built into directories at the
# top of the build tree rather than in hard-to-find leaf
# directories. This simplifies manual testing and the use of the build
# tree rather than installed Boost libraries.
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
# Windows DLLs are "runtime" for CMake. Output them to "bin" like the Visual Studio projects do.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Append our module directory to CMake
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

#################################################################################
# Setup C/C++ compiler options
#################################################################################

if(NOT MSVC_IDE)
  if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING
      "Choose the type of build, options are: None Debug Release" FORCE)
  endif()
  message(STATUS "Setting Poco build type - ${CMAKE_BUILD_TYPE}")
endif()

if (CMAKE_BUILD_TYPE STREQUAL "")
    set( CMAKE_BUILD_TYPE "RelWithDebInfo" )
endif ()

# http://www.cmake.org/Wiki/CMake_Useful_Variables :
# CMAKE_BUILD_TYPE
#    Choose the type of build. CMake has default flags for these:
#
#    * None (CMAKE_C_FLAGS or CMAKE_CXX_FLAGS used)
#    * Debug (CMAKE_C_FLAGS_DEBUG or CMAKE_CXX_FLAGS_DEBUG)
#    * Release (CMAKE_C_FLAGS_RELEASE or CMAKE_CXX_FLAGS_RELEASE)
#    * RelWithDebInfo (CMAKE_C_FLAGS_RELWITHDEBINFO or CMAKE_CXX_FLAGS_RELWITHDEBINFO
#    * MinSizeRel (CMAKE_C_FLAGS_MINSIZEREL or CMAKE_CXX_FLAGS_MINSIZEREL)

# For Debug build types, append a "d" to the library names.
set(CMAKE_DEBUG_POSTFIX "d" CACHE STRING "Set debug library postfix" FORCE)

# Include some common macros to simpilfy the Poco CMake files
include(PocoMacros)

# Allow enabling and disabling components
option(ENABLE_XML "Enable the XML" ON)
option(ENABLE_JSON "Enable the JSON" ON)
option(ENABLE_MONGODB "Enable MongoDB" ON)
option(ENABLE_PDF "Enable PDF" OFF)
option(ENABLE_UTIL "Enable Util" ON)
option(ENABLE_NET "Enable Net" ON)
option(ENABLE_NETSSL "Enable NetSSL" ON)
option(ENABLE_NETSSL_WIN "Enable NetSSL Windows" OFF)
option(ENABLE_CRYPTO "Enable Crypto" ON)
option(ENABLE_DATA "Enable Data" ON)
option(ENABLE_DATA_SQLITE "Enable Data SQlite" ON)
option(ENABLE_DATA_MYSQL "Enable Data MySQL" ON)
option(ENABLE_DATA_ODBC "Enable Data ODBC" ON)
option(ENABLE_SEVENZIP "Enable SevenZip" OFF)
option(ENABLE_ZIP "Enable Zip" ON)
option(ENABLE_APACHECONNECTOR "Enable ApacheConnector" OFF)
option(ENABLE_CPPPARSER "Enable C++ parser" OFF)
option(ENABLE_POCODOC "Enable Poco Documentation Generator" OFF)
option(ENABLE_PAGECOMPILER "Enable PageCompiler" ON)
option(ENABLE_PAGECOMPILER_FILE2PAGE "Enable File2Page" ON)

option(FORCE_OPENSSL "Force usage of OpenSSL even under windows" OFF)

option(ENABLE_TESTS
  "Set to OFF|ON (default is OFF) to control build of POCO tests & samples" OFF)

option(POCO_STATIC
  "Set to OFF|ON (default is OFF) to control build of POCO as STATIC library" OFF)

option(POCO_UNBUNDLED
  "Set to OFF|ON (default is OFF) to control linking dependencies as external" OFF)

# Uncomment from next two lines to force statitc or dynamic library, default is autodetection
if(POCO_STATIC)
    add_definitions( -DPOCO_STATIC -DPOCO_NO_AUTOMATIC_LIBS)
    set( LIB_MODE STATIC )
    message(STATUS "Building static libraries")
else(POCO_STATIC)
    set( LIB_MODE SHARED )
    message(STATUS "Building dynamic libraries")
endif(POCO_STATIC)

if (ENABLE_TESTS)
  include(CTest)
  enable_testing()
  message(STATUS "Building with unittests & samples")
else ()
  message(STATUS "Building without tests & samples")
endif ()

if (POCO_UNBUNDLED)
  add_definitions( -DPOCO_UNBUNDLED)
  message(STATUS "Build with using external sqlite, libz, pcre, expat ...")
else ()
  message(STATUS "Build with using internal copy of sqlite, libz, pcre, expat, ...")
endif ()

include(CheckTypeSize)
find_package(Cygwin)

# OS Detection
if(WIN32)
  add_definitions( -DPOCO_OS_FAMILY_WINDOWS -DUNICODE -D_UNICODE)
  #set(SYSLIBS iphlpapi gdi32 odbc32)
endif(WIN32)

if (UNIX AND NOT ANDROID )
  add_definitions( -DPOCO_OS_FAMILY_UNIX )
  # Standard 'must be' defines
  if (APPLE)
    add_definitions( -DPOCO_HAVE_IPv6 -DPOCO_NO_STAT64)
    set(SYSLIBS  dl)
  else (APPLE)
    add_definitions( -D_XOPEN_SOURCE=500 -D_REENTRANT -D_THREAD_SAFE -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64)
    set(SYSLIBS  pthread dl rt)
  endif (APPLE)
endif(UNIX AND NOT ANDROID )

if (CMAKE_SYSTEM MATCHES "SunOS")
  add_definitions( -DPOCO_OS_FAMILY_UNIX )
  # Standard 'must be' defines
  add_definitions( -D_XOPEN_SOURCE=500 -D_REENTRANT -D_THREAD_SAFE -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64 )
  set(SYSLIBS  pthread socket xnet nsl resolv rt dl)
endif(CMAKE_SYSTEM MATCHES "SunOS")

if (CMAKE_COMPILER_IS_MINGW)
  add_definitions(-DWC_NO_BEST_FIT_CHARS=0x400  -DPOCO_WIN32_UTF8)
  add_definitions(-mno-cygwin -D_WIN32 -DMINGW32 -DWINVER=0x500 -DODBCVER=0x0300 -DPOCO_THREAD_STACK_SIZE -DFoundation_Config_INCLUDED )
  link_directories(/usr/local/lib /usr/lib)
  include_directories(/usr/local/include /usr/include)
endif (CMAKE_COMPILER_IS_MINGW)

if (CYGWIN)
#    add_definitions(-DWC_NO_BEST_FIT_CHARS=0x400  -DPOCO_WIN32_UTF8)
endif (CYGWIN)

# SunPro C++
if (${CMAKE_CXX_COMPILER_ID} MATCHES "SunPro")
  add_definitions( -D_BSD_SOURCE -library=stlport4)
endif (${CMAKE_CXX_COMPILER_ID} MATCHES "SunPro")

# iOS
if (IOS)
  add_definitions( -DPOCO_HAVE_IPv6 -DPOCO_NO_FPENVIRONMENT -DPOCO_NO_STAT64 -DPOCO_NO_SHAREDLIBS -DPOCO_NO_NET_IFTYPES )
endif(IOS)

#Android
if (ANDROID)
  add_definitions( -DPOCO_ANDROID -DPOCO_NO_FPENVIRONMENT -DPOCO_NO_WSTRING -DPOCO_NO_SHAREDMEMORY )
endif(ANDROID)


# Collect the built libraries and include dirs, the will be used to create the PocoConfig.cmake file
set(Poco_COMPONENTS "")

if (ENABLE_TESTS)
   add_subdirectory(CppUnit)
endif ()

add_subdirectory(Foundation)
if(ENABLE_XML)
add_subdirectory(XML)
list(APPEND Poco_COMPONENTS "XML")
endif()
if(ENABLE_JSON)
add_subdirectory(JSON)
list(APPEND Poco_COMPONENTS "JSON")
endif()
if(ENABLE_MONGODB)
add_subdirectory(MongoDB)
list(APPEND Poco_COMPONENTS "MongoDB")
endif()
if(ENABLE_PDF)
add_subdirectory(PDF)
list(APPEND Poco_COMPONENTS "PDF")
endif()
if(ENABLE_UTIL)
add_subdirectory(Util)
list(APPEND Poco_COMPONENTS "Util")
endif()
if(ENABLE_NET)
add_subdirectory(Net)
list(APPEND Poco_COMPONENTS "Net")
endif()


#NetSSL


if(WIN32 AND ENABLE_NETSSL_WIN)
    add_subdirectory(NetSSL_Win)
    list(APPEND Poco_COMPONENTS "NetSSL_Win")
endif(WIN32 AND ENABLE_NETSSL_WIN)

find_package(OpenSSL)
if(OPENSSL_FOUND)
    include_directories("${OPENSSL_INCLUDE_DIR}")
    if(ENABLE_NETSSL)
    add_subdirectory(NetSSL_OpenSSL)
    list(APPEND Poco_COMPONENTS "NetSSL_OpenSSL")
    endif()
    if(ENABLE_CRYPTO)
    add_subdirectory(Crypto)
    list(APPEND Poco_COMPONENTS "Crypto")
    endif()
endif(OPENSSL_FOUND)

if(ENABLE_DATA)
add_subdirectory(Data)
list(APPEND Poco_COMPONENTS "Data")
endif()
if(ENABLE_SEVENZIP)
add_subdirectory(SevenZip)
list(APPEND Poco_COMPONENTS "SevenZip")
endif()
if(ENABLE_ZIP)
add_subdirectory(Zip)
list(APPEND Poco_COMPONENTS "Zip")
endif()

find_package(APR)
find_package(Apache2)
if(APRUTIL_FOUND AND APACHE_FOUND)
    include_directories( "${APACHE_INCLUDE_DIR}" "${APRUTIL_INCLUDE_DIR}" )
    if(ENABLE_APACHECONNECTOR)
    add_subdirectory(ApacheConnector)
    list(APPEND Poco_COMPONENTS "ApacheConnector")
    endif()
endif(APRUTIL_FOUND AND APACHE_FOUND)

if(ENABLE_CPPPARSER)
add_subdirectory(CppParser)
list(APPEND Poco_COMPONENTS "CppParser")
endif()

if(ENABLE_POCODOC)
add_subdirectory(PocoDoc)
list(APPEND Poco_COMPONENTS "PocoDoc")
endif()

if(ENABLE_PAGECOMPILER)
add_subdirectory(PageCompiler)
list(APPEND Poco_COMPONENTS "PageCompiler")
endif()

if(ENABLE_PAGECOMPILER_FILE2PAGE)
add_subdirectory(PageCompiler/File2Page)
list(APPEND Poco_COMPONENTS "File2Page")
endif()

#############################################################
# Uninstall stuff see: http://www.vtk.org/Wiki/CMake_FAQ
configure_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake/cmake_uninstall.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
  IMMEDIATE @ONLY)

add_custom_target(uninstall
  "${CMAKE_COMMAND}" -P "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake")

#############################################################
# Enable packaging

include(InstallRequiredSystemLibraries)

set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Poco Libraries")
set(CPACK_PACKAGE_VENDOR "Applied Informatics Software Engineering GmbH")
set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/README")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "/usr/local")

include(CPack)

#############################################################
# cmake config files 

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}/${PROJECT_NAME}ConfigVersion.cmake"
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY AnyNewerVersion
)

configure_file(cmake/${PROJECT_NAME}Config.cmake.in "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}/${PROJECT_NAME}Config.cmake" @ONLY)
install(
    FILES
        ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}/${PROJECT_NAME}Config.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}/${PROJECT_NAME}ConfigVersion.cmake
    DESTINATION
        "lib/cmake/${PROJECT_NAME}"
    COMPONENT
        Devel
)

# in tree build settings
#configure_file(PocoBuildTreeSettings.cmake.in ${CMAKE_CURRENT_BINARY_DIR}/PocoBuildTreeSettings.cmake @ONLY)


message(STATUS "CMake ${CMAKE_VERSION} successfully configured ${PROJECT_NAME} using ${CMAKE_GENERATOR} generator")
message(STATUS "Installation target path: ${CMAKE_INSTALL_PREFIX}")

message(STATUS "C_FLAGS:  =${CMAKE_C_FLAGS}")
message(STATUS "CXX_FLAGS:=${CMAKE_CXX_FLAGS}")

foreach(component ${Poco_COMPONENTS})
message(STATUS "Building: ${component}")
endforeach()

