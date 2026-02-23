# HTML & CSS Basics
This laboratory work focuses on creating a multi-page HTML website with various CSS styling techniques. The project is based on a **Culinary Recipes** Collection theme.

## Tasks Completed
### Task 1: Two-Page Structure with Bookmarks
**Files**: `page1.html` and `page2.html`
- `page1.html`: Contains extensive descriptive text about culinary recipes
  - Properly formatted paragraphs
  - Bookmarks placed throughout the document for navigation
  - Embedded CSS stylesheet in the header defining styles for headings and paragraphs

- `page2.html`: Navigation page with two links to `page1.html`
  - "Read from beginning" - navigates to the start of page1
  - "Read from last paragraph" - navigates to a bookmark at the end of page1

### Task 2: Google Fonts Integration
**File**: `page3.html`

- Two custom fonts selected from Google Fonts
- Fonts properly configured and applied to different text elements
- Demonstrates web font usage in a practical layout

### Task 3: Styled Table with Cell Merging
**File**: `page4.html`
- Three-column table featuring recipe ingredients/products:
  - Column 1: Ingredient/Product name
  - Column 2: Price
  - Column 3: Quantity
- Single border styling using border-collapse property
- Custom background for the third column header
- Vertical cell merging using rowspan attribute in the second column

### Task 4: Flexible Frame with Image Slicing
**File**: `page5.html` (or index page with frame)
- Implemented a rubber/responsive frame using sliced ramka.png image
- Frame dimensions are flexible:
  - Width: 100% of browser window
  - Height: Automatically adjusts to content
- Text content has no hard line breaks, allowing natural flow
- Demonstrates advanced CSS positioning with sliced images technique

## Project Structure
```
project-root/
├── README.md
├── page1.html          # Main content with bookmarks
├── page2.html          # Navigation to page1
├── page3.html          # Google Fonts demonstration
├── page4.html          # Styled table with merged cells
├── page5.html          # Flexible frame with sliced image
└── images/             # Frame image for slicing
    ├── ramka1.png
    └── ...
```

## How to Run
1. Clone the repository
2. Open any HTML file in a modern web browser
3. Navigate between pages using the provided links

## Features Demonstrated
- Internal navigation with bookmarks
- Embedded CSS styling
- Google Fonts integration
- Complex table structures with merged cells
- Image slicing technique for flexible layouts
- Responsive design principles
