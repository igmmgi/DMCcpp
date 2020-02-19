cmake_minimum_required(VERSION 3.10.2)
project(DMCcpp)

find_package(Threads)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE Release)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

include_directories(include)

add_executable(dmcSim src/dmcSim.cpp src/inDMC.cpp src/outDMC.cpp src/runDMC.cpp)
target_link_libraries( dmcSim ${CMAKE_THREAD_LIBS_INIT} )

