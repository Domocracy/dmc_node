cmake_minimum_required (VERSION 2.6)

add_executable(testUpnpDriver test.cpp ${CMAKE_SOURCE_DIR}/src/code/backEnd/deviceDrivers/UpnpDriver.cpp ${CMAKE_SOURCE_DIR}/src/code/backEnd/deviceDrivers/upnp/SddpParser.cpp ${CMAKE_SOURCE_DIR}/src/code/backEnd/deviceDrivers/upnp/UpnpDevice.cpp)
target_include_directories(testUpnpDriver PUBLIC 	${CMAKE_SOURCE_DIR}/lib/poco/Net/include
													${CMAKE_SOURCE_DIR}/lib/poco/Foundation/include
													${CMAKE_SOURCE_DIR}/lib/poco/XML/include
													${CMAKE_SOURCE_DIR}/lib/cjson/src)
			
target_link_libraries(testUpnpDriver LINK_PUBLIC cjson PocoNet PocoFoundation)
			
add_test(UpnpDriverUnit testUpnpDriver )
