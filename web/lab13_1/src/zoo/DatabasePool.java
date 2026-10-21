package zoo;

import java.sql.Connection;
import java.sql.SQLException;

public interface DatabasePool {
    Connection getConnection() throws SQLException;
    void releaseConnection(Connection conn);
    void shutdown();
}