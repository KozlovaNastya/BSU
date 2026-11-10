package zoo.dao;

import jakarta.persistence.EntityManager;
import jakarta.persistence.PersistenceException;
import jakarta.persistence.criteria.CriteriaBuilder;
import jakarta.persistence.criteria.CriteriaQuery;
import jakarta.persistence.criteria.Root;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import zoo.JpaManager;
import zoo.model.Animal_;
import zoo.model.Care;
import zoo.model.Care_;

import java.util.List;

/** Data access operations for care activities, implemented with Criteria API. */
public class CareDao {
    private static final Logger logger = LoggerFactory.getLogger(CareDao.class);

    public List<Care> findAll() {
        try (EntityManager em = JpaManager.getEntityManager()) {
            CriteriaBuilder cb = em.getCriteriaBuilder();
            CriteriaQuery<Care> cq = cb.createQuery(Care.class);
            Root<Care> care = cq.from(Care.class);
            cq.select(care).orderBy(cb.asc(care.get(Care_.id)));
            List<Care> result = em.createQuery(cq).getResultList();
            logger.info("Loaded {} care activities", result.size());
            return result;
        } catch (PersistenceException | IllegalArgumentException e) {
            logger.error("Unable to load care activities", e);
            return List.of();
        }
    }

    public Care findById(int id) {
        if (id <= 0) { logger.warn("Invalid care id: {}", id); return null; }
        try (EntityManager em = JpaManager.getEntityManager()) {
            CriteriaBuilder cb = em.getCriteriaBuilder();
            CriteriaQuery<Care> cq = cb.createQuery(Care.class);
            Root<Care> care = cq.from(Care.class);
            cq.select(care).where(cb.equal(care.get(Care_.id), id));
            return em.createQuery(cq).getResultStream().findFirst().orElse(null);
        } catch (PersistenceException | IllegalArgumentException e) {
            logger.error("Unable to find care activity with id={}", id, e);
            return null;
        }
    }

    public List<Care> findByAnimalId(int animalId) {
        try (EntityManager em = JpaManager.getEntityManager()) {
            CriteriaBuilder cb = em.getCriteriaBuilder();
            CriteriaQuery<Care> cq = cb.createQuery(Care.class);
            Root<Care> care = cq.from(Care.class);
            cq.select(care)
                    .where(cb.equal(care.get(Care_.animal).get(Animal_.id), animalId))
                    .orderBy(cb.asc(care.get(Care_.id)));
            return em.createQuery(cq).getResultList();
        } catch (PersistenceException | IllegalArgumentException e) {
            logger.error("Unable to find care activities for animal id={}", animalId, e);
            return List.of();
        }
    }

    public boolean insert(Care care) {
        if (care == null || care.getAnimal() == null || care.getAnimal().getId() <= 0) {
            logger.warn("Cannot insert care activity without a persisted animal");
            return false;
        }
        try {
            JpaManager.inTransaction(em -> {
                care.setAnimal(em.getReference(zoo.model.Animal.class, care.getAnimal().getId()));
                em.persist(care);
                return null;
            });
            logger.info("Added care activity '{}' with id={}", care.getDescription(), care.getId());
            return true;
        } catch (RuntimeException e) {
            logger.error("Unable to insert care activity", e);
            return false;
        }
    }
}
