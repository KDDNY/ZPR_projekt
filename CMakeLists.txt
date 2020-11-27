cmake_minimum_required(VERSION 3.16.3)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17") # enable C++11 standard

project(untitled1)


find_package(wxWidgets REQUIRED COMPONENTS net core base)
include(${wxWidgets_USE_FILE})


add_executable(main main.cpp
        classes/testedClass.h
        classes/Application.cpp
        classes/Application.h
        classes/Profile.cpp
        classes/Profile.h
        classes/Directory.cpp
        classes/Directory.h
        classes/LocalDirectory.cpp
        classes/LocalDirectory.h
        classes/File.cpp
        classes/File.h
        classes/Visitor.h
        classes/ScannerVisitor.cpp
        classes/ScannerVisitor.h
        "GUI classes/StartFrame.cpp"
        "GUI classes/StartFrame.h"
        "GUI classes/MainFrame.cpp"
        "GUI classes/MainFrame.h"
        "GUI classes/ProfileDialog.cpp"
        "GUI classes/ProfileDialog.h")
target_link_libraries(main ${wxWidgets_LIBRARIES})

