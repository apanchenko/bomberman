cmake_minimum_required(VERSION 3.0.0)
project(bomberman VERSION 0.1.0 LANGUAGES CXX)

# link with sdl2 library
set(SDL_STATIC ON CACHE BOOL "" FORCE)
set(SDL_SHARED OFF CACHE BOOL "" FORCE)
add_subdirectory(libs/SDL-mirror)

# target executable
cmake_policy(SET CMP0076 NEW)
add_executable(bomberman WIN32 "")
add_subdirectory(src)

# use modern C++ standard
set_target_properties(bomberman PROPERTIES
  CXX_STANDARD 17
  CXX_EXTENSIONS ON)

target_include_directories(bomberman PRIVATE src)

target_link_libraries(bomberman SDL2-static) # SDL2main SDL2-static

# copy resulting executable into root folder for convenience
#set_target_properties(bomberman PROPERTIES
#  RUNTIME_OUTPUT_DIRECTORY_DEBUG ..
#  RUNTIME_OUTPUT_DIRECTORY_RELEASE ..)