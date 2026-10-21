package zoo.dao;

import zoo.DatabaseConnector;
import zoo.model.Animal;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.List;

public class AnimalDao {
    private static final Logger logger = LoggerFactory.getLogger(AnimalDao.class);

    private static final String SELECT_ALL = "SELECT * FROM animals";
    private static final String SELECT_BY_ID = "SELECT * FROM animals WHERE id = ?";
    private static final String INSERT = "INSERT INTO animals(name, kind, age, weight) VALUES (?, ?, ?, ?)";

    public List<Animal> findAll() {
        List<Animal> animals = new ArrayList<>();
        Connection conn = null;
        try {
            conn = DatabaseConnector.getConnection();
            try (Statement stmt = conn.createStatement();
                 ResultSet rs = stmt.executeQuery(SELECT_ALL)) {

                while (rs.next()) {
                    animals.add(mapRow(rs));
                }
            }
            logger.info("Loaded {} animals from DB", animals.size());
        } catch (Exception e) {
            logger.error("Error loading animals", e);
        } finally {
            DatabaseConnector.releaseConnection(conn);
        }
        return animals;
    }

    public Animal findById(int id) {
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
            logger.error("Error finding animal by id=" + id, e);
        } finally {
            DatabaseConnector.releaseConnection(conn);
        }
        return null;
    }

    public void insert(Animal animal) {
        Connection conn = null;
        try {
            conn = DatabaseConnector.getConnection();
            try (PreparedStatement ps = conn.prepareStatement(INSERT)) {
                ps.setString(1, animal.getName());
                ps.setString(2, animal.getKind());
                ps.setInt(3, animal.getAge());
                ps.setDouble(4, animal.getWeight());
                ps.executeUpdate();
            }
            logger.info("Added new animal: {}", animal.getName());
        } catch (Exception e) {
            logger.error("Error adding animal", e);
        } finally {
            DatabaseConnector.releaseConnection(conn);
        }
    }

    private Animal mapRow(ResultSet rs) throws Exception {
        return new Animal(
                rs.getInt("id"),
                rs.getString("name"),
                rs.getString("kind"),
                rs.getInt("age"),
                rs.getDouble("weight")
        );
    }
}