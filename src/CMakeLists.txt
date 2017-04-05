cmake_minimum_required(VERSION 3.6)

PROJECT(selector)

set (CMAKE_CXX_STANDARD 11)



set(HEADER_FILES 
    BaseSelector.h
    DefaultSelector.h
    EpollSelector.h
    )

set(SOURCE_FILES
    DefaultSelector.cc
    EpollSelector.cc
    )


add_library(selector STATIC ${HEADER_FILES} ${SOURCE_FILES})
add_subdirectory(test)