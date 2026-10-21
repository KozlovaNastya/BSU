package zoo;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import java.sql.Connection;
import java.sql.DriverManager;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;
import java.util.concurrent.TimeUnit;

public class MyPool implements DatabasePool {
    private static final Logger logger = LoggerFactory.getLogger(MyPool.class);
    private BlockingQueue<Connection> pool;
    private static final int POOL_SIZE = 5;

    public MyPool(String url, String driver) throws Exception {
        this.pool = new LinkedBlockingQueue<>(POOL_SIZE);
        Class.forName(driver);
        
        for (int i = 0; i < POOL_SIZE; i++) {
            pool.offer(DriverManager.getConnection(url));
        }
        logger.info("MyPool initialized with {} connections", POOL_SIZE);
    }

    @Override
    public Connection getConnection() throws java.sql.SQLException {
        try {
            Connection conn = pool.poll(5, TimeUnit.SECONDS);
            if (conn == null) throw new java.sql.SQLException("MyPool timeout");
            return conn;
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
            throw new java.sql.SQLException("Interrupted", e);
        }
    }

    @Override
    public void releaseConnection(Connection conn) {
        if (conn != null) {
            pool.offer(conn);
        }
    }

    @Override
    public void shutdown() {
        for (Connection conn : pool) {
            try { conn.close(); } catch (Exception ignored) {}
        }
        logger.info("MyPool closed");
    }
}