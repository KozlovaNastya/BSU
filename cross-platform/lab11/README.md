# ShapeCreator

## Overview
**ShapeCreator** is a mini paint application built with **Qt**.  
It allows you to draw and customize simple shapes such as **rectangles, circles, and lines**.  
You can adjust **color** and **pen width**, as well as **save** and **upload** your drawings.  
Additionally, the app supports **basic animation of figures**.

## Features
- Draw shapes: rectangle, circle, line.  
- Choose custom **colors**.  
- Adjust **pen width**.  
- Save drawings to an image file.  
- Upload images for editing.  
- Animate created figures.  


## Requirements
- **Qt 5/6** (Core, Widgets, GUI modules)  
- **C++17** or newer  


## Build Instructions
### Using qmake
```
bash
qmake
make
./ShapeCreator
```
### Using cmake
```
mkdir build && cd build
cmake ..
make
./ShapeCreator
```

## Usage

1. Select the shape tool (rectangle, circle, or line).
2. Choose color and pen width.
3. Draw on the canvas.
4. Use Save to export or Upload to load an image.
5. Optionally, animate shapes for dynamic effects.
