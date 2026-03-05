# Alive Artform - Interactive Wave Simulation

> **Warning**: This project is a work in progress and very buggy. It was an early learning project for SDL2 and graphics programming in C++.
> On to better things, but immortalizing in the GitHub graveyard of projects nonetheless!

An interactive wave simulation art application built with SDL2 and C++23.

## Overview

Alive Artform simulates 120 strings using wave physics. Users can interact with the strings by clicking and dragging the mouse to "pluck" them, creating beautiful wave patterns.

## Building

```bash
meson setup build
meson compile -C ./build
```

## Running

```bash
./build/alive_artform
```

## Controls

- **Left mouse button**: Pluck the strings by clicking and dragging
- **Scroll wheel**: Adjust the distance of the pluck effect
- Time step can be modified in `src/main.cpp`

## Requirements

- SDL2
- SDL2_ttf
- C++23 compatible compiler
- Meson build system

## Project Structure

- `src/main.cpp` - Application entry point
- `src/physics.cpp` - Wave physics simulation
- `src/event_handlers.cpp` - Input handling
- `src/constants.hpp` - Configuration constants
- `assets/` - Embedded font resources

## Customization

Edit constants in `src/constants.hpp` to adjust:

- Number of strings (`NUM_STRINGS`)
- Points per string (`N_POINTS`)
- Window dimensions (`WIDTH`, `HEIGHT`)

Or modify physics parameters in `src/main.cpp`:

- Wave speed (`CWAVE_SPEED`)
- Damping factor (`GAMMA`)
- Mouse strength (`MOUSE_STRENGTH_DISPLACEMENT`)
