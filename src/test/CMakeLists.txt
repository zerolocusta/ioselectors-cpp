cmake_minimum_required(VERSION 3.6)
set (CMAKE_CXX_STANDARD 11)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})


set(HEADER_INCLUDE_DIRS
    ./
    ../)

set(SOURCE_FILES
    ../DefaultSelector.cc
    ../EpollSelector.cc
    testAllSelector.cc
    testEpollSelector.cc
    )

include_directories(${HEADER_INCLUDE_DIRS})
add_executable(runTests ${SOURCE_FILES})
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)