package zoo.dao;

import jakarta.persistence.EntityManager;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import zoo.JpaManager;
import zoo.model.Animal;
import zoo.model.Care;
import zoo.model.Keeper;
import zoo.model.Task;
import java.util.List;

public class TaskDao {
    private static final Logger logger = LoggerFactory.getLogger(TaskDao.class);

    public List<Task> findByKeeper(int keeperId) {
        try (EntityManager em = JpaManager.getEntityManager()) {
            return em.createNamedQuery("Task.findByKeeper", Task.class)
                    .setParameter("keeperId", keeperId).getResultList();
        } catch (Exception e) {
            logger.error("Error loading tasks", e);
            return List.of();
        }
    }

    public boolean insert(Task task) {
        try (EntityManager em = JpaManager.getEntityManager()) {
            em.getTransaction().begin();
            // Подменяем отсоединённые объекты управляемыми ссылками текущего EntityManager.
            task.setKeeper(em.getReference(Keeper.class, task.getKeeper().getId()));
            task.setAnimal(em.getReference(Animal.class, task.getAnimal().getId()));
            if (task.getCare() != null)
                task.setCare(em.getReference(Care.class, task.getCare().getId()));
            em.persist(task);
            em.getTransaction().commit();
            logger.info("Task assigned: {}", task.getDescription());
            return true;
        } catch (Exception e) {
            logger.error("Error assigning task", e);
            return false;
        }
    }

    public boolean updateResult(int taskId, String result) {
        try (EntityManager em = JpaManager.getEntityManager()) {
            em.getTransaction().begin();
            Task task = em.find(Task.class, taskId);
            if (task == null) {
                em.getTransaction().rollback();
                logger.warn("Task with id={} not found", taskId);
                return false;
            }
            task.setStatus("completed");
            task.setResult(result);
            em.getTransaction().commit();
            logger.info("Task {} marked completed", taskId);
            return true;
        } catch (Exception e) {
            logger.error("Error updating task", e);
            return false;
        }
    }
}
