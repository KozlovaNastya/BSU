package zoo.dao;

import zoo.JdbcConnector;
import zoo.model.Keeper;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.List;

public class KeeperDao {

    private static final String SELECT_ALL = "SELECT * FROM keepers";

    public List<Keeper> findAll() throws Exception {
        List<Keeper> keepers = new ArrayList<>();
        try (Connection conn = JdbcConnector.getConnection();
             Statement stmt = conn.createStatement();
             ResultSet rs = stmt.executeQuery(SELECT_ALL)) {

            while (rs.next()) {
                keepers.add(new Keeper(
                        rs.getInt("id"),
                        rs.getString("name"),
                        rs.getString("phone")
                ));
            }
        }
        return keepers;
    }
}