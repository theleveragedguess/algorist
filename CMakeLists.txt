cmake_minimum_required(VERSION 3.8)
set(CMAKE_CXX_STANDARD 17)

project(algorist)

include_directories("${PROJECT_SOURCE_DIR}")

set(
    SOURCE
    algorist.cpp
    common/combinatorics.cpp
    practical_alorithm_design/1_introduction_to_algorithm_design/programs.cpp
)

add_executable(${PROJECT_NAME} ${SOURCE})
