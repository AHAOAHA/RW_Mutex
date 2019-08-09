cmake_minimum_required(VERSION 2.8)
project(rw_mutex)

# 生成静态库
add_library(rw_mutex rw_mutex.cpp)

add_compile_options(-std=c++11 -lpthread)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/spin_lock/src)

link_directories(${CMAKE_CURRENT_SOURCE_DIR}/spin_lock/src)
