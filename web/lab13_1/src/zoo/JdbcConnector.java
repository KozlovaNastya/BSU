package zoo;

import java.io.InputStream;
import java.sql.Connection;
import java.sql.DriverManager;
import java.util.Properties;

public class JdbcConnector {
    private static String URL;
    private static String DRIVER;

    static {
        try (InputStream input = JdbcConnector.class
                .getClassLoader()
                .getResourceAsStream("zoo/resources/database.properties")) {

            if (input == null) {
                throw new RuntimeException(
                    "Не найден database.properties"
                );
            }

            Properties props = new Properties();
            props.load(input);
            URL = props.getProperty("db.url");
            DRIVER = props.getProperty("db.driver");

            Class.forName(DRIVER);
            System.out.println("Подключение к БД настроено: " + URL);
        } catch (Exception e) {
            throw new RuntimeException("Ошибка загрузки конфигурации БД", e);
        }
    }

    public static Connection getConnection() throws Exception {
        return DriverManager.getConnection(URL);
    }
}