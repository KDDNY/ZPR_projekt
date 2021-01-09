cmake_minimum_required(VERSION 3.16.3)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17") # enable C++17 standard

project(untitled1)


find_package(wxWidgets REQUIRED COMPONENTS net core base)
find_package(libssh REQUIRED)
if (NOT TARGET ssh)
    add_library(ssh SHARED IMPORTED)
    set_target_properties(ssh
            PROPERTIES
            ​          IMPORTED_LOCATION "${LIBSSH_LIBRARIES}"
            INTERFACE_INCLUDE_DIRECTORIES "${LIBSSH_INCLUDE_DIR}")
endif()
include(${wxWidgets_USE_FILE})


add_executable(main main.cpp
        classes/Application.h
        classes/Dir.cpp
        classes/Dir.h
        classes/Profile.cpp
        classes/Profile.h
        classes/Visitor.h
        classes/SshConnector.h
        classes/SshConnector.cpp
        "GUI classes/StartFrame.cpp"
        "GUI classes/StartFrame.h"
        "GUI classes/MainFrame.cpp"
        "GUI classes/MainFrame.h"
        "GUI classes/ProfileDialog.cpp"
        "GUI classes/ProfileDialog.h"
        classes/Application.cpp
        classes/File.cpp
        classes/File.h
        classes/Scanner.cpp
        classes/Scanner.h classes/FileCommandFactory.cpp classes/FileCommandFactory.h classes/FileCommand.cpp classes/FileCommand.h)
target_link_libraries(main ${wxWidgets_LIBRARIES} ssh)


