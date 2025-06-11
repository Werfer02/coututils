cmake_minimum_required(VERSION 3.10.0)
project(coututils VERSION 0.1.0 LANGUAGES C CXX)

add_library(coututils coututils/coututils.cpp)

target_include_directories(coututils PUBLIC coututils)

add_executable(coututilsdemo main.cpp)

target_link_libraries(coututilsdemo PRIVATE coututils)

target_include_directories(coututilsdemo PRIVATE coututils)