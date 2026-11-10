package zoo;

import zoo.dao.AnimalDao;
import zoo.dao.CareDao;
import zoo.dao.KeeperDao;
import zoo.dao.TaskDao;
import zoo.model.Animal;
import zoo.model.Care;
import zoo.model.Keeper;
import zoo.model.Task;

import java.time.LocalDate;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import java.util.List;
import java.util.Scanner;

public class Main {
    private static final Logger logger = LoggerFactory.getLogger(Main.class);
    private static final Scanner scanner = new Scanner(System.in);
    private static final AnimalDao animalDao = new AnimalDao();
    private static final CareDao careDao = new CareDao();
    private static final KeeperDao keeperDao = new KeeperDao();
    private static final TaskDao taskDao = new TaskDao();

    public static void main(String[] args) {
        logger.info("Starting Zoo Management System (Criteria API edition)");
        System.out.println("Zoo App (JPA + Criteria API Edition)");
        System.out.println("=====================================");
        try {
            seedDatabaseIfEmpty();
            boolean running = true;
            while (running) {
                printMenu();
                switch (readInt("Выбор: ")) {
                    case 1 -> showAllAnimals();
                    case 2 -> showAllCares();
                    case 3 -> showKeeperTasks();
                    case 4 -> assignTask();
                    case 5 -> completeTask();
                    case 0 -> { System.out.println("До свидания!"); running = false; }
                    default -> {
                        logger.warn("Unknown menu option selected");
                        System.out.println("Неверный выбор.");
                    }
                }
            }
        } catch (ExceptionInInitializerError e) {
            logger.error("JPA initialization failed", e);
            System.err.println("Не удалось инициализировать JPA: " + e.getMessage());
        } catch (Exception e) {
            logger.error("Application terminated because of an unexpected error", e);
            System.err.println("Ошибка приложения: " + e.getMessage());
        } finally {
            try { JpaManager.close(); }
            catch (Throwable e) { logger.warn("JPA resources were not initialized or could not be closed", e); }
            scanner.close();
            logger.info("Application stopped");
        }
    }

    private static void seedDatabaseIfEmpty() {
        // Заполняем каждую таблицу отдельно: предыдущий запуск мог сохранить
        // животных, но завершиться ошибкой до сохранения остальных сущностей.
        List<Animal> animals = animalDao.findAll();
        Animal panda = animals.stream().filter(a -> "Бу".equals(a.getName())).findFirst().orElse(null);
        Animal lion = animals.stream().filter(a -> "Симба".equals(a.getName())).findFirst().orElse(null);

        if (panda == null) {
            panda = new Animal("Бу", "Панда", 3, 12.5);
            if (!animalDao.insert(panda)) throw new IllegalStateException("Не удалось добавить панду");
            panda = animalDao.findAll().stream().filter(a -> "Бу".equals(a.getName())).findFirst().orElseThrow();
        }
        if (lion == null) {
            lion = new Animal("Симба", "Лев", 5, 150.0);
            if (!animalDao.insert(lion)) throw new IllegalStateException("Не удалось добавить льва");
            lion = animalDao.findAll().stream().filter(a -> "Симба".equals(a.getName())).findFirst().orElseThrow();
        }

        List<Care> cares = careDao.findAll();
        final int pandaId = panda.getId();
        final int lionId = lion.getId();
        Care pandaCare = cares.stream().filter(c -> c.getAnimal() != null && c.getAnimal().getId() == pandaId).findFirst().orElse(null);
        Care lionCare = cares.stream().filter(c -> c.getAnimal() != null && c.getAnimal().getId() == lionId).findFirst().orElse(null);
        if (pandaCare == null) {
            pandaCare = new Care("Кормление бамбуком", "Питание", panda);
            if (!careDao.insert(pandaCare)) throw new IllegalStateException("Не удалось добавить уход за пандой");
        }
        if (lionCare == null) {
            lionCare = new Care("Кормление мясом", "Питание", lion);
            if (!careDao.insert(lionCare)) throw new IllegalStateException("Не удалось добавить уход за львом");
        }

        List<Keeper> keepers = keeperDao.findAll();
        Keeper keeper;
        if (keepers.isEmpty()) {
            keeper = new Keeper(0, "Иван Петров", "+375291234567");
            if (!keeperDao.insert(keeper)) throw new IllegalStateException("Не удалось добавить смотрителя");
            keeper = keeperDao.findAll().get(0);
        } else {
            keeper = keepers.get(0);
        }

        if (taskDao.findByKeeper(keeper.getId()).isEmpty()) {
            Task task = new Task();
            task.setDescription("Покормить панду утром");
            task.setStatus("assigned");
            task.setDateAssigned(LocalDate.now().toString());
            task.setKeeper(keeper);
            task.setAnimal(panda);
            task.setCare(pandaCare);
            if (!taskDao.insert(task)) throw new IllegalStateException("Не удалось добавить тестовое задание");
        }
        System.out.println("Проверка начальных данных завершена.");
    }

    private static void printMenu() {
        System.out.println("\n===== МЕНЮ =====");
        System.out.println("1. Показать всех животных");
        System.out.println("2. Показать возможные действия по уходу");
        System.out.println("3. Показать задания смотрителя");
        System.out.println("4. Назначить задание смотрителю");
        System.out.println("5. Записать результат выполнения");
        System.out.println("0. Выход");
    }

    private static void showAllAnimals() {
        List<Animal> animals = animalDao.findAll();
        System.out.println("\nЖивотные (" + animals.size() + "): ");
        for (Animal a : animals)
            System.out.printf("ID: %d | %s (%s) | возраст: %d | вес: %.1f%n",
                    a.getId(), a.getName(), a.getKind(), a.getAge(), a.getWeight());
    }

    private static void showAllCares() {
        List<Care> cares = careDao.findAll();
        System.out.println("\nДействия по уходу (" + cares.size() + "): ");
        for (Care c : cares)
            System.out.printf("ID: %d | %s | тип: %s | животное: %s%n", c.getId(),
                    c.getDescription(), c.getType(), c.getAnimal() == null ? "—" : c.getAnimal().getName());
    }

    private static void showKeeperTasks() {
        List<Keeper> keepers = keeperDao.findAll();
        if (keepers.isEmpty()) { System.out.println("Смотрителей пока нет."); return; }
        System.out.println("\nСмотрители:");
        for (Keeper k : keepers) System.out.printf("ID: %d | %s | %s%n", k.getId(), k.getName(), k.getPhone());
        int keeperId = readInt("Введите ID смотрителя: ");
        List<Task> tasks = taskDao.findByKeeper(keeperId);
        System.out.println("\nЗадания (" + tasks.size() + "): ");
        for (Task t : tasks)
            System.out.printf("ID: %d | [%s] %s | дата: %s | результат: %s%n",
                    t.getId(), t.getStatus(), t.getDescription(), t.getDateAssigned(),
                    t.getResult() == null ? "не указан" : t.getResult());
    }

    private static void assignTask() {
        List<Keeper> keepers = keeperDao.findAll();
        List<Animal> animals = animalDao.findAll();
        List<Care> cares = careDao.findAll();
        if (keepers.isEmpty() || animals.isEmpty()) {
            System.out.println("Для назначения нужны хотя бы один смотритель и одно животное.");
            return;
        }
        System.out.println("\nСмотрители:");
        for (Keeper k : keepers) System.out.printf("%d. %s%n", k.getId(), k.getName());
        int keeperId = readInt("ID смотрителя: ");
        Keeper keeper = keepers.stream().filter(k -> k.getId() == keeperId).findFirst().orElse(null);
        if (keeper == null) { System.out.println("Смотритель не найден."); return; }

        System.out.println("\nЖивотные:");
        for (Animal a : animals) System.out.printf("%d. %s (%s)%n", a.getId(), a.getName(), a.getKind());
        int animalId = readInt("ID животного: ");
        Animal animal = animals.stream().filter(a -> a.getId() == animalId).findFirst().orElse(null);
        if (animal == null) { System.out.println("Животное не найдено."); return; }

        List<Care> matchingCares = cares.stream()
                .filter(c -> c.getAnimal() != null && c.getAnimal().getId() == animalId).toList();
        Care care = null;
        if (!matchingCares.isEmpty()) {
            System.out.println("\nВиды ухода:");
            for (Care c : matchingCares) System.out.printf("%d. %s (%s)%n", c.getId(), c.getDescription(), c.getType());
            int careId = readInt("ID действия по уходу: ");
            care = matchingCares.stream().filter(c -> c.getId() == careId).findFirst().orElse(null);
            if (care == null) { System.out.println("Действие не найдено."); return; }
        }
        System.out.print("Описание задания: ");
        String description = scanner.nextLine().trim();
        if (description.isEmpty()) { System.out.println("Описание не может быть пустым."); return; }

        Task task = new Task();
        task.setDescription(description);
        task.setStatus("assigned");
        task.setDateAssigned(LocalDate.now().toString());
        task.setKeeper(keeper);
        task.setAnimal(animal);
        task.setCare(care);
        System.out.println(taskDao.insert(task) ? "Задание успешно назначено." : "Не удалось назначить задание.");
    }

    private static void completeTask() {
        List<Keeper> keepers = keeperDao.findAll();
        if (keepers.isEmpty()) { System.out.println("Смотрителей пока нет."); return; }
        for (Keeper k : keepers) System.out.printf("ID смотрителя: %d | %s%n", k.getId(), k.getName());
        int keeperId = readInt("ID смотрителя: ");
        List<Task> tasks = taskDao.findByKeeper(keeperId);
        List<Task> assigned = tasks.stream().filter(t -> !"completed".equalsIgnoreCase(t.getStatus())).toList();
        if (assigned.isEmpty()) { System.out.println("Незавершённых заданий нет."); return; }
        for (Task t : assigned) System.out.printf("ID: %d | %s | статус: %s%n", t.getId(), t.getDescription(), t.getStatus());
        int taskId = readInt("ID выполненного задания: ");
        if (assigned.stream().noneMatch(t -> t.getId() == taskId)) {
            System.out.println("У этого смотрителя нет такого незавершённого задания.");
            return;
        }
        System.out.print("Результат выполнения: ");
        String result = scanner.nextLine().trim();
        if (result.isEmpty()) { System.out.println("Результат не может быть пустым."); return; }
        System.out.println(taskDao.updateResult(taskId, result)
                ? "Результат сохранён, задание отмечено выполненным."
                : "Не удалось сохранить результат.");
    }

    private static int readInt(String prompt) {
        while (true) {
            System.out.print(prompt);
            String input = scanner.nextLine().trim();
            try { return Integer.parseInt(input); }
            catch (NumberFormatException e) { logger.warn("Invalid integer entered: '{}'", input); System.out.println("Введите целое число."); }
        }
    }
}
