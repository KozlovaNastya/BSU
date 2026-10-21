package zoo.dao;

import zoo.JdbcConnector;
import zoo.model.Care;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.List;

public class CareDao {

    private static final String SELECT_ALL = "SELECT * FROM cares";
    private static final String SELECT_BY_ID = "SELECT * FROM cares WHERE id = ?";

    public List<Care> findAll() throws Exception {
        List<Care> cares = new ArrayList<>();
        try (Connection conn = JdbcConnector.getConnection();
             Statement stmt = conn.createStatement();
             ResultSet rs = stmt.executeQuery(SELECT_ALL)) {

            while (rs.next()) {
                cares.add(mapRow(rs));
            }
        }
        return cares;
    }

    public Care findById(int id) throws Exception {
        try (Connection conn = JdbcConnector.getConnection();
             PreparedStatement ps = conn.prepareStatement(SELECT_BY_ID)) {

            ps.setInt(1, id);
            try (ResultSet rs = ps.executeQuery()) {
                if (rs.next()) {
                    return mapRow(rs);
                }
            }
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