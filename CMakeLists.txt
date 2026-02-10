cmake_minimum_required(VERSION 3.20)

project(kafka_cpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(kafka
    src/main.cpp
    src/server.cpp
)

target_include_directories(kafka PRIVATE include)

target_compile_options(kafka PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)
