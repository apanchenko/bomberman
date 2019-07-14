# Bomberman

Clone of a well known [Bomberman](https://m.youtube.com/watch?v=3smytj9Bu_E) game written from scratch.

You are a yellow hero starting in top left corner.

- Press arrows to move
- Press 'Space' to drop bomb
- Press 'R' to add roaming foe
- Press 'C' to add chasing foe
- Press 'Esc' to exit.

Try to destroy all carton boxes while avoiding foes.

## How to Build

Install [CMake](https://cmake.org) and [Build Tools for Visual Studio](https://visualstudio.microsoft.com/downloads/), run then:

```bat
cmake -S src -B build
cmake --build build
```

## To do

- Tests
- Textures and animations
- Scores
- Sound effects
- Stage exit, start new stage
- Start menu screen
- Make project more data-driven

## Known issues

- Arrow and WASD keys work a little different with multiple hits

## Done

- Drop bombs
- Chasing foe
- Wandering foe
- Wall collisions
- Spawn controlled player
- Build maze
- Render colored rectangles
