# Culinary Collection: Dynamic Recursive Menu

A web project demonstrating a multi-level navigation system that generates menus and submenus dynamically from a JavaScript data structure.

## Project Structure

*   **main.html** — The primary landing page for "Home Cooking," featuring a sidebar that links to the breakfast menu.
*   **menu.html** — The interactive menu page. It serves as a container for the dynamic navigation bar.
*   **JavaScript (Embedded)** — Logic within `menu.html` that parses a nested array (`MenuA`) to build the UI on the fly.

## Key Features

### 1. Recursive Menu Generation
The system uses a recursive function `ShowMenu()` to handle an unlimited depth of submenus. If a menu item contains a `submenu` property, the script automatically creates a new nested level.

### 2. Intelligent Positioning
*   **Top-level:** Displays items horizontally across the main bar.
*   **Sub-levels:** Automatically calculates coordinates to display nested lists to the right or below the parent item, ensuring a clean dropdown/flyout effect.

### 3. Event-Driven Interaction
*   **Click-to-Expand:** Submenus appear upon clicking parent categories (e.g., "Kashas" -> "Sweet").
*   **Auto-Cleanup:** Clicking outside the menu or on different branches automatically closes irrelevant open submenus to prevent UI clutter.

## Technologies

*   **HTML5 / CSS3** — Absolute and relative positioning for complex layout management.
*   **JavaScript (DOM API)** — `getBoundingClientRect()` for precise positioning and dynamic element creation.

## How to Use

1.  Open `main.html` and click the **"Завтраки" (Breakfasts)** link.
2.  On the menu page, click on categories like **"Каши"** or **"Напитки"**.
3.  Explore the nested submenus (e.g., *Каши -> Молочные -> Рисовая*).
