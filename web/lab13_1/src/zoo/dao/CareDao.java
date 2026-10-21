package zoo.dao;

import zoo.DatabaseConnector;
import zoo.model.Care;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.List;

public class CareDao {
    private static final Logger logger = LoggerFactory.getLogger(CareDao.class);

    private static final String SELECT_ALL = "SELECT * FROM cares";
    private static final String SELECT_BY_ID = "SELECT * FROM cares WHERE id = ?";

    public List<Care> findAll() {
        List<Care> cares = new ArrayList<>();
        Connection conn = null;
        try {
            conn = DatabaseConnector.getConnection();
            try (Statement stmt = conn.createStatement();
                 ResultSet rs = stmt.executeQuery(SELECT_ALL)) {

                while (rs.next()) {
                    cares.add(mapRow(rs));
                }
            }
            logger.info("Loaded {} cares from DB", cares.size());
        } catch (Exception e) {
            logger.error("Error loading cares", e);
        } finally {
            DatabaseConnector.releaseConnection(conn);
        }
        return cares;
    }

    public Care findById(int id) {
        Connection conn = null;
        try {
            conn = DatabaseConnector.getConnection();
            try (PreparedStatement ps = conn.prepareStatement(SELECT_BY_ID)) {
                ps.setInt(1, id);
                try (ResultSet rs = ps.executeQuery()) {
                    if (rs.next()) {
                        return mapRow(rs);
                    }
                }
            }
        } catch (Exception e) {
            logger.error("Error finding care by id=" + id, e);
        } finally {
            DatabaseConnector.releaseConnection(conn);
        }
        return null;
    }

    private Care mapRow(ResultSet rs) throws Exception {
        return new Care(
                rs.getInt("id"),
                rs.getInt("animal_id"),
                rs.getString("description"),
                rs.getString("type")
        );
    }
}