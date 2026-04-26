# Pagination

This update adds advanced data management features to the existing Recipe Book application.

## New Features

- **Search**: Real-time filtering of recipes by name using the `oninput` event.
- **Sorting**: Alphabetical sorting (A-Z and Z-A) of recipe titles.
- **Pagination**: Splitting the recipe list into multiple pages to improve performance and readability.

## Changes Breakdown

### Backend (store.js & rest.js)
- **Filtering logic**: Added `.filter()` to handle search queries.
- **Sorting logic**: Implemented `.sort()` with `localeCompare` for correct Russian language sorting.
- **Pagination logic**: Added `.slice()` to extract specific items for the requested page.
- **Query Params**: The API now accepts parameters via URL (e.g., `/items?page=1&search=soup`).

### Frontend (app.js & index.ejs)
- **Dynamic Rendering**: Shifted from server-side EJS loops to client-side rendering using `innerHTML`.
- **Event Listeners**: Added `oninput` for search and `onchange` for sorting.
- **Pagination UI**: Dynamically generated buttons that track the current page.

## How to Test
1. **Search**: Type "Борщ" in the search box; the list should update instantly.
2. **Sort**: Change the dropdown to "Название (А-Я)"; recipes will rearrange.
3. **Pagination**: Click on page numbers at the top to navigate through the list (3-5 items per page).
