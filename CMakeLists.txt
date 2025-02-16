cmake_minimum_required(VERSION 3.5.0)
project(Shell VERSION 0.1.0 LANGUAGES C)

file(GLOB SRC "src/*.c")

add_executable(Shell ${SRC})

