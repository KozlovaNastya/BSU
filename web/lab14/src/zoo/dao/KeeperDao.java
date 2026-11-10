package zoo.dao;

import jakarta.persistence.EntityManager;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import zoo.JpaManager;
import zoo.model.Keeper;
import java.util.List;

public class KeeperDao {
    private static final Logger logger = LoggerFactory.getLogger(KeeperDao.class);

    public List<Keeper> findAll() {
        try (EntityManager em = JpaManager.getEntityManager()) {
            List<Keeper> result = em.createNamedQuery("Keeper.findAll", Keeper.class).getResultList();
            logger.info("Loaded {} keepers", result.size());
            return result;
        } catch (Exception e) {
            logger.error("Error loading keepers", e);
            return List.of();
        }
    }

    public boolean insert(Keeper keeper) {
        try (EntityManager em = JpaManager.getEntityManager()) {
            em.getTransaction().begin();
            em.persist(keeper);
            em.getTransaction().commit();
            logger.info("Added keeper: {}", keeper.getName());
            return true;
        } catch (Exception e) {
            logger.error("Error adding keeper", e);
            return false;
        }
    }
}
