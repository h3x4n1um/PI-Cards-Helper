cmake_minimum_required(VERSION 3.12)
project(PI_Cards_Helper)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(PI_Cards_Helper
        json.hpp
        main.cpp
        PI.h
        RTON.cpp)
