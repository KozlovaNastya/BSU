# SPA and React Routing

## Overview
Single Page Application (SPA) with client-side routing using React Router DOM v5 and Material UI.

## Features
- SPA with no page reloads
- HashRouter for client-side routing
- App Bar header (Material UI)
- Navigation sidebar with links
- Dynamic content area
- Material UI Grid layout

## Tech Stack
- React 17 (Functional Components + Hooks)
- React Router DOM v5
- Material UI
- Webpack + Babel

## Project Structure
```
├── index.html # Main entry point
├── index.jsx # ReactDOM render
├── App.jsx # Routing configuration
├── components/
│ ├── Layout.jsx # Layout with sidebar
│ ├── Example/
│ ├── Regions/
│ └── MySearch/
└── modelData/ # Data models
```


## Installation & Running
```bash
npm install
npm run build
node webServer.js
```

## Routes
| Route |	Component |
| ----- | --------- |
| `/` or `/example` |	Example |
| `/regions` | Regions |
| `/mysearch`	| MySearch |
