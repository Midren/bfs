cmake_minimum_required(VERSION 3.14)
project(rpc)

set(CMAKE_CXX_STANDARD 14)

add_executable(rpc main.cpp rpc.cpp rpc.h)