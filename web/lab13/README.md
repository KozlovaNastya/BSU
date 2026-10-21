# JDBC, DAO & SQLite

## Description
A console-based Java application for managing a Zoo database. This part focuses on core JDBC technology and the Data Access Object (DAO) pattern.

## Features
- **SQLite** database integration.
- **DAO pattern** to isolate database logic from the main application.
- **PreparedStatement** used for all SQL queries to prevent SQL injection.
- Database credentials stored in a separate `database.properties` resource file.
- Data normalized to **2NF** (tables: `animals`, `cares`, `keepers`, `tasks`).

## Tech Stack
- Java 25
- JDBC API
- SQLite
- `sqlite-jdbc` driver

## How to Run
1. Ensure you have Java 17+ installed.
2. Make sure the `.jar` files are in the `lib/` folder.
3. Run `Main.java` (the entry point of the application).
4. Use the console menu to interact with the database.

## Project Structure
```text
src/
└── zoo/
    ├── Main.java                # Console menu and entry point
    ├── JdbcConnector.java       # Database connection manager
    ├── DatabaseInitializer.java # Creates tables and seeds initial data
    ├── dao/                     # Data Access Object classes
    ├── model/                   # Entity classes
    └── resources/
        └── database.properties  # DB credentials and settings
```
