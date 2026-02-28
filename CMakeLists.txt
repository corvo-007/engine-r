cmake_minimum_required(VERSION 3.31)
project(EngineR)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(OpenGL REQUIRED)
find_package(SDL2 REQUIRED)

option(EngineR_build_tests "Build test files" OFF)
option(enginem_build_tests "Build test files" OFF)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_subdirectory(lib/engine-m)
add_subdirectory(lib/glfw)

add_executable(EngineR ${SOURCES} lib/glad/src/glad.c)

target_include_directories(EngineR PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/engine-m/include
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/glad/include
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/glfw/include
)

target_link_libraries(EngineR PRIVATE enginem glfw OpenGL::GL SDL2::SDL2)
