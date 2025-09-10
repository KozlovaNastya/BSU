# Bulls and Cows Game (Qt Application)

## Overview
This is a desktop implementation of the classic **Bulls and Cows** (in Russian: *Быки и Коровы*) game built with **Qt**.  
The program generates a random **4-digit number with unique digits**. The player must guess the number, and after each attempt, the program shows the number of **bulls** (correct digits in the correct position) and **cows** (correct digits in the wrong position).  

The application also includes a **records system** that stores the top 10 best results (fewest attempts). Records are persisted in a local text file.


## Features
- Randomly generates a 4-digit secret number (first digit is never 0, all digits are unique).
- Game log with all attempts displayed in a table.
- Validation of input (only 4 digits allowed).
- Records system:
  - Saves player name and number of attempts.
  - Sorted automatically (best results first).
  - Keeps only top 10 scores.
  - Records persist across sessions (`records.txt`).
- Simple and intuitive Qt Widgets UI.
- Auto-save records on exit.


## Project Structure

```
├── main.cpp # Application entry point
├── mainwindow.cpp # Main game logic and UI handling
├── mainwindow.h # MainWindow class definition
├── records.cpp # Records dialog implementation
├── records.h # Records dialog header
├── ui_mainwindow.h # Generated UI header for main window
├── ui_records.h # Generated UI header for records dialog
├── records.txt # Persistent storage of high scores
```

## Requirements
- **Qt 5/6** (Core, Widgets, GUI modules)
- **C++17** or newer
- Build system: `qmake` or `CMake`

## How to Play
1. Launch the game.
2. Press Start to generate a new secret number.
3. Enter a 4-digit guess into the input field.
   - Only digits are allowed.
   - Must be exactly 4 characters.
4. Press Check → The result is shown:
   - Bulls = correct digits in correct positions.
   - Cows = correct digits but wrong positions.
5. The game continues until you guess all 4 digits (4 bulls → Victory).
6. On victory:
   - Enter your name to save the score in the records table.
   - The score (number of attempts) is saved to records.txt.
  
## Records System
- Accessible via the Records button.
- Displays top 10 scores (fewest attempts).
- Stored in a plain text file:
  ``` attempts player_name ```
- Example:
```
5 Alice
7 Bob
8 Charlie
```

## 🛠 Future Improvements
- Add difficulty levels (different number lengths).
- Timer for speed-based records.
- Online leaderboard integration.
- Dark mode support.
