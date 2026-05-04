# Reactive Recipe Book with Webpack & RxJS

This update transforms the Recipe Book application into a modern, reactive web application using **RxJS** for data flow management and **Webpack** for module bundling.

## New Features

- **Reactive Streams**: All user interactions (search, sort, pagination) are handled as Observables.
- **Real-time Search**: Filtering recipes with a `debounceTime` delay to optimize server requests.
- **Module Bundling**: Integrated Webpack to manage dependencies and assets (JS, CSS, libraries).
- **Automated UI Updates**: Using `combineLatest` to automatically refresh the list whenever any filter or page changes.

## Changes Breakdown

### Module Bundling (Webpack)
- **Entry Point**: Logic moved to `public/app.js` and bundled into `dist/bundle.js`.
- **Loaders**: Configured `style-loader` and `css-loader` to include CSS directly into the JS bundle.
- **Automation**: `HtmlWebpackPlugin` automatically generates the final HTML file with all necessary links.

### Reactive Logic (RxJS)
- **Event Streams**: Used `fromEvent` to capture inputs and button clicks without inline `onclick` attributes.
- **Ajax Observable**: Switched from `fetch` to `ajax.getJSON` for consistent stream handling.
- **State Management**: Used `BehaviorSubject` to track the current page and manual refresh triggers for CRUD operations.

### Backend (server.js)
- **Static Hosting**: Configured Express to serve the compiled files from the `/dist` directory.
- **API Integrity**: Maintained the existing CRUD endpoints while supporting reactive queries.

## How to Run

1. **Install Dependencies**:
   ```bash
   npm install
   ```
2. **Build the Project**:
   ```bash
   npm run build
   ```
3. **Start the Server**:
   ```bash
   npm start
   ```

## How to Test
1. **Reactive Search**: Start typing a recipe name; notice the list updates automatically after you stop typing for 300ms.
2. **Dynamic Sorting**: Change the sort order; the stream detects the change and fetches updated data immediately.
3. **CRUD Operations**: Add or delete a recipe; the UI refreshes automatically by pushing a new value to the `refresh$` stream.
