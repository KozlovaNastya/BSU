package zoo.dao;

import jakarta.persistence.EntityManager;
import jakarta.persistence.PersistenceException;
import jakarta.persistence.criteria.CriteriaBuilder;
import jakarta.persistence.criteria.CriteriaQuery;
import jakarta.persistence.criteria.Root;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import zoo.JpaManager;
import zoo.model.Animal;
import zoo.model.Care;
import zoo.model.Keeper;
import zoo.model.Keeper_;
import zoo.model.Task;
import zoo.model.Task_;

import java.util.List;

/** Task DAO. Dynamic, type-safe filters are built with Criteria and Metamodel APIs. */
public class TaskDao {
    private static final Logger logger = LoggerFactory.getLogger(TaskDao.class);

    public List<Task> findAll() {
        try (EntityManager em = JpaManager.getEntityManager()) {
            CriteriaBuilder cb = em.getCriteriaBuilder();
            CriteriaQuery<Task> cq = cb.createQuery(Task.class);
            Root<Task> task = cq.from(Task.class);
            cq.select(task).orderBy(cb.desc(task.get(Task_.id)));
            return em.createQuery(cq).getResultList();
        } catch (PersistenceException | IllegalArgumentException e) {
            logger.error("Unable to load tasks", e);
            return List.of();
        }
    }

    public List<Task> findByKeeper(int keeperId) {
        if (keeperId <= 0) { logger.warn("Invalid keeper id: {}", keeperId); return List.of(); }
        try (EntityManager em = JpaManager.getEntityManager()) {
            CriteriaBuilder cb = em.getCriteriaBuilder();
            CriteriaQuery<Task> cq = cb.createQuery(Task.class);
            Root<Task> task = cq.from(Task.class);
            cq.select(task)
                    .where(cb.equal(task.get(Task_.keeper).get(Keeper_.id), keeperId))
                    .orderBy(cb.desc(task.get(Task_.id)));
            List<Task> result = em.createQuery(cq).getResultList();
            logger.info("Loaded {} tasks for keeper id={}", result.size(), keeperId);
            return result;
        } catch (PersistenceException | IllegalArgumentException e) {
            logger.error("Unable to load tasks for keeper id={}", keeperId, e);
            return List.of();
        }
    }

    public List<Task> findByKeeperAndStatus(int keeperId, String status) {
        try (EntityManager em = JpaManager.getEntityManager()) {
            CriteriaBuilder cb = em.getCriteriaBuilder();
            CriteriaQuery<Task> cq = cb.createQuery(Task.class);
            Root<Task> task = cq.from(Task.class);
            cq.select(task);
            if (status == null || status.isBlank()) {
                cq.where(cb.equal(task.get(Task_.keeper).get(Keeper_.id), keeperId));
            } else {
                cq.where(cb.and(cb.equal(task.get(Task_.keeper).get(Keeper_.id), keeperId),
                        cb.equal(cb.lower(task.get(Task_.status)), status.trim().toLowerCase())));
            }
            cq.orderBy(cb.desc(task.get(Task_.id)));
            return em.createQuery(cq).getResultList();
        } catch (PersistenceException | IllegalArgumentException e) {
            logger.error("Unable to filter tasks for keeper id={}", keeperId, e);
            return List.of();
        }
    }

    public boolean insert(Task task) {
        if (task == null || task.getKeeper() == null || task.getAnimal() == null
                || task.getKeeper().getId() <= 0 || task.getAnimal().getId() <= 0) {
            logger.warn("Cannot assign task: keeper and animal must already exist");
            return false;
        }
        try {
            JpaManager.inTransaction(em -> {
                task.setKeeper(em.getReference(Keeper.class, task.getKeeper().getId()));
                task.setAnimal(em.getReference(Animal.class, task.getAnimal().getId()));
                if (task.getCare() != null)
                    task.setCare(em.getReference(Care.class, task.getCare().getId()));
                em.persist(task);
                return null;
            });
            logger.info("Assigned task id={} to keeper id={}", task.getId(), task.getKeeper().getId());
            return true;
        } catch (RuntimeException e) {
            logger.error("Unable to assign task", e);
            return false;
        }
    }

    public boolean updateResult(int taskId, String result) {
        if (taskId <= 0 || result == null || result.isBlank()) {
            logger.warn("Invalid task completion data: taskId={}", taskId);
            return false;
        }
        try {
            boolean updated = JpaManager.inTransaction(em -> {
                Task task = em.find(Task.class, taskId);
                if (task == null) return false;
                task.setStatus("completed");
                task.setResult(result.trim());
                return true;
            });
            if (updated) logger.info("Task id={} marked as completed", taskId);
            else logger.warn("Task with id={} was not found", taskId);
            return updated;
        } catch (RuntimeException e) {
            logger.error("Unable to update result for task id={}", taskId, e);
            return false;
        }
    }
}
