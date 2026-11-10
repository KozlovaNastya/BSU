package zoo.dao;

import jakarta.persistence.EntityManager;
import jakarta.persistence.PersistenceException;
import jakarta.persistence.criteria.CriteriaBuilder;
import jakarta.persistence.criteria.CriteriaQuery;
import jakarta.persistence.criteria.Root;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import zoo.JpaManager;
import zoo.model.Keeper;
import zoo.model.Keeper_;

import java.util.List;

/** Data access operations for keepers, implemented with Criteria API. */
public class KeeperDao {
    private static final Logger logger = LoggerFactory.getLogger(KeeperDao.class);

    public List<Keeper> findAll() {
        try (EntityManager em = JpaManager.getEntityManager()) {
            CriteriaBuilder cb = em.getCriteriaBuilder();
            CriteriaQuery<Keeper> cq = cb.createQuery(Keeper.class);
            Root<Keeper> keeper = cq.from(Keeper.class);
            cq.select(keeper).orderBy(cb.asc(keeper.get(Keeper_.id)));
            List<Keeper> result = em.createQuery(cq).getResultList();
            logger.info("Loaded {} keepers", result.size());
            return result;
        } catch (PersistenceException | IllegalArgumentException e) {
            logger.error("Unable to load keepers", e);
            return List.of();
        }
    }

    public List<Keeper> searchByName(String namePart) {
        try (EntityManager em = JpaManager.getEntityManager()) {
            CriteriaBuilder cb = em.getCriteriaBuilder();
            CriteriaQuery<Keeper> cq = cb.createQuery(Keeper.class);
            Root<Keeper> keeper = cq.from(Keeper.class);
            if (namePart == null || namePart.isBlank()) {
                cq.select(keeper);
            } else {
                cq.select(keeper).where(cb.like(keeper.get(Keeper_.name),
                        "%" + namePart.trim() + "%"));
            }
            cq.orderBy(cb.asc(keeper.get(Keeper_.name)));
            return em.createQuery(cq).getResultList();
        } catch (PersistenceException | IllegalArgumentException e) {
            logger.error("Unable to search keepers", e);
            return List.of();
        }
    }

    public boolean insert(Keeper keeper) {
        if (keeper == null) { logger.warn("Cannot insert a null keeper"); return false; }
        try {
            JpaManager.inTransaction(em -> { em.persist(keeper); return null; });
            logger.info("Added keeper '{}' with id={}", keeper.getName(), keeper.getId());
            return true;
        } catch (RuntimeException e) {
            logger.error("Unable to insert keeper", e);
            return false;
        }
    }
}
