cmake_minimum_required(VERSION 3.6)
set (CMAKE_CXX_STANDARD 11)

PROJECT(selector)


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