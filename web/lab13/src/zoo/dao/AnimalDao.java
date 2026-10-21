package zoo.dao;

import zoo.JdbcConnector;
import zoo.model.Animal;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.List;

public class AnimalDao {

    // SQL-запросы как константы
    private static final String SELECT_ALL = "SELECT * FROM animals";
    private static final String SELECT_BY_ID = "SELECT * FROM animals WHERE id = ?";
    private static final String INSERT = "INSERT INTO animals(name, kind, age, weight) VALUES (?, ?, ?, ?)";

    // Получить всех животных
    public List<Animal> findAll() throws Exception {
        List<Animal> animals = new ArrayList<>();
        try (Connection conn = JdbcConnector.getConnection();
             Statement stmt = conn.createStatement();
             ResultSet rs = stmt.executeQuery(SELECT_ALL)) {

            while (rs.next()) {
                animals.add(mapRow(rs));
            }
        }
        return animals;
    }

    // Найти животное по id
    public Animal findById(int id) throws Exception {
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

    // Добавить животное
    public void insert(Animal animal) throws Exception {
        try (Connection conn = JdbcConnector.getConnection();
             PreparedStatement ps = conn.prepareStatement(INSERT)) {

            ps.setString(1, animal.getName());
            ps.setString(2, animal.getKind());
            ps.setInt(3, animal.getAge());
            ps.setDouble(4, animal.getWeight());
            ps.executeUpdate();
        }
    }

    // Преобразование строки БД в объект
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