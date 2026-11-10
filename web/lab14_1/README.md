# Zoo Management System — JPA Criteria API

## Program Description

A console-based Java application for managing zoo animals, care activities, keepers, and assigned tasks. This version extends the previous JPA project by replacing static JPQL named queries with dynamic, type-safe queries built with the JPA Criteria API and Static Metamodel API.

## Functionality

- Display and search for animals.
- View care activities and their related animals.
- Display tasks assigned to a keeper.
- Filter tasks by keeper and status.
- Assign new tasks to keepers.
- Record task completion results.
- Persist data in an SQLite database.

## Technologies

- Java 17 or later
- Jakarta Persistence API 3.1
- EclipseLink 4.0.4
- SQLite JDBC
- JPA Criteria API
- JPA Static Metamodel API
- SLF4J and Logback

## Project Structure

- `src/zoo/model/` — JPA entity classes and static metamodel classes (`Animal_`, `Care_`, `Keeper_`, `Task_`).
- `src/zoo/dao/` — DAO classes containing type-safe Criteria API queries and transaction handling.
- `src/META-INF/persistence.xml` — JPA persistence configuration.
- `src/logback.xml` — logging configuration.
- `src/zoo/JpaManager.java` — EntityManagerFactory and SQLite schema initialization.
- `src/zoo/Main.java` — console application entry point.
- `lib/` — external JAR dependencies used by the manual VS Code build.

## How to Run

1. Open the project folder in Visual Studio Code.
2. Make sure the Java extensions are installed.
3. Ensure that the JAR files in `lib/` are included in the project classpath (configured in `.vscode/settings.json`).
4. Run `zoo.Main` from the Run button in VS Code.

## Database

The application uses SQLite. The database file `zoo.db` is created in the working directory when the application starts.

## Query Implementation

All DAO read queries are constructed dynamically with `CriteriaBuilder`, `CriteriaQuery`, and entity roots/joins. Attribute references use the static metamodel classes, avoiding string-based field paths and providing compile-time type checking.

## Exception Handling and Logging

DAO operations validate input, handle persistence and runtime exceptions, and log successful operations and failures through SLF4J with Logback.

### Windows Console Encoding

If Cyrillic text is displayed incorrectly in the VS Code terminal, run `chcp 65001` in the integrated terminal and start the application again.
