# React Search Lab

A React-based laboratory project demonstrating component-based search functionality with real-time filtering.

## Features
- Functional React components with Hooks (`useState`, `useEffect`)
- Real-time search with case-insensitive filtering
- Alphabetical sorting of results
- Material UI integration (`List`, `ListItem`)
- Modular architecture with separate model data and components

## Project Structure

```
├── components/ # React components
│ ├── Example/ # Example component with lifecycle demo
│ ├── Regions/ # Search for Belarus regions
│ └── MySearch/ # Custom search component with Material UI
├── modelData/ # Data models (example.js, regions.js, MyData.js)
├── compiled/ # Webpack build output
├── styles/ # Global styles
├── p2.html / p2.jsx # Entry point for Regions
├── MySearch.html / MySearch.jsx # Entry point for MySearch
├── gettingStarted.jsx # Entry point for Example
└── webpack.config.js # Build configuration
```


## Tech Stack
- **React** (Functional Components + Hooks)
- **Material UI** (List, ListItem)
- **Webpack** (Module bundler)
- **Babel** (JSX transpilation)

## Installation & Running
```bash
npm install
npm run build
node webServer.js
```

## Core Logic
- Search: `item.toLowerCase().includes(term.toLowerCase())`

- Sorting: `localeCompare(term, 'ru')` for Russian alphabet

- State Management: useState hooks

- Lifecycle: useEffect for side effects
