cmake_minimum_required(VERSION 3.10.2)
project(DMCcpp)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(DMCcpp
        inDMC.cpp
        inDMC.h
        main.cpp
        outDMC.cpp
        outDMC.h
        runDMC.cpp
        runDMC.h)
