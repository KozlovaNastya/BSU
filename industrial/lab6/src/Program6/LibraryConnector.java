package Program6;

import java.io.*;
import java.util.Optional;

public class LibraryConnector {
    private String filePath;

    public LibraryConnector(String filePath) {
        this.filePath = filePath;
    }

    // Сохранение библиотеки в файл
    public void saveLibrary(Library library) {
        if (library == null) {
            throw new IllegalArgumentException("Библиотека не может быть null.");
        }

        try (ObjectOutputStream oos = new ObjectOutputStream(new FileOutputStream(filePath))) {
            oos.writeObject(library);
            System.out.println("Библиотека успешно сохранена в файл: " + filePath);
        } catch (IOException e) {
            throw new RuntimeException("Ошибка при сохранении библиотеки в файл: " + e.getMessage(), e);
        }
    }

    // Загрузка библиотеки из файла
    public Library loadLibrary() {
        File file = new File(filePath);
        if (!file.exists()) {
            throw new RuntimeException("Файл не найден: " + filePath);
        }

        try (ObjectInputStream ois = new ObjectInputStream(new FileInputStream(filePath))) {
            Library library = (Library) ois.readObject();
            System.out.println("Библиотека успешно загружена из файла: " + filePath);
            return library;
        } catch (IOException | ClassNotFoundException e) {
            throw new RuntimeException("Ошибка при загрузке библиотеки из файла: " + e.getMessage(), e);
        }
    }

    public <T> Optional<T> findObject(String dataFile, java.util.function.Predicate<T> predicate, Class<T> clazz) {
        System.out.println("Для поиска конкретных объектов загрузите библиотеку и используйте ее методы.");
        return Optional.empty();
    }
}