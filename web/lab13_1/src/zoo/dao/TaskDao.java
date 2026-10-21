package zoo.dao;

import zoo.DatabaseConnector;
import zoo.model.Task;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.ArrayList;
import java.util.List;

public class TaskDao {
    private static final Logger logger = LoggerFactory.getLogger(TaskDao.class);

    private static final String SELECT_BY_KEEPER =
            "SELECT t.*, a.name AS animal_name, c.description AS care_desc " +
            "FROM tasks t " +
            "JOIN animals a ON t.animal_id = a.id " +
            "JOIN cares c ON t.care_id = c.id " +
            "WHERE t.keeper_id = ?";

    private static final String INSERT =
            "INSERT INTO tasks(keeper_id, animal_id, care_id, description, status, date_assigned) " +
            "VALUES (?, ?, ?, ?, ?, ?)";

    private static final String UPDATE_RESULT =
            "UPDATE tasks SET status = 'completed', result = ? WHERE id = ?";

    public List<Task> findByKeeper(int keeperId) {
        List<Task> tasks = new ArrayList<>();
        Connection conn = null;
        try {
            conn = DatabaseConnector.getConnection();
            try (PreparedStatement ps = conn.prepareStatement(SELECT_BY_KEEPER)) {

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
                                + " [animal: " + rs.getString("animal_name")
                                + ", care: " + rs.getString("care_desc") + "]");
                        tasks.add(t);
                    }
                }
            }
            logger.info("Loaded {} tasks for keeper id={}", tasks.size(), keeperId);
        } catch (Exception e) {
            logger.error("Error loading tasks for keeper id=" + keeperId, e);
        } finally {
            DatabaseConnector.releaseConnection(conn);
        }
        return tasks;
    }

    public void insert(Task task) {
        Connection conn = null;
        try {
            conn = DatabaseConnector.getConnection();
            try (PreparedStatement ps = conn.prepareStatement(INSERT)) {
                ps.setInt(1, task.getKeeperId());
                ps.setInt(2, task.getAnimalId());
                ps.setInt(3, task.getCareId());
                ps.setString(4, task.getDescription());
                ps.setString(5, task.getStatus());
                ps.setString(6, task.getDateAssigned());
                ps.executeUpdate();
            }
            logger.info("Task assigned to keeper id={}", task.getKeeperId());
        } catch (Exception e) {
            logger.error("Error assigning task", e);
        } finally {
            DatabaseConnector.releaseConnection(conn);
        }
    }

    public void updateResult(int taskId, String result) {
        Connection conn = null;
        try {
            conn = DatabaseConnector.getConnection();
            try (PreparedStatement ps = conn.prepareStatement(UPDATE_RESULT)) {
                ps.setString(1, result);
                ps.setInt(2, taskId);
                ps.executeUpdate();
            }
            logger.info("Task id={} completed with result: {}", taskId, result);
        } catch (Exception e) {
            logger.error("Error updating task id=" + taskId, e);
        } finally {
            DatabaseConnector.releaseConnection(conn);
        }
    }
}