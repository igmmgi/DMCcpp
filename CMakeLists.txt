cmake_minimum_required(VERSION 3.10.2)
project(DMCcpp)


set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE Release)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")


include_directories(include)
file(GLOB SOURCES "src/*.cpp")

add_executable(dmcSim ${SOURCES})

