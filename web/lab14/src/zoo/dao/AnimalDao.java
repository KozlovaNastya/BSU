package zoo.dao;

import jakarta.persistence.EntityManager;
import jakarta.persistence.TypedQuery;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import zoo.JpaManager;
import zoo.model.Animal;
import java.util.List;

public class AnimalDao {
    private static final Logger logger = LoggerFactory.getLogger(AnimalDao.class);

    public List<Animal> findAll() {
        try (EntityManager em = JpaManager.getEntityManager()) {
            List<Animal> result = em.createNamedQuery("Animal.findAll", Animal.class).getResultList();
            logger.info("Loaded {} animals from DB via JPA", result.size());
            return result;
        } catch (Exception e) {
            logger.error("Error loading animals", e);
            return List.of();
        }
    }

    public Animal findById(int id) {
        try (EntityManager em = JpaManager.getEntityManager()) {
            return em.find(Animal.class, id);
        }
    }

    public boolean insert(Animal animal) {
        try (EntityManager em = JpaManager.getEntityManager()) {
            em.getTransaction().begin();
            em.persist(animal);
            em.getTransaction().commit();
            logger.info("Added animal: {}", animal.getName());
            return true;
        } catch (Exception e) {
            logger.error("Error adding animal", e);
            return false;
        }
    }
}
