cmake_minimum_required(VERSION 2.8)
project(SpinLock)

# 生成静态库
add_library(spinlock rw_mutex.cpp)

add_compile_options(-std=c++11)
