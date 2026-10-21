package zoo.dao;

import zoo.JdbcConnector;
import zoo.model.Task;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.ArrayList;
import java.util.List;

public class TaskDao {

    // Задания заданного смотрителя (с JOIN для получения имени животного)
    private static final String SELECT_BY_KEEPER =
            "SELECT t.*, a.name AS animal_name, c.description AS care_desc " +
            "FROM tasks t " +
            "JOIN animals a ON t.animal_id = a.id " +
            "JOIN cares c ON t.care_id = c.id " +
            "WHERE t.keeper_id = ?";

    // Добавить задание
    private static final String INSERT =
            "INSERT INTO tasks(keeper_id, animal_id, care_id, description, status, date_assigned) " +
            "VALUES (?, ?, ?, ?, ?, ?)";

    // Обновить результат задания
    private static final String UPDATE_RESULT =
            "UPDATE tasks SET status = 'completed', result = ? WHERE id = ?";

    public List<Task> findByKeeper(int keeperId) throws Exception {
        List<Task> tasks = new ArrayList<>();
        try (Connection conn = JdbcConnector.getConnection();
             PreparedStatement ps = conn.prepareStatement(SELECT_BY_KEEPER)) {

            ps.setInt(1, keeperId);
            try (ResultSet rs = ps.executeQuery()) {
                while (rs.next()) {
                    Task t = new Task(
                            rs.getInt("id"),
                            rs.getInt("keeper_id"),
                            rs.getInt("animal_id"),
                            rs.getInt("care_id"),
                            rs.getString("description"),
                            rs.getString("status"),
                            rs.getString("date_assigned"),
                            rs.getString("result")
                    );
                    t.setDescription(t.getDescription()
                            + " [животное: " + rs.getString("animal_name")
                            + ", уход: " + rs.getString("care_desc") + "]");
                    tasks.add(t);
                }
            }
        }
        return tasks;
    }

    public void insert(Task task) throws Exception {
        try (Connection conn = JdbcConnector.getConnection();
             PreparedStatement ps = conn.prepareStatement(INSERT)) {

            ps.setInt(1, task.getKeeperId());
            ps.setInt(2, task.getAnimalId());
            ps.setInt(3, task.getCareId());
            ps.setString(4, task.getDescription());
            ps.setString(5, task.getStatus());
            ps.setString(6, task.getDateAssigned());
            ps.executeUpdate();
        }
    }

    public void updateResult(int taskId, String result) throws Exception {
        try (Connection conn = JdbcConnector.getConnection();
             PreparedStatement ps = conn.prepareStatement(UPDATE_RESULT)) {

            ps.setString(1, result);
            ps.setInt(2, taskId);
            ps.executeUpdate();
        }
    }
}