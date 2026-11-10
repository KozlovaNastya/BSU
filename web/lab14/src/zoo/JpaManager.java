package zoo;

import jakarta.persistence.EntityManager;
import jakarta.persistence.EntityManagerFactory;
import jakarta.persistence.Persistence;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.Statement;

public final class JpaManager {
    private static final String JDBC_URL = "jdbc:sqlite:zoo.db";
    private static final EntityManagerFactory EMF;

    static {
        try {
            Class.forName("org.sqlite.JDBC");
            createDatabaseSchema();
            EMF = Persistence.createEntityManagerFactory("zoo-unit");
        } catch (Exception e) {
            throw new ExceptionInInitializerError(e);
        }
    }

    private JpaManager() { }

    // SQLite требует задавать внешние ключи при CREATE TABLE,
    // а не добавлять их отдельным ALTER TABLE.
    private static void createDatabaseSchema() throws Exception {
        try (Connection connection = DriverManager.getConnection(JDBC_URL);
             Statement statement = connection.createStatement()) {
            statement.execute("PRAGMA foreign_keys = ON");
            statement.executeUpdate("""
                CREATE TABLE IF NOT EXISTS SEQUENCE (
                    SEQ_NAME TEXT PRIMARY KEY,
                    SEQ_COUNT INTEGER NOT NULL
                )
                """);
            statement.executeUpdate("INSERT OR IGNORE INTO SEQUENCE (SEQ_NAME, SEQ_COUNT) VALUES ('SEQ_GEN_IDENTITY', 0)");
            statement.executeUpdate("""
                CREATE TABLE IF NOT EXISTS animals (
                    ID INTEGER PRIMARY KEY AUTOINCREMENT,
                    name TEXT NOT NULL,
                    kind TEXT NOT NULL,
                    age INTEGER NOT NULL,
                    weight REAL NOT NULL
                )
                """);
            statement.executeUpdate("""
                CREATE TABLE IF NOT EXISTS cares (
                    ID INTEGER PRIMARY KEY AUTOINCREMENT,
                    description TEXT NOT NULL,
                    type TEXT NOT NULL,
                    animal_id INTEGER NOT NULL,
                    FOREIGN KEY (animal_id) REFERENCES animals(ID)
                )
                """);
            statement.executeUpdate("""
                CREATE TABLE IF NOT EXISTS keepers (
                    ID INTEGER PRIMARY KEY AUTOINCREMENT,
                    name TEXT NOT NULL,
                    phone TEXT
                )
                """);
            statement.executeUpdate("""
                CREATE TABLE IF NOT EXISTS tasks (
                    ID INTEGER PRIMARY KEY AUTOINCREMENT,
                    description TEXT NOT NULL,
                    status TEXT NOT NULL,
                    dateAssigned TEXT,
                    result TEXT,
                    keeper_id INTEGER NOT NULL,
                    animal_id INTEGER NOT NULL,
                    care_id INTEGER,
                    FOREIGN KEY (keeper_id) REFERENCES keepers(ID),
                    FOREIGN KEY (animal_id) REFERENCES animals(ID),
                    FOREIGN KEY (care_id) REFERENCES cares(ID)
                )
                """);
        }
    }

    public static EntityManager getEntityManager() {
        return EMF.createEntityManager();
    }

    public static void close() {
        if (EMF.isOpen()) EMF.close();
    }
}
