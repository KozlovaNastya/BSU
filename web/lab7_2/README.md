# Culinary Book: AJAX-Powered SPA

A comprehensive web application that combines a Single Page Application (SPA) frontend with a Node.js/Express backend to manage, display, and download recipe data.

## Project Structure

*   **server.js** — The Node.js backend using **Express**. Handles static file serving and the secure file download route.
*   **index.html** — The application shell containing the global UI and the AJAX/Fetch logic.
*   **home.html & recipes.html** — Content fragments loaded dynamically into the main shell.
*   **data.json** — External data source containing additional recipe records.

## Key Features

### 1. Backend Integration (Node.js & Express)
The project now includes a real server environment. It serves the application and provides a dedicated endpoint (`/download-data`) that allows users to download the recipe database as a physical file using `res.download()`.

### 2. Dynamic JSON Data Injection
The `loadJsonData()` function demonstrates how to fetch raw JSON data asynchronously. It parses the object and dynamically builds an HTML table to inject into the "Home" page, showcasing **Client-Side Rendering (CSR)**.

### 3. Advanced AJAX Workflow
*   **HTML Fetching:** Swaps pages without reloads.
*   **JSON Fetching:** Pulls structured data from the server and transforms it into visual elements.
*   **Async/Await:** Clean, modern JavaScript for handling multiple network requests.

### 4. File Management
Users can export the collection. The "Download JSON" button triggers a backend route that sends the `data.json` file directly to the user's computer.

## Technologies

*   **Backend:** Node.js, Express.js.
*   **Frontend:** JavaScript (ES6+), Fetch API, HTML5, CSS3.
*   **Data Format:** JSON (JavaScript Object Notation).

## Installation & Launch

1.  Ensure you have **Node.js** installed.
2.  Install the dependencies (if not already):
    ```bash
    npm install express
    ```
3.  Run the server:
    ```bash
    node server.js
    ```
4.  Open your browser at **`http://localhost:3000`**.

## How to Use

1.  On the Home page, click **"Загрузить рецепты из JSON"** to see the dynamic table generation.
2.  Click **"Скачать JSON файл"** to test the backend file-serving capability.
3.  Navigate through the SPA to view the main recipe catalog.
