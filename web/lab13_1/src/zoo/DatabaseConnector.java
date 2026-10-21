package zoo;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import java.io.InputStream;
import java.sql.Connection;
import java.util.Properties;

public class DatabaseConnector {
    private static final Logger logger = LoggerFactory.getLogger(DatabaseConnector.class);
    private static DatabasePool pool;

    static {
        try (InputStream input = DatabaseConnector.class.getClassLoader()
                .getResourceAsStream("zoo/resources/database.properties")) {
            
            Properties props = new Properties();
            props.load(input);
            
            String url = props.getProperty("db.url");
            String driver = props.getProperty("db.driver");
            String poolType = props.getProperty("pool.type", "hikari");

            // ВОТ ОНА - ЛОГИКА ПЕРЕКЛЮЧЕНИЯ (БЕЗ ОТДЕЛЬНОЙ ФАБРИКИ)
            if ("my".equalsIgnoreCase(poolType)) {
                pool = new MyPool(url, driver);
                logger.info("Using MY custom connection pool");
            } else {
                pool = new HikariPool(url, driver);
                logger.info("Using HIKARI connection pool");
            }
        } catch (Exception e) {
            logger.error("Error initializing database pool", e);
            throw new RuntimeException(e);
        }
    }

    public static Connection getConnection() throws Exception {
        return pool.getConnection();
    }

    public static void releaseConnection(Connection conn) {
        pool.releaseConnection(conn);
    }
}