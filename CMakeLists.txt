cmake_minimum_required(VERSION 3.17)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17") # enable C++11 standard

project(untitled1)

add_subdirectory(lib/googletest)
include_directories(lib/googletest/googletest/include)
include_directories(lib/googletest/googlemock/include)

add_executable(main main.cpp classes/testedClass.h classes/Application.cpp classes/Application.h classes/Profile.cpp classes/Profile.h classes/Directory.cpp classes/Directory.h classes/LocalDirectory.cpp classes/LocalDirectory.h classes/File.cpp classes/File.h classes/Visitor.h classes/ScannerVisitor.cpp classes/ScannerVisitor.h)
target_link_libraries(main gtest gtest_main)

