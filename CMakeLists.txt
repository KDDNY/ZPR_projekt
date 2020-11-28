cmake_minimum_required(VERSION 3.17)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17") # enable C++11 standard

project(untitled1)



add_executable(main main.cpp classes/testedClass.h classes/Application.cpp classes/Application.h classes/Profile.cpp classes/Profile.h classes/File.cpp classes/File.h classes/Visitor.h classes/ScannerVisitor.cpp classes/ScannerVisitor.h classes/Command.cpp classes/Command.h classes/Dir.cpp classes/Dir.h)


