package zoo;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.Statement;

public class DatabaseInitializer {
    private static final Logger logger = LoggerFactory.getLogger(DatabaseInitializer.class);

    public static void init() {
        Connection conn = null;
        try {
            conn = DatabaseConnector.getConnection();
            try (Statement stmt = conn.createStatement()) {
                stmt.execute("CREATE TABLE IF NOT EXISTS animals (" +
                        "id INTEGER PRIMARY KEY AUTOINCREMENT," +
                        "name TEXT NOT NULL," +
                        "kind TEXT NOT NULL," +
                        "age INTEGER," +
                        "weight REAL)");

                stmt.execute("CREATE TABLE IF NOT EXISTS cares (" +
                        "id INTEGER PRIMARY KEY AUTOINCREMENT," +
                        "animal_id INTEGER NOT NULL," +
                        "description TEXT NOT NULL," +
                        "type TEXT NOT NULL," +
                        "FOREIGN KEY (animal_id) REFERENCES animals(id))");

                stmt.execute("CREATE TABLE IF NOT EXISTS keepers (" +
                        "id INTEGER PRIMARY KEY AUTOINCREMENT," +
                        "name TEXT NOT NULL," +
                        "phone TEXT)");

                stmt.execute("CREATE TABLE IF NOT EXISTS tasks (" +
                        "id INTEGER PRIMARY KEY AUTOINCREMENT," +
                        "keeper_id INTEGER NOT NULL," +
                        "animal_id INTEGER NOT NULL," +
                        "care_id INTEGER NOT NULL," +
                        "description TEXT," +
                        "status TEXT DEFAULT 'assigned'," +
                        "date_assigned TEXT," +
                        "result TEXT," +
                        "FOREIGN KEY (keeper_id) REFERENCES keepers(id)," +
                        "FOREIGN KEY (animal_id) REFERENCES animals(id)," +
                        "FOREIGN KEY (care_id) REFERENCES cares(id))");

                logger.info("Tables successfully created (or already exist)");
            }
        } catch (Exception e) {
            logger.error("Error initializing database", e);
        } finally {
            DatabaseConnector.releaseConnection(conn);
        }
    }

    public static void seed() {
        Connection conn = null;
        try {
            conn = DatabaseConnector.getConnection();
            try (Statement stmt = conn.createStatement()) {
                ResultSet rs = stmt.executeQuery("SELECT COUNT(*) FROM animals");
                rs.next();
                if (rs.getInt(1) > 0) {
                    logger.info("Data already exists, skipping seeding");
                    return;
                }

                stmt.execute("INSERT INTO animals(name, kind, age, weight) VALUES " +
                        "('Бу', 'Панда', 3, 12.5)," +
                        "('Симба', 'Лев', 5, 150.0)," +
                        "('Дамбо', 'Слон', 10, 2000.0)," +
                        "('Мельман', 'Жираф', 7, 800.0)," +
                        "('Скиппер', 'Пингвин', 2, 15.0)");

                stmt.execute("INSERT INTO cares(animal_id, description, type) VALUES " +
                        "(1, 'Кормление бамбуком', 'Питание')," +
                        "(1, 'Медицинский осмотр', 'Лечение')," +
                        "(2, 'Кормление мясом', 'Питание')," +
                        "(3, 'Купание', 'Содержание')," +
                        "(4, 'Осмотр копыт', 'Лечение')," +
                        "(5, 'Кормление рыбой', 'Питание')");

                stmt.execute("INSERT INTO keepers(name, phone) VALUES " +
                        "('Иван Петров', '+375291234567')," +
                        "('Мария Сидорова', '+375297654321')," +
                        "('Алексей Кузнецов', '+375333333333')");

                stmt.execute("INSERT INTO tasks(keeper_id, animal_id, care_id, description, status, date_assigned) VALUES " +
                        "(1, 1, 1, 'Покормить панду утром', 'assigned', '2026-10-14')," +
                        "(1, 2, 3, 'Покормить льва', 'assigned', '2026-10-14')," +
                        "(2, 3, 4, 'Искупать слона', 'assigned', '2026-10-14')," +
                        "(2, 5, 6, 'Покормить пингвина', 'completed', '2026-10-13')");

                logger.info("Initial data seeded successfully");
            }
        } catch (Exception e) {
            logger.error("Error seeding database", e);
        } finally {
            DatabaseConnector.releaseConnection(conn);
        }
    }
}