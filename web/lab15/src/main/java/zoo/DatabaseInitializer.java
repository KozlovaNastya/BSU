package zoo;

import jakarta.persistence.EntityManager;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import zoo.model.Animal;
import zoo.model.Care;
import zoo.model.Keeper;
import zoo.model.Task;

import java.time.LocalDate;

/** Creates a small demonstration dataset on the first application start. */
public final class DatabaseInitializer {
    private static final Logger logger = LoggerFactory.getLogger(DatabaseInitializer.class);

    private DatabaseInitializer() { }

    public static void initialize() {
        try (EntityManager em = JpaManager.getEntityManager()) {
            Long count = em.createQuery("SELECT COUNT(a) FROM Animal a", Long.class).getSingleResult();
            if (count != null && count > 0) {
                logger.info("Database already contains data; demo seeding skipped");
                return;
            }
        }

        JpaManager.inTransaction(em -> {
            Animal panda = new Animal("Бу", "Панда", 3, 12.5);
            Animal lion = new Animal("Симба", "Лев", 5, 150.0);
            Animal elephant = new Animal("Дамбо", "Слон", 10, 2000.0);
            em.persist(panda);
            em.persist(lion);
            em.persist(elephant);

            Care bamboo = new Care("Кормление бамбуком", "Питание", panda);
            Care checkup = new Care("Медицинский осмотр", "Лечение", panda);
            Care meat = new Care("Кормление мясом", "Питание", lion);
            Care bath = new Care("Купание", "Содержание", elephant);
            em.persist(bamboo);
            em.persist(checkup);
            em.persist(meat);
            em.persist(bath);

            Keeper ivan = new Keeper();
            ivan.setName("Иван Петров");
            ivan.setPhone("+375291234567");
            Keeper maria = new Keeper();
            maria.setName("Мария Сидорова");
            maria.setPhone("+375297654321");
            em.persist(ivan);
            em.persist(maria);

            Task task1 = new Task();
            task1.setDescription("Покормить панду утром");
            task1.setStatus("assigned");
            task1.setDateAssigned(LocalDate.now().toString());
            task1.setKeeper(ivan);
            task1.setAnimal(panda);
            task1.setCare(bamboo);
            em.persist(task1);

            Task task2 = new Task();
            task2.setDescription("Покормить льва");
            task2.setStatus("assigned");
            task2.setDateAssigned(LocalDate.now().toString());
            task2.setKeeper(maria);
            task2.setAnimal(lion);
            task2.setCare(meat);
            em.persist(task2);
            return null;
        });
        logger.info("Demo data initialized");
    }
}
