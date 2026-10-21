package zoo;

import java.sql.Connection;
import java.sql.Statement;

public class DatabaseInitializer {

    public static void init() throws Exception {
        try (Connection conn = JdbcConnector.getConnection();
             Statement stmt = conn.createStatement()) {

            // Таблица животных
            stmt.execute(
                "CREATE TABLE IF NOT EXISTS animals (" +
                "id INTEGER PRIMARY KEY AUTOINCREMENT," +
                "name TEXT NOT NULL," +
                "kind TEXT NOT NULL," +
                "age INTEGER," +
                "weight REAL)"
            );

            // Таблица ухода
            stmt.execute(
                "CREATE TABLE IF NOT EXISTS cares (" +
                "id INTEGER PRIMARY KEY AUTOINCREMENT," +
                "animal_id INTEGER NOT NULL," +
                "description TEXT NOT NULL," +
                "type TEXT NOT NULL," +
                "FOREIGN KEY (animal_id) REFERENCES animals(id))"
            );

            // Таблица смотрителей
            stmt.execute(
                "CREATE TABLE IF NOT EXISTS keepers (" +
                "id INTEGER PRIMARY KEY AUTOINCREMENT," +
                "name TEXT NOT NULL," +
                "phone TEXT)"
            );

            // Таблица заданий
            stmt.execute(
                "CREATE TABLE IF NOT EXISTS tasks (" +
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
                "FOREIGN KEY (care_id) REFERENCES cares(id))"
            );

            System.out.println("Таблицы созданы");
        }
    }

    // Заполнить начальными данными (только если пусто)
    public static void seed() throws Exception {
        try (Connection conn = JdbcConnector.getConnection();
             Statement stmt = conn.createStatement()) {

            // Проверяем, есть ли данные
            var rs = stmt.executeQuery("SELECT COUNT(*) FROM animals");
            rs.next();
            if (rs.getInt(1) > 0) {
                System.out.println("Данные уже есть, пропускаю заполнение");
                return;
            }

            // Животные
            stmt.execute("INSERT INTO animals(name, kind, age, weight) VALUES " +
                    "('Бу', 'Панда', 3, 12.5)," +
                    "('Симба', 'Лев', 5, 150.0)," +
                    "('Дамбо', 'Слон', 10, 2000.0)," +
                    "('Мельман', 'Жираф', 7, 800.0)," +
                    "('Скиппер', 'Пингвин', 2, 15.0)");

            // Уход
            stmt.execute("INSERT INTO cares(animal_id, description, type) VALUES " +
                    "(1, 'Кормление бамбуком', 'Питание')," +
                    "(1, 'Медицинский осмотр', 'Лечение')," +
                    "(2, 'Кормление мясом', 'Питание')," +
                    "(3, 'Купание', 'Содержание')," +
                    "(4, 'Осмотр копыт', 'Лечение')," +
                    "(5, 'Кормление рыбой', 'Питание')");

            // Смотрители
            stmt.execute("INSERT INTO keepers(name, phone) VALUES " +
                    "('Иван Петров', '+375291234567')," +
                    "('Мария Сидорова', '+375297654321')," +
                    "('Алексей Кузнецов', '+375333333333')");

            // Задания
            stmt.execute("INSERT INTO tasks(keeper_id, animal_id, care_id, description, status, date_assigned) VALUES " +
                    "(1, 1, 1, 'Покормить панду утром', 'assigned', '2026-10-14')," +
                    "(1, 2, 3, 'Покормить льва', 'assigned', '2026-10-14')," +
                    "(2, 3, 4, 'Искупать слона', 'assigned', '2026-10-14')," +
                    "(2, 5, 6, 'Покормить пингвина', 'completed', '2026-10-13')");

            System.out.println("✅ Начальные данные добавлены");
        }
    }
}