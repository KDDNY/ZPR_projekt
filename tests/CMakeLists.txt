cmake_minimum_required(VERSION 3.17)
project(tests)

find_package(wxWidgets REQUIRED COMPONENTS net core base)
include(${wxWidgets_USE_FILE})
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
find_package(libssh REQUIRED)
if (NOT TARGET ssh)
    add_library(ssh SHARED IMPORTED)
    set_target_properties(ssh
            PROPERTIES
            ​          IMPORTED_LOCATION "${LIBSSH_LIBRARIES}"
            INTERFACE_INCLUDE_DIRECTORIES "${LIBSSH_INCLUDE_DIR}")
endif()
find_package(OpenSSL REQUIRED)

set(CMAKE_CXX_STANDARD 17)

add_executable(tests main.cpp
        ../classes/Application.cpp
        ../classes/Application.h
        ../classes/Dir.cpp
        ../classes/Dir.h
        ../classes/Profile.cpp
        ../classes/Profile.h
        ../classes/Visitor.h
        ../classes/File.cpp
        ../classes/File.h
        ../classes/Scanner.h
        ../classes/Scanner.cpp
        ../classes/FileCommandFactory.h
        ../classes/FileCommandFactory.cpp
        ../classes/FileCommand.h
        ../classes/FileCommand.cpp
        ../classes/SshConnector.cpp
        ../classes/SshConnector.h
        "../GUI classes/StartFrame.cpp"
        "../GUI classes/StartFrame.h"
        "../GUI classes/MainFrame.cpp"
        "../GUI classes/MainFrame.h"
        "../GUI classes/ProfileDialog.cpp"
        "../GUI classes/ProfileDialog.h"
        ApplicationTests.cpp
        ProfileTests.cpp
        DirTests.cpp
        )
target_link_libraries(tests ${wxWidgets_LIBRARIES} ${GTEST_LIBRARIES} pthread ssh OpenSSL::Crypto)
