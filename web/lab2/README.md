# Laboratory Work №2: Table & Block Layout
This project demonstrates two different approaches to web layouts: Table-based and Block-based (DIV), using the **Culinary Recipes** theme (Variant #3).

## Objectives
- Create a rubber (fluid) layout where the main column stretches.
- Fix the sidebar width (menu).
- Ensure the sidebar is taller than the main content by adding sufficient menu items.

## Projects Included
1. **MAKET_TABLE**: Implemented using the `<table>` tag. 
   - Uses `width="100%"` for the table.
   - Fixed width for the menu `<td>`.
2. **MAKET_DIV**: Implemented using modern `display: flex`.
   - Sidebar has a fixed `flex-basis`.
   - Main content uses `flex: 1` for dynamic stretching.

## Content
- Theme: Culinary Recipes (from Lab #1).
- Navigation: Fixed sidebar with recipe categories.
- Main area: Recipe description with a "rubber" layout.
