cmake_minimum_required (VERSION 2.6)

add_executable(testFrontendIntegration test.cpp)

add_test(FrontendIntegration testFrontendIntegration)