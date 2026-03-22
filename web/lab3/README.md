# Culinary Collection & Dish Management System

A simple web project consisting of an information page with recipes and an interactive interface for managing a dish database (client-side storage).

## Project Structure

*   **main.html** — The "Home Cooking" information page. Includes recipe examples, a navigation menu, and a responsive layout using Flexbox and Media Queries.
*   **index.html** — The Control Panel. A button-based interface to interact with the dish database via JavaScript.
*   **script.js** — Application logic. Contains functions to add, delete, search, and list dishes.

## Features

The project allows managing a list of dishes in the browser's memory:
1.  **Add:** Save a dish name along with its cooking time.
2.  **Delete:** Remove a dish from the list by its name.
3.  **Search:** Retrieve detailed information about a specific dish.
4.  **View List:** Display all saved records in a single alert window.

## Technologies

*   **HTML5** — Semantic markup.
*   **CSS3** — Styling and mobile responsiveness.
*   **JavaScript (ES6)** — Working with objects and `prompt/alert` dialog boxes.

## How to Use

1.  Open `main.html` in your browser to view the main culinary collection interface.
2.  Open `index.html` to use the management functions.
    *   *Note: Data is stored in the `dishesStorage` object and will be reset if the page is refreshed.*
