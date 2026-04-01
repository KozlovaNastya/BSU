# Culinary Book: AJAX-Powered SPA

An advanced Single Page Application (SPA) that loads content dynamically from external HTML files without refreshing the browser tab.

## Project Structure

*   **index.html** — The main application shell. Contains the global styles and the navigation engine.
*   **home.html** — Fragment file for the landing page content.
*   **recipes.html** — Fragment file containing the recipe database table.

## Key Features

### 1. Dynamic Content Fetching (AJAX)
The app uses the modern **Fetch API** with `async/await` syntax. Instead of hiding/showing hidden divs, it physically requests the content of `home.html` or `recipes.html` and injects it into the `#app` container.

### 2. True SPA Architecture
*   **Asynchronous Loading:** Only the necessary content is downloaded when needed, saving initial bandwidth.
*   **Error Handling:** Includes a `try...catch` block to notify the user if a page fails to load or a network error occurs.
*   **Initial State:** The `DOMContentLoaded` listener ensures the "Home" page is automatically loaded as soon as the shell is ready.

### 3. Modular Design
By separating content into standalone HTML fragments, the project remains organized and easy to scale. Adding a new section (like "Contacts") only requires creating a new `.html` file and calling `navigateTo('contacts')`.

## Technologies

*   **HTML5 / CSS3** — Core structure and modern UI styling.
*   **JavaScript (ES6+)** — **Asynchronous Fetch API**, DOM manipulation, and dynamic HTML injection.

## Important Note

Since this project uses **AJAX (fetch)**, it must be run through a **local web server** (like *Live Server* in VS Code) to avoid CORS policy restrictions when loading local files.

## How to Use

1.  Launch the project using a local server.
2.  The app will display "Загрузка приложения..." (Loading...) for a split second before injecting the home content.
3.  Click the buttons to swap between the **Landing Page** and the **Recipe List** seamlessly.
