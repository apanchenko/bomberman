cmake_minimum_required(VERSION 3.0.0)
project(bomberman VERSION 0.1.0 LANGUAGES CXX)

# define target executable
cmake_policy(SET CMP0076 NEW)
add_executable(bomberman WIN32 "")
add_subdirectory(bomberman)

# use modern C++ standard
set_target_properties(bomberman PROPERTIES
  CXX_STANDARD 17
  CXX_EXTENSIONS ON)

# setup include directories
target_include_directories(bomberman
  PRIVATE bomberman
  PRIVATE sdl2/include)

message(WARNING ${CMAKE_GENERATOR_PLATFORM})

# link with sdl2 library
add_library(sdl2 STATIC IMPORTED)

if (CMAKE_SIZEOF_VOID_P EQUAL 8)
  set_target_properties(sdl2 PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/sdl2/lib/x64/SDL2.lib)
else ()
  set_target_properties(sdl2 PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/sdl2/lib/x86/SDL2.lib)
endif ()

target_link_libraries(bomberman sdl2)

# copy resulting executable into root folder for convenience
set_target_properties(bomberman PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY_DEBUG ..
  RUNTIME_OUTPUT_DIRECTORY_RELEASE ..)
