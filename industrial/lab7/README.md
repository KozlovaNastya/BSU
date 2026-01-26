# Parking Management System

## Description
This project implements a parking management system with file-based data storage, indexing, search, deletion, file compaction, and both **console** and **GUI (Swing)** interfaces.

The system is written in **Java** and demonstrates working with `RandomAccessFile`, object serialization, indexing, and desktop UI development.

## Project Structure
```
Program7/
├── parking.java
├── ParkingFileManager.java
├── ParkingIndex.java
├── ParkingMenu.java
├── ParkingGUI.java
└── parking_data.dat
```

## Core Components

### `parking`
Serializable data model representing a parking record:
- car number
- owner full name (FIO)
- start/end date and time
- price per hour
- automatic parking duration calculation

Validation rules:
- Date format: `dd.MM.yyyy`
- Time format: `HH:mm`
- Full name must contain exactly three parts

### `ParkingFileManager`
Handles low-level file operations using `RandomAccessFile`:
- add records
- sequential read
- indexed search
- logical deletion
- file compaction (physical removal of deleted records)
- index rebuild and persistence

Supported operations:
- search by number
- search numbers greater / less than given value
- delete by number
- clear all data
- rebuild index

### `ParkingIndex`
Index implementation based on `TreeMap<Integer, Long>`:
- key: car number
- value: position in data file

Features:
- ascending / descending sorting
- range queries
- serialization to `.index` file

### `ParkingMenu`
Console-based user interface:
- test data generation
- record listing
- searching and sorting
- deletion
- index status display

Useful for testing without GUI.

### `ParkingGUI`
Swing-based graphical interface:
- data input form
- menu-driven operations
- search and delete dialogs
- text output area
- file operations

Supports all core system features.

## Data Storage
- Main data file: `parking_data.dat`
- Index file: `parking_data.dat.index`
- Format: binary (serialized objects)
- Deletion strategy: logical deletion using a marker (`-1`)


## Features
- Indexed access for fast search
- Persistent file-based storage
- Logical and physical deletion
- File compaction
- Console and GUI interfaces
- Robust input validation

## How to Run

### Console Version
```bash
java Program7.ParkingMenu
```

### GUI Version
```bash
java Program7.ParkingGUI
```
