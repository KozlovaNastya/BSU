package zoo.dao;

import jakarta.persistence.EntityManager;
import jakarta.persistence.PersistenceException;
import jakarta.persistence.TypedQuery;
import jakarta.persistence.criteria.CriteriaBuilder;
import jakarta.persistence.criteria.CriteriaQuery;
import jakarta.persistence.criteria.Predicate;
import jakarta.persistence.criteria.Root;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import zoo.JpaManager;
import zoo.model.Animal;
import zoo.model.Animal_;

import java.util.ArrayList;
import java.util.List;

/** Data access operations for animals. All reads use the Criteria API and static metamodel. */
public class AnimalDao {
    private static final Logger logger = LoggerFactory.getLogger(AnimalDao.class);

    public List<Animal> findAll() {
        try (EntityManager em = JpaManager.getEntityManager()) {
            CriteriaBuilder cb = em.getCriteriaBuilder();
            CriteriaQuery<Animal> cq = cb.createQuery(Animal.class);
            Root<Animal> animal = cq.from(Animal.class);
            cq.select(animal).orderBy(cb.asc(animal.get(Animal_.id)));
            List<Animal> result = em.createQuery(cq).getResultList();
            logger.info("Loaded {} animals", result.size());
            return result;
        } catch (PersistenceException | IllegalArgumentException e) {
            logger.error("Unable to load animals", e);
            return List.of();
        }
    }

    public Animal findById(int id) {
        if (id <= 0) { logger.warn("Invalid animal id: {}", id); return null; }
        try (EntityManager em = JpaManager.getEntityManager()) {
            CriteriaBuilder cb = em.getCriteriaBuilder();
            CriteriaQuery<Animal> cq = cb.createQuery(Animal.class);
            Root<Animal> animal = cq.from(Animal.class);
            cq.select(animal).where(cb.equal(animal.get(Animal_.id), id));
            return em.createQuery(cq).getResultStream().findFirst().orElse(null);
        } catch (PersistenceException | IllegalArgumentException e) {
            logger.error("Unable to find animal with id={}", id, e);
            return null;
        }
    }

    /** Demonstrates dynamic filters: any argument may be null and will be ignored. */
    public List<Animal> search(String kind, Integer minAge, Integer maxAge) {
        try (EntityManager em = JpaManager.getEntityManager()) {
            CriteriaBuilder cb = em.getCriteriaBuilder();
            CriteriaQuery<Animal> cq = cb.createQuery(Animal.class);
            Root<Animal> animal = cq.from(Animal.class);
            List<Predicate> predicates = new ArrayList<>();
            if (kind != null && !kind.isBlank())
                predicates.add(cb.equal(animal.get(Animal_.kind), kind.trim()));
            if (minAge != null) predicates.add(cb.greaterThanOrEqualTo(animal.get(Animal_.age), minAge));
            if (maxAge != null) predicates.add(cb.lessThanOrEqualTo(animal.get(Animal_.age), maxAge));
            cq.select(animal).where(predicates.toArray(Predicate[]::new))
                    .orderBy(cb.asc(animal.get(Animal_.name)));
            return em.createQuery(cq).getResultList();
        } catch (PersistenceException | IllegalArgumentException e) {
            logger.error("Unable to search animals", e);
            return List.of();
        }
    }

    public boolean insert(Animal animal) {
        if (animal == null) { logger.warn("Cannot insert a null animal"); return false; }
        try {
            JpaManager.inTransaction(em -> { em.persist(animal); return null; });
            logger.info("Added animal '{}' with id={}", animal.getName(), animal.getId());
            return true;
        } catch (RuntimeException e) {
            logger.error("Unable to insert animal", e);
            return false;
        }
    }
}
