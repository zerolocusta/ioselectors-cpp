cmake_minimum_required(VERSION 3.6)

PROJECT(selector)

set (CMAKE_CXX_STANDARD 11)



set(HEADER_DIRECTORIES
    ..
    )

set(PackedMessageUnitTest_SOURCE_FILES
    UtilsUnitTest.cc
    ../Utils.cc
    )

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${HEADER_DIRECTORIES})


add_executable(TestUtils ${PackedMessageUnitTest_SOURCE_FILES})
target_link_libraries(TestUtils ${GTEST_LIBRARIES} pthread)