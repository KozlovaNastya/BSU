package zoo.dao;

import zoo.DatabaseConnector;
import zoo.model.Keeper;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.List;

public class KeeperDao {
    private static final Logger logger = LoggerFactory.getLogger(KeeperDao.class);

    private static final String SELECT_ALL = "SELECT * FROM keepers";

    public List<Keeper> findAll() {
        List<Keeper> keepers = new ArrayList<>();
        Connection conn = null;
        try {
            conn = DatabaseConnector.getConnection();
            try (Statement stmt = conn.createStatement();
                 ResultSet rs = stmt.executeQuery(SELECT_ALL)) {

                while (rs.next()) {
                    keepers.add(new Keeper(
                            rs.getInt("id"),
                            rs.getString("name"),
                            rs.getString("phone")
                    ));
                }
            }
            logger.info("Loaded {} keepers from DB", keepers.size());
        } catch (Exception e) {
            logger.error("Error loading keepers", e);
        } finally {
            DatabaseConnector.releaseConnection(conn);
        }
        return keepers;
    }
}