cmake_minimum_required(VERSION 3.20)
project(artemis LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# imgui & minhook includes
include_directories(
    ${CMAKE_SOURCE_DIR}/libraries/imgui
    ${CMAKE_SOURCE_DIR}/libraries/minhook
    ${CMAKE_SOURCE_DIR}/libraries
)

# link dirs for static libraries
link_directories(${CMAKE_SOURCE_DIR}/libraries/static)

# source files
file(GLOB_RECURSE SRC
    # GLOB_RECURSE tells cmake to scan everywhere within these things:
    ${CMAKE_SOURCE_DIR}/src/*.cpp
    # all of our source files
    ${CMAKE_SOURCE_DIR}/libraries/*.hpp
    # our dependencies
)

add_library(artemis SHARED ${SRC})

# win/ogl definitions
target_compile_definitions(artemis PRIVATE
    WIN32_LEAN_AND_MEAN
    # WIN32_LEAN_AND_MEAN just removes all super niche functions/variables that are unused or else it would be litered with random things
    NOMINMAX
)

# link things
target_link_libraries(artemis
    MinHook.x64.lib
    opengl32.lib
    user32.lib
    gdi32.lib
)
