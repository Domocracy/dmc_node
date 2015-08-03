cmake_minimum_required (VERSION 2.6)

add_executable(testUpnpDriver test.cpp ${CMAKE_SOURCE_DIR}/src/code/backEnd/deviceDrivers/UpnpDriver.cpp)
target_include_directories(testUpnpDriver PUBLIC ${CMAKE_SOURCE_DIR}/lib/poco/Net/include
													${CMAKE_SOURCE_DIR}/lib/poco/Foundation/include)
			
target_link_libraries(testUpnpDriver LINK_PUBLIC PocoNet PocoFoundation)
			
add_test(UpnpDriverUnit testUpnpDriver )
