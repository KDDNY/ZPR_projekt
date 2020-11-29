cmake_minimum_required(VERSION 3.17)
project(tests)

find_package(wxWidgets REQUIRED COMPONENTS net core base)
include(${wxWidgets_USE_FILE})
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 17)

add_executable(tests main.cpp
        ../classes/Application.h
        ../classes/Application.cpp)
target_link_libraries(tests ${wxWidgets_LIBRARIES} ${GTEST_LIBRARIES} pthread)
