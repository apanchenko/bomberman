cmake_minimum_required(VERSION 3.0.0)
project(bomberman VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE app_src *.cpp)

add_executable(bomberman WIN32 ${app_src})

target_include_directories(bomberman PRIVATE ../libs/sdl2/include)
target_include_directories(bomberman PRIVATE .)

set_target_properties(bomberman PROPERTIES
  CXX_STANDARD 17
  CXX_EXTENSIONS ON)

target_link_libraries(bomberman ../libs/sdl2/lib/x64/SDL2)

set_target_properties(bomberman PROPERTIES
                      RUNTIME_OUTPUT_DIRECTORY_DEBUG ..
                      RUNTIME_OUTPUT_DIRECTORY_RELEASE ..)