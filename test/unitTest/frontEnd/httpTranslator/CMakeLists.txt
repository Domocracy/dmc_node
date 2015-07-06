cmake_minimum_required (VERSION 2.6)

add_executable(testHttpTranslator test.cpp ${CMAKE_SOURCE_DIR}/src/code/frontEnd/HttpTranslator.cpp)
target_include_directories(testHttpTranslator PUBLIC ${CMAKE_SOURCE_DIR}/lib/poco/Foundation/include ${CMAKE_SOURCE_DIR}/lib/poco/Net/include ${CMAKE_SOURCE_DIR}/lib/cjson/src)
target_link_libraries(testHttpTranslator LINK_PUBLIC PocoNet PocoFoundation)

add_test(HttpTranslatorUnit testHttpTranslator)