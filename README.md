# Cub3D - Raycasting Game Engine

A Wolfenstein 3D-inspired raycaster engine implementing the principles of ray-casting as described by John Carmack. Built from scratch in C with minimalist dependencies.

![Cub3D Demo](https://i.imgur.com/teuOvMq.jpg)

## 🧊 Overview

Cub3D recreates the groundbreaking pseudo-3D rendering technique that powered the first generation of FPS games. The engine uses ray-casting to create a 3D perspective from a 2D map, creating an immersive maze exploration experience.

This implementation follows the 42 school project requirements, featuring textured walls, sprite rendering, and collision detection—all executed with careful memory management and efficient rendering.

## ⚡ Features

### Core Features
- **Ray-casting Engine**: Custom-built renderer with precise distance calculations
- **Textured Environment**: Direction-specific wall textures (North, South, East, West)
- **Interactive Navigation**: Real-time movement with collision detection
- **Sprite System**: Rendering of 2D objects in 3D space
- **Dynamic View**: Camera rotation with varying perspective
- **Configurable Maps**: Custom level design through configuration files
- **Screenshot Capture**: Save rendered frames as BMP images

### Bonus Implementations
- **Minimap System**: Real-time top-down view for navigation assistance
- **Distance-based Shading**: Atmospheric depth effect for improved visual realism
- **Collision Detection**: Realistic physics preventing wall and sprite penetration
- **Look Controls**: Vertical camera adjustment for enhanced immersion

## 🔧 Technical Specifications

- **Language**: C
- **Graphics**: MinilibX
- **Memory Management**: Custom allocation system with leak prevention
- **Map Format**: Customizable .cub files with texture paths and map data
- **Architecture**: Modular code structure with separation of concerns
- **Performance**: Optimized rendering loop for smooth gameplay

## 📦 Installation

```bash
# Clone the repository
git clone https://github.com/abdurahim-H/Cub3D.git
cd cub3d

# Build the project
make

# Run with a map
./cub3D maps/test00.cub
or
./cub3D maps/test01.cub
or
./cub3D maps/test02.cub
or
./cub3D maps/test03.cub

#For Screenshot Capture
./cub3D maps/test00.cub --save
```


## 🎮 Controls

| Key | Action |
|-----|--------|
| `W` | Move forward |
| `S` | Move backward |
| `A` | Strafe left |
| `D` | Strafe right |
| `←` | Rotate camera left |
| `→` | Rotate camera right |
| `↑` | Look up (Currently disabled) |
| `↓` | Look down (CUrrently disabled) |
| `ESC` | Exit game |

## 🗺️ Map Configuration

Maps use the `.cub` extension with the following format:

```
R 1920 1080           # Resolution
NO ./path_to_north.xpm # North texture
SO ./path_to_south.xpm # South texture
WE ./path_to_west.xpm  # West texture 
EA ./path_to_east.xpm  # East texture
S ./path_to_sprite.xpm # Sprite texture
F 220,100,0           # Floor color (RGB)
C 225,30,0            # Ceiling color (RGB)

# Map (1=wall, 0=floor, 2=sprite, N/S/E/W=player start position and direction)
1 1 1 1 1 1 1 1 1 1 1
1 0 0 0 0 0 0 0 0 0 1
1 0 1 0 0 0 0 0 1 0 1
1 0 0 0 0 2 0 0 0 0 1
1 0 0 0 0 0 0 0 0 0 1
1 0 0 0 0 0 0 0 0 0 1
1 0 0 0 0 0 0 0 0 0 1
1 0 N 0 0 0 0 0 0 0 1
1 1 1 1 1 1 1 1 1 1 1
```

## 🧮 Core Algorithm

The ray-casting algorithm works by:

1. Casting rays from the player's position
2. Using DDA (Digital Differential Analysis) to find wall intersections
3. Calculating perpendicular distance to avoid fisheye effect
4. Determining wall height based on distance
5. Applying textures based on wall orientation and hit position
6. Rendering sprites from farthest to nearest using a Z-buffer

## 📸 Screenshots

### In-Game View
![Game View](https://i.imgur.com/PG87vJL.jpg)

### Texture Demonstration
![Textures](https://i.imgur.com/hYKbjIJ.jpg)

### Sprite Rendering
![Sprites](https://i.imgur.com/hLs8MCD.jpg)

## 🔬 Implementation Notes

- **Memory Management**: Custom wrappers prevent memory leaks
- **Error Handling**: Robust input validation and graceful error reporting
- **Texture Mapping**: Precise wall-hit calculation for accurate texture alignment
- **Performance**: Optimized rendering loop with minimal buffer flushing
- **Architecture**: Event-driven system with frame-based rendering

## 💻 Development Journey

This project started as an exploration of fundamental 3D rendering techniques that don't rely on hardware acceleration. The decision to focus on raycasting connects us with the roots of 3D game development while enforcing optimization principles and spatial reasoning that remain relevant in modern graphics programming.

Key development challenges included:
- Implementing accurate collision detection
- Managing performance with dynamic texture loading
- Creating intuitive depth perception without shader access
- Building an extensible architecture that supports further features

*This project is inspired by the revolutionary techniques pioneered by id Software in Wolfenstein 3D.*