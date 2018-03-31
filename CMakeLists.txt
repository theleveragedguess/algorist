cmake_minimum_required(VERSION 3.8)
set(CMAKE_CXX_STANDARD 17)

project(algorist)

include_directories("${PROJECT_SOURCE_DIR}")

set(
    SOURCE
    algorist.cpp
    common/combinatorics.cpp
    part_1/chapter_1/programs.cpp
)

add_executable(${PROJECT_NAME} ${SOURCE})
