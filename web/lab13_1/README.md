# Connection Pools & Logging

## Description
An advanced version of the Zoo application. This part focuses on connection pooling (custom and industrial), exception handling, and logging.

## Features
- **Custom Connection Pool**: Implemented using a thread-safe `BlockingQueue`.
- **HikariCP**: Integrated a high-performance connection pool.
- **Strategy Pattern**: A `DatabaseConnector` acts as a director, dynamically switching between Hikari and the custom pool based on the `database.properties` file.
- **Logging**: Replaced `System.out.println` with **SLF4J + Logback** for structured logging.
- **Exception Handling**: All SQL operations are wrapped in `try-catch` blocks with proper resource management.

## Tech Stack
- Java 25
- JDBC API & SQLite
- **HikariCP** (Connection Pool)
- **SLF4J + Logback** (Logging)

## How to switch pools
Open `src/zoo/resources/database.properties` and change the `pool.type` value:
- `pool.type=hikari` (default) — uses HikariCP.
- `pool.type=my` — uses the custom `MyPool`.

## How to Run
1. Ensure all `.jar` files are in the `lib/` folder.
2. Run `Main.java`.
3. Check the console logs to see which pool is initialized (e.g., `Using HIKARI connection pool`).

## Project Structure
```text
src/
├── logback.xml                  # Logger configuration
└── zoo/
    ├── Main.java                # Console menu
    ├── DatabaseConnector.java   # Director/Strategy class for pools
    ├── DatabasePool.java        # Interface for connection pools
    ├── HikariPool.java          # HikariCP implementation
    ├── MyPool.java              # Custom pool implementation
    ├── DatabaseInitializer.java # DB initialization with logging
    ├── dao/                     # DAOs using DatabaseConnector
    └── model/                   # Entity classes
```
