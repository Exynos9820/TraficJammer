cmake_minimum_required(VERSION 3.16)
project(TraficJammer)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(raylib REQUIRED)

file(GLOB_RECURSE SOURCES src/*.cpp)

add_executable(TraficJammer ${SOURCES})

target_include_directories(TraficJammer PRIVATE include)
target_include_directories(TraficJammer PRIVATE include/Objects)
target_include_directories(TraficJammer PRIVATE include/Objects/Tree)

target_link_libraries(TraficJammer PRIVATE raylib)
