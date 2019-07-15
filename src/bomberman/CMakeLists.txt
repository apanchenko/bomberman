add_subdirectory(actors)
add_subdirectory(types)

target_sources(bomberman
    PRIVATE
        Game.cpp
        Game.h
        main.cpp)