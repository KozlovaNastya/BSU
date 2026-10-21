package zoo;

import com.zaxxer.hikari.HikariConfig;
import com.zaxxer.hikari.HikariDataSource;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import java.sql.Connection;
import java.sql.SQLException;

public class HikariPool implements DatabasePool {
    private static final Logger logger = LoggerFactory.getLogger(HikariPool.class);
    private HikariDataSource dataSource;

    public HikariPool(String url, String driver) {
        HikariConfig config = new HikariConfig();
        config.setJdbcUrl(url);
        config.setDriverClassName(driver);
        config.setMaximumPoolSize(10);
        
        this.dataSource = new HikariDataSource(config);
        logger.info("HikariPool initialized");
    }

    @Override
    public Connection getConnection() throws SQLException {
        return dataSource.getConnection();
    }

    @Override
    public void releaseConnection(Connection conn) {
        // Hikari сам перехватывает close(), поэтому тут ничего делать не надо
        try {
            if (conn != null) conn.close();
        } catch (SQLException e) {
            logger.error("Error closing Hikari connection", e);
        }
    }

    @Override
    public void shutdown() {
        if (dataSource != null) dataSource.close();
    }
}