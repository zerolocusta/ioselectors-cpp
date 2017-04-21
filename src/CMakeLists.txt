cmake_minimum_required(VERSION 3.6)

PROJECT(selector)

set (CMAKE_CXX_STANDARD 11)



set(HEADER_DIRECTORIES
    .
    )

set(SOURCE_FILES
    DefaultSelector.cc
    EpollSelector.cc
    )
FIND_PACKAGE( Boost 1.55 COMPONENTS program_options REQUIRED )
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${HEADER_DIRECTORIES})
add_library(selector STATIC ${Boost_LIBRARIES} ${SOURCE_FILES})
