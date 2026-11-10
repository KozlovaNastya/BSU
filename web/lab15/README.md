# Zoo Management Web Application — Laboratory Work №15

## Program Description

A Java web application for managing zoo animals, care activities, keepers, and their tasks. The project extends the JPA application from Laboratory Work №14 with a central Java Servlet dispatcher, separate controllers, Thymeleaf pages, HTTP sessions, and cookies.

## Functionality

- View all animals, filter them by species and age, and add new animals.
- Browse care activities, add new care activities, and link them to animals.
- View the keeper directory and add new keepers.
- View tasks assigned to a selected keeper and filter them by status.
- Assign a new task to a keeper.
- Mark a task as completed and save its result.
- Display session information: the previous session date/time, total browser visits, and the number of requests in the current session.
- Initialize a small demonstration dataset automatically when the database is empty.

## Technologies

- Java 17
- Maven WAR project
- Jakarta Servlet 5.0
- Thymeleaf 3.1
- Jakarta Persistence 3.1
- EclipseLink 4.0.4
- SQLite JDBC
- Jetty 11 Maven Plugin
- SLF4J and Logback

## Project Structure

- `src/main/java/zoo/model/` — JPA entities and static metamodel classes.
- `src/main/java/zoo/dao/` — DAO classes reused from Laboratory Work №14; read operations use Criteria API and Static Metamodel API.
- `src/main/java/zoo/JpaManager.java` — EntityManagerFactory, SQLite schema creation, and transaction helper.
- `src/main/java/zoo/DatabaseInitializer.java` — inserts sample records when the database is empty.
- `src/main/java/zoo/web/FrontControllerServlet.java` — central servlet that resolves URLs and dispatches requests.
- `src/main/java/zoo/web/controllers/` — separate controllers for each page and task operation.
- `src/main/java/zoo/web/TemplateConfig.java` — Thymeleaf configuration.
- `src/main/webapp/WEB-INF/templates/` — Thymeleaf HTML templates.
- `src/main/resources/META-INF/persistence.xml` — JPA configuration.
- `pom.xml` — dependencies and Maven plugins.

## How to Run

1. Install JDK 17 (or newer) and Apache Maven.
2. Open the `lab15` folder in Visual Studio Code.
3. Open the integrated terminal in the project folder.
4. Run:

   ```bash
   mvn clean package
   mvn jetty:run
   ```

5. Open `http://localhost:8080/ZooWeb/` in a browser.
6. Stop the server with `Ctrl+C` in the terminal.

Maven downloads the required libraries automatically; no manual JAR configuration is needed. The first start creates `zoo.db` in the working directory and inserts demonstration data. The database file is not committed to the project, so it can be recreated by deleting it and restarting the application.

## Request Routing

The `FrontControllerServlet` is mapped to `/*`. It extracts the request path, finds the corresponding controller, and either renders a Thymeleaf template or redirects after a POST request.

| URL | Controller | Purpose |
|---|---|---|
| `/` | `DashboardController` | Overview page |
| `/animals` | `AnimalsController` | Animal list and filtering |
| `/animals/create` | `CreateAnimalController` | Add an animal (POST) |
| `/cares` | `CaresController` | Care activity list |
| `/cares/create` | `CreateCareController` | Add a care activity (POST) |
| `/keepers` | `KeepersController` | Keeper list |
| `/keepers/create` | `CreateKeeperController` | Add a keeper (POST) |
| `/tasks` | `TasksController` | Keeper tasks and task filters |
| `/tasks/assign` | `AssignTaskController` | Assign a task (POST) |
| `/tasks/complete` | `CompleteTaskController` | Save task completion (POST) |

## Sessions and Cookies

The application creates an `HttpSession` for each visitor and stores a `UserSession` object in it. The object records the session creation time and the number of requests made during the current session. Two cookies are used:

- `lastSession` — timestamp of the latest session start, used to display the previous session time on the next visit.
- `visitCount` — total number of browser visits (new sessions).

Both cookies are kept for one year and are marked `HttpOnly`.

## Database

The application uses the same SQLite/JPA model and DAO layer as Laboratory Work №14. `JpaManager` creates the schema before initializing EclipseLink. The database file is `zoo.db` in the application's working directory.

## Error Handling and Logging

Controllers validate form input before calling DAO methods. DAO classes handle persistence errors and write diagnostic messages through SLF4J and Logback. Unexpected request errors are logged and shown on a dedicated error page.
