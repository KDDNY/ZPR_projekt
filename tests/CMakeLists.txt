cmake_minimum_required(VERSION 3.17)
project(tests)

find_package(wxWidgets REQUIRED COMPONENTS net core base)
include(${wxWidgets_USE_FILE})
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 14)

add_executable(tests main.cpp
        ../classes/testedClass.h
        ../classes/Application.cpp
        ../classes/Application.h
        ../classes/Profile.cpp
        ../classes/Profile.h
        ../classes/Directory.cpp
        ../classes/Directory.h
        ../classes/LocalDirectory.cpp
        ../classes/LocalDirectory.h
        ../classes/File.cpp
        ../classes/File.h
        ../classes/Visitor.h
        ../classes/ScannerVisitor.cpp
        ../classes/ScannerVisitor.h
        "../GUI classes/StartFrame.cpp"
        "../GUI classes/StartFrame.h"
        "../GUI classes/MainFrame.cpp"
        "../GUI classes/MainFrame.h"
        "../GUI classes/ProfileDialog.cpp"
        "../GUI classes/ProfileDialog.h")
target_link_libraries(tests ${wxWidgets_LIBRARIES} ${GTEST_LIBRARIES} pthread)
