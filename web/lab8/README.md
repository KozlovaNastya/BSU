# Express CRUD Application

A simple web application for managing recipes using a REST API. This project demonstrates basic CRUD (Create, Read, Update, Delete) operations using Node.js, Express, and a JSON file as a local database.

## Project Overview

The application allows users to:
- **View** all recipes from a local `db.json` file.
- **Add** new recipes to the list.
- **Update** existing recipe names.
- **Delete** recipes from the database.

## Tech Stack

- **Backend:** Node.js, Express.js
- **Frontend:** EJS (Template Engine), CSS, Vanilla JavaScript
- **Database:** Local `db.json` file
- **Middleware:** Body-Parser

## Project Structure

```text
lab8/
├── public/
│   ├── style.css    # Application styling
│   └── app.js       # Client-side logic & Fetch API
├── views/
│   └── index.ejs    # Main page template
├── db.json          # Data storage (JSON format)
├── rest.js          # REST API route handlers
├── store.js         # File system logic (Read/Write)
├── server.js        # Server configuration & entry point
└── package.json     # Project dependencies
```

## Installation and Setup
1. Ensure Node.js is installed on your system.
2. Install dependencies:Open your terminal in the project root and run:

   `npm install express body-parser ejs`
3. Start the server: `bashnode server.js`
4. Access the app:
   
   Open your browser and navigate to http://localhost:3000.

## API Endpoints
- `GET /items` - Get all recipes.
- `GET /items/:id` - Get a specific recipe by ID.
- `POST /items` - Create a new recipe.
- `PUT /items/:id` - Update an existing recipe.
- `DELETE /items/:id` - Delete a recipe.

## Features
- **Persistence**: All changes are saved directly to db.json.
- **Dynamic Rendering**: Uses EJS to render the recipe list on the server side.
- **Responsive UI**: Interactive buttons for editing and deleting items.
