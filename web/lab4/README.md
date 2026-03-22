# Culinary Collection & Dish Management System (OOP Version)

A web-based dish management system utilizing an Object-Oriented Programming (OOP) approach to handle recipe data within a custom hash storage class.

## Project Structure

*   **main.html** — The "Home Cooking" information page. Features recipe examples, a navigation menu, and a responsive layout (Flexbox/Media Queries).
*   **index.html** — The Control Panel. An interactive interface that triggers JavaScript methods to manage the dish database.
*   **script.js** — The core logic. Implements the `THashStorage` class using private fields (`#dishesStorage`) and encapsulates data management methods.

## Features

The system uses a dedicated class instance (`dishStorage`) to manage data:
1.  **Encapsulated Storage:** Uses a private class field to prevent direct external modification of the data.
2.  **Add Dish:** Prompts for a dish name and cooking time, saving them into the hash-map.
3.  **Delete Dish:** Removes a specific entry by its key (dish name).
4.  **Information Retrieval:** Returns formatted strings for specific dishes or a complete list of all entries.
5.  **Console Logging:** The full list of dishes is output directly to the browser's developer console.

## Technologies

*   **HTML5 / CSS3** — Semantic structure and responsive design.
*   **JavaScript (ES6+)** — Advanced OOP features including **Classes**, **Private Class Fields** (`#`), and **Encapsulation**.

## How to Use

1.  Open `main.html` for the visual recipe guide.
2.  Open `index.html` to access the management tools.
3.  Click "Перечень всех блюд" (List all dishes) and **open your Browser Console (F12)** to see the output.
    *   *Note: As an in-memory storage, all data is cleared when the page is refreshed.*
