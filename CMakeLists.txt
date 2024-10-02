cmake_minimum_required(VERSION 3.30 FATAL_ERROR)
project(ShadowFallEngine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3)

add_subdirectory(engine)
add_subdirectory(game)

add_subdirectory(testing)