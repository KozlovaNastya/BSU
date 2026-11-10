package zoo.dao;

import jakarta.persistence.EntityManager;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import zoo.JpaManager;
import zoo.model.Animal;
import zoo.model.Care;
import java.util.List;

public class CareDao {
    private static final Logger logger = LoggerFactory.getLogger(CareDao.class);

    public List<Care> findAll() {
        try (EntityManager em = JpaManager.getEntityManager()) {
            List<Care> result = em.createNamedQuery("Care.findAll", Care.class).getResultList();
            logger.info("Loaded {} care records", result.size());
            return result;
        } catch (Exception e) {
            logger.error("Error loading care records", e);
            return List.of();
        }
    }

    public Care findById(int id) {
        try (EntityManager em = JpaManager.getEntityManager()) {
            return em.find(Care.class, id);
        }
    }

    public boolean insert(Care care) {
        try (EntityManager em = JpaManager.getEntityManager()) {
            em.getTransaction().begin();
            care.setAnimal(em.getReference(Animal.class, care.getAnimal().getId()));
            em.persist(care);
            em.getTransaction().commit();
            logger.info("Added care record: {}", care.getDescription());
            return true;
        } catch (Exception e) {
            logger.error("Error adding care record", e);
            return false;
        }
    }
}
