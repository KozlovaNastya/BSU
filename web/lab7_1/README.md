# Culinary Book (SPA Version)

A lightweight Single Page Application (SPA) that provides a seamless user experience for browsing recipes without reloading the page.

## Project Structure

*   **index.html** — The monolithic file containing the layout (HTML), styles (CSS), and navigation logic (JavaScript).
*   **Single-File Architecture** — Combines all components into one document for fast loading and easy deployment.

## Key Features

### 1. Single Page Application (SPA) Logic
The application uses a custom `navigateTo()` function to swap content dynamically. It toggles the `active` class across different sections, simulating multi-page navigation instantly.

### 2. Smooth UI/UX
*   **CSS Animations:** Uses `@keyframes fadeIn` to create a smooth transition effect when switching between the Home screen and the Recipe list.
*   **Responsive Tables:** Organizes recipe data (ingredients and methods) into a clean, readable tabular format.
*   **Modern Styling:** Features a vibrant coral-to-peach color palette with rounded buttons and subtle drop shadows.

### 3. State Management
The interface tracks which "page" is currently visible by manipulating the DOM, removing the need for traditional server-side routing.

## Technologies

*   **HTML5** — Semantic sections (`<section>`) used as virtual pages.
*   **CSS3** — Custom animations, Flexbox-inspired centering, and advanced button transitions.
*   **JavaScript (ES6)** — DOM manipulation and event handling for the navigation engine.

## How to Use

1.  Open the file in any modern web browser.
2.  On the **Home** screen, click "Открыть книгу рецептов" (Open Recipe Book).
3.  The recipe table will appear with a smooth fade-in effect.
4.  Use the **"Вернуться назад"** (Go Back) button to return to the landing page instantly.
