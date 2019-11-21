cmake_minimum_required(VERSION 3.10)
project(madproto-sample)

include_directories(${CMAKE_SOURCE_DIR}/../src)

add_executable(${PROJECT_NAME} main.cpp ${CMAKE_SOURCE_DIR}/../src/mproto.c)
