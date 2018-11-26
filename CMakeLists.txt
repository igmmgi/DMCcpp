cmake_minimum_required(VERSION 3.10.2)
project(DMCcpp)

set(CMAKE_BUILD_TYPE Release)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

set(CMAKE_CXX_STANDARD 14)

add_executable(dmcSim
  inDMC.cpp
  inDMC.h
  main.cpp
  outDMC.cpp
  outDMC.h
  runDMC.cpp
  runDMC.h)

