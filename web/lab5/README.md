# Culinary Collection & Dynamic Recipe Form

An expanded web project that features a responsive recipe catalog and a sophisticated, configuration-driven form for adding new recipes with real-time validation.

## Project Structure

*   **index.html** — The main "Home Cooking" landing page. It uses a flexible block layout (Flexbox) and serves as the navigation hub, including a link to the contribution form.
*   **form.html** — A dedicated page for recipe submission containing an empty form container populated dynamically by JavaScript.
*   **form.js** — The engine behind the form. It reads a configuration array to build DOM elements and handles field-level validation logic.

## Key Features

### 1. Dynamic Form Generation
Instead of hardcoding HTML inputs, the form is generated programmatically from the `FormConfig` array. This makes it easy to add or remove fields (text, numbers, checkboxes) without touching the HTML file.

### 2. Intelligent Validation
*   **Real-time Checks:** Validates fields immediately when the user moves to the next input (`blur` event).
*   **Constraint Enforcement:** Ensures "Required" fields aren't empty and checks specific logic (e.g., Difficulty must be between 1 and 5).
*   **Visual Feedback:** Displays red error messages next to invalid fields and blocks submission until all data is correct.

### 3. Responsive Navigation
The main site features a sidebar menu with a clean layout that links all sections of the collection, including the new "Add Recipe" functionality.

## Technologies

*   **HTML5 / CSS3** — Flexbox-based layout and semantic structure.
*   **JavaScript (ES6)** — DOM Manipulation, Event Listeners, and configuration-based UI rendering.

## How to Use

1.  Open `index.html` to browse existing content.
2.  Navigate to **"Добавить рецепт"** (Add Recipe) via the sidebar.
3.  Fill out the form. Try leaving a field blank or entering a difficulty of "10" to see the **validation system** in action.
4.  The form will only allow submission once all errors are resolved.
