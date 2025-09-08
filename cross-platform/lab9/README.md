# Dot Chart Graph

This project implements a **Qt-based desktop application** that visualizes integer data points as a smooth line chart with dots and labels. The core visualization is provided by a custom **DotChart widget**, and the **MainWindow** integrates it with menus, file operations, and customization features. 

Data is initially loaded from a resource file (`:/data/data.txt`), but users can also open their own `.txt` files with integer values.

## Features
**Custom DotChart Widget** 
  - Smooth cubic curve connecting data points
  - Dots with numeric label
  - Axes with ticks and labels
  - Context menu for pen width (1px, 2px, 3px)

**MainWindow Integration**
  - Open `.txt` data files
  - Save chart as PNG/JPEG image
  - Close chart and reset state
  - Change pen color and style (Solid, Dash, Dot)
  - Change brush (dot fill) color
  - Status bar showing file name, pen width, color, and style
  - About dialog with author information

**Data Validation**: 
  - only non-negative integers are allowed

## Project Structure
├── dotchart.cpp       
├── dotchart.h         
├── loadData.cpp       
├── loadData.h         
├── main.cpp           
├── mainwindow.cpp     
├── mainwindow.h       
├── data.txt           
└── resources.qrc      
## Requirements
  - **Qt 5/6** (Widgets, Core, GUI modules)
  - **C++17** or later
  - **Build system**: qmake or CMake
## Usage
  1. Run the application → chart displays dataset from `data.txt`.
  2. Use the **File menu** to:
    - Open `.txt` file with space-separated integers
    - Save chart as PNG/JPEG image
    - Close chart or exit app
  3. Use the **Pen menu** to:
     - Change color
     - Switch style (Solid, Dash, Dot)
     - Adjust width via right-click context menu
  4. Use the **Brush menu** to change the dot fill color.
  5. Check the **status bar** for current file, pen, and brush settings.
  6. Use the **Help → About** dialog for author information.
## Future Improvements
  - Add support for negative values with symmetric Y-axis
  - Interactive zoom and pan
  - Export data to CSV
  - Advanced styling (gradient brushes, marker shapes)
