cmake_minimum_required(VERSION 3.10)
project(Tetris)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SOURCE_FILES
  source/*.cpp
  source/*.c
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})