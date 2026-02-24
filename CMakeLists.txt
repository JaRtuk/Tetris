cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

set(PROJECT_NAME Tetris)

project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE SOURCE_FILES
  source/*.cpp
  source/*.c
  source/*.h
  source/*.hpp
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

set (GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set (GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE) 
set (GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set (GLFW_INSTALL OFF CACHE BOOL "" FORCE)

set(GLFW_BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glfw)
target_link_libraries(${PROJECT_NAME} glfw)

add_subdirectory(external/glad)
target_link_libraries(${PROJECT_NAME} glad)

target_include_directories(${PROJECT_NAME}
  PRIVATE
    external/glfw/include
    external/glad/include
)

set_target_properties(${PROJECT_NAME}  PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${CMAKE_SOURCE_DIR}/resurses $<TARGET_FILE_DIR:${PROJECT_NAME}>/resurses)

