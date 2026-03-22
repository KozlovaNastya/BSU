# Culinary Collection & Persistent Storage System

An advanced version of the dish management system that features data persistence, ensuring your recipes remain available even after closing the browser or refreshing the page.

## Project Structure

*   **index.html** — The control panel interface with interactive buttons to manage the dish database.
*   **script.js** — The logic layer featuring a dual-class architecture for data management and persistence.

## Key Features

### 1. Permanent Data Persistence
Unlike previous versions, this system uses the browser's `LocalStorage`. Data is serialized into JSON format and saved under a specific key (`dishes_data`), allowing for long-term storage without a backend database.

### 2. Provider Pattern Architecture
The code is organized into two specialized classes:
*   **`TLocalStorage`**: A dedicated provider class that handles low-level storage operations (saving and loading JSON strings).
*   **`THashStorage`**: The high-level logic class that manages the dish collection and uses the storage provider to sync changes automatically.

### 3. Automatic Synchronization
Every action that modifies the data (Adding or Deleting a dish) automatically triggers a save command to the local storage, preventing data loss.

## Technologies

*   **HTML5 / CSS3** — User interface and styling.
*   **JavaScript (ES6+)** — Advanced OOP with **Private Class Fields** (`#`), **JSON Serialization**, and the **Web Storage API**.

## How to Use

1.  Open `index.html` in your browser.
2.  Use the **"Ввод информации"** (Add information) button to save a dish.
3.  **Refresh the page** or close the browser.
4.  Click **"Перечень всех блюд"** (List all dishes) to see that your data is still there!
