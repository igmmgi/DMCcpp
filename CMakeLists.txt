cmake_minimum_required(VERSION 3.10.2)
project(DMCcpp)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(dmcSim
  inDMC.cpp
  inDMC.h
  main.cpp
  outDMC.cpp
  outDMC.h
  runDMC.cpp
  runDMC.h)

