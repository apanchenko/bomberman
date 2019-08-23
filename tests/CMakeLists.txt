project(tests VERSION 0.1.0 LANGUAGES CXX)

add_executable(tests "")

target_include_directories(tests PRIVATE ../libs)

target_sources(tests
    PRIVATE
        main.cpp
        test.cpp)