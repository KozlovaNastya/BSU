# Library Management System

## Objective
To implement a console-based library management system with support for book cataloging, reader registration, order processing, serialization, and localization.

## Program Structure

### Main Components
- `Book`: Represents a book with ISBN, title, author, year, availability, and creation time.
- `Reader`: Represents a library reader with personal data, blacklist status, and borrowed books.
- `Order`: Represents a book order with type, date, status, and creation time.
- `Catalog`: Stores and manages books with search functionality.
- `Library`: Core class that manages catalog, readers, and orders.
- `LibraryConnector`: Handles saving and loading library data via serialization.
- `main`: Console UI with menu navigation and localization support.

## Key Features
- Object serialization (`Serializable`) for persistent storage
- Automatic tracking of object creation time (`Date`)
- Book availability management
- Reader blacklist support
- Order lifecycle handling
- Robust validation with exceptions

## Localization
- Uses `.properties` files with `ResourceBundle`
- Language and country are set via command-line arguments
- Date and messages are localized according to selected locale

## Persistence
- Library state is saved to and loaded from a `.ser` file
- Transient fields are restored using custom `readObject()` methods

## User Interface
- Console-based menu system
- Input validation
- Localized messages and date formatting

## Technologies Used
- Java Collections
- Java Serialization
- Java Streams
- ResourceBundle & Locale
- Date & Time API
