cmake_minimum_required (VERSION 2.6)

add_executable(testRequestProcessor "test.cpp" ${CMAKE_SOURCE_DIR}/src/code/backEnd/RequestProcessors/CommandDispatcher.cpp)

add_test(RequestProcessorUnit testRequestProcessor)