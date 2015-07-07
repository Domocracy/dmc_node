cmake_minimum_required (VERSION 2.6)

add_executable(testFrontendIntegration test.cpp ${CMAKE_SOURCE_DIR}/src/code/frontEnd/LocalServer.cpp ${CMAKE_SOURCE_DIR}/src/code/frontEnd/RequestDispatcher.cpp ${CMAKE_SOURCE_DIR}/src/code/frontEnd/HTTPTranslator.cpp ${CMAKE_SOURCE_DIR}/src/code/frontEnd/Response.cpp)
target_include_directories(testFrontendIntegration PUBLIC ${CMAKE_SOURCE_DIR}/lib/poco/Net/include ${CMAKE_SOURCE_DIR}/lib/poco/Foundation/include ${CMAKE_SOURCE_DIR}/lib/cjson/src)
target_link_libraries(testFrontendIntegration LINK_PUBLIC PocoNet PocoFoundation)
target_link_libraries(testFrontendIntegration LINK_PUBLIC cjson)

add_test(FrontendIntegration testFrontendIntegration)