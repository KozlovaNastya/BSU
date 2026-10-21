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
import java.util.List;
import java.util.Scanner;

public class Main {

    private static final Scanner scanner = new Scanner(System.in);
    private static final AnimalDao animalDao = new AnimalDao();
    private static final CareDao careDao = new CareDao();
    private static final KeeperDao keeperDao = new KeeperDao();
    private static final TaskDao taskDao = new TaskDao();

    public static void main(String[] args) {
        try {
            System.out.println("Зоопарк");
            System.out.println("=====================================");

            // Инициализация БД
            DatabaseInitializer.init();
            DatabaseInitializer.seed();

            // Главный цикл меню
            while (true) {
                printMenu();
                int choice = readInt("Выбор: ");

                switch (choice) {
                    case 1 -> showAllAnimals();
                    case 2 -> showAllCares();
                    case 3 -> showKeeperTasks();
                    case 4 -> assignTask();
                    case 5 -> completeTask();
                    case 0 -> {
                        System.out.println("До свидания!");
                        return;
                    }
                    default -> System.out.println("Неверный выбор");
                }
            }
        } catch (Exception e) {
            System.err.println("Ошибка: " + e.getMessage());
            e.printStackTrace();
        }
    }

    private static void printMenu() {
        System.out.println("\n===== МЕНЮ =====");
        System.out.println("1. Показать всех животных");
        System.out.println("2. Показать возможные действия с животными (уход)");
        System.out.println("3. Показать задания смотрителя");
        System.out.println("4. Назначить задание смотрителю");
        System.out.println("5. Записать результат выполнения задания");
        System.out.println("0. Выход");
    }

    // 1. Все животные
    private static void showAllAnimals() {
        List<Animal> animals = animalDao.findAll();
        System.out.println("\nЖивотные в зоопарке (" + animals.size() + "):");
        System.out.println("--------------------------------------------------");
        for (Animal a : animals) {
            System.out.printf("ID: %d | %s (%s) | возраст: %d | вес: %.1f кг%n",
                    a.getId(), a.getName(), a.getKind(), a.getAge(), a.getWeight());
        }
    }

    // 2. Действия с животными
    private static void showAllCares() throws Exception {
        List<Care> cares = careDao.findAll();
        System.out.println("\nВозможные действия с животными (" + cares.size() + "):");
        System.out.println("--------------------------------------------------");
        for (Care c : cares) {
            System.out.printf("ID: %d | животное №%d | %s | тип: %s%n",
                    c.getId(), c.getAnimalId(), c.getDescription(), c.getType());
        }
    }

    // 3. Задания смотрителя
    private static void showKeeperTasks() throws Exception {
        List<Keeper> keepers = keeperDao.findAll();
        System.out.println("\nСмотрители:");
        for (Keeper k : keepers) {
            System.out.printf("  ID: %d | %s | %s%n", k.getId(), k.getName(), k.getPhone());
        }

        int keeperId = readInt("\nВведите ID смотрителя: ");
        List<Task> tasks = taskDao.findByKeeper(keeperId);
        System.out.println("\nЗадания (" + tasks.size() + "):");
        System.out.println("--------------------------------------------------");
        for (Task t : tasks) {
            System.out.printf("ID: %d | [%s] %s | дата: %s%n",
                    t.getId(), t.getStatus(), t.getDescription(), t.getDateAssigned());
            if (t.getResult() != null) {
                System.out.println("   Результат: " + t.getResult());
            }
        }
    }

    // 4. Назначить задание
    private static void assignTask() throws Exception {
        System.out.println("\nНазначение задания");

        int keeperId = readInt("ID смотрителя: ");
        int animalId = readInt("ID животного: ");
        int careId = readInt("ID ухода: ");
        System.out.print("Описание задания: ");
        String description = scanner.nextLine();

        Task task = new Task();
        task.setKeeperId(keeperId);
        task.setAnimalId(animalId);
        task.setCareId(careId);
        task.setDescription(description);
        task.setStatus("assigned");
        task.setDateAssigned(LocalDate.now().toString());

        taskDao.insert(task);
        System.out.println("Задание назначено!");
    }

    // 5. Записать результат
    private static void completeTask() throws Exception {
        System.out.println("\nЗавершение задания");

        int taskId = readInt("ID задания: ");
        System.out.print("Результат: ");
        String result = scanner.nextLine();

        taskDao.updateResult(taskId, result);
        System.out.println("Результат сохранён!");
    }

    // Утилита: безопасный ввод числа
    private static int readInt(String prompt) {
        while (true) {
            System.out.print(prompt);
            try {
                int value = Integer.parseInt(scanner.nextLine().trim());
                return value;
            } catch (NumberFormatException e) {
                System.out.println("Введите число!");
            }
        }
    }
}