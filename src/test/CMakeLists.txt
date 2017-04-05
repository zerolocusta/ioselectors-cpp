cmake_minimum_required(VERSION 3.6)
PROJECT(selector)

set (CMAKE_CXX_STANDARD 11)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})


set(HEADER_INCLUDE_DIRS
    ./
    ./utils/
    ../
    )

set(EpollSelectorUnitTest_SOURCE_FILES
    ../EpollSelector.cc
    EpollSelectorUnitTest.cc
    )

include_directories(${HEADER_INCLUDE_DIRS})
add_executable(EpollSelectorUnitTest ${EpollSelectorUnitTest_SOURCE_FILES})
target_link_libraries(EpollSelectorUnitTest ${GTEST_LIBRARIES} pthread)