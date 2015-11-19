cmake_minimum_required(VERSION 3.2)
project(common)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
LINK_LIBRARIES("pthread")

set(SOURCE_FILES
    include/cond_var.h
    include/mutex.h
    include/thread.h
    include/thread_pool.h
    test/test.cpp
    )

add_executable(common ${SOURCE_FILES})
