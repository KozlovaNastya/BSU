# Zoo Management System (JPA)

## Program Description

A console-based Java application for managing a zoo. The project uses Java Persistence API (JPA) with EclipseLink and SQLite for database operations.

## Functionality

- Display all animals.
- View available animal care activities.
- Display keeper tasks.
- Assign tasks to keepers.
- Record task completion results.
- Store and retrieve data using JPA.

## Technologies

- Java
- Jakarta Persistence API (JPA)
- EclipseLink 4.0.4
- SQLite
- JDBC
- SLF4J and Logback

## Project Structure

- `model/` – JPA entity classes.
- `dao/` – Data Access Objects for database operations.
- `META-INF/` – JPA persistence configuration.
- `JpaManager.java` – EntityManagerFactory management.
- `Main.java` – Application entry point and console menu.
- `lib/` – External libraries.

## How to Run

Open the project in Visual Studio Code and run `zoo.Main`.

Make sure the required JAR libraries are configured in the project settings.

## Database

The application uses SQLite as its database and EclipseLink as its JPA provider.