cmake_minimum_required(VERSION 2.8)
project(common)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

add_subdirectory(test)
aux_source_directory(src DIR_SRC)
include_directories(./include)

link_libraries("pthread")
add_library(common ${DIR_SRC})
install(DIRECTORY include/ DESTINATION include/common/)
#include/ will install include/*, result si include/common/*.h
#include will install include, result si include/common/include
#install(DIRECTORY include DESTINATION include/common/)
install(TARGETS common DESTINATION lib/)
