package Program6;

import java.util.List;
import java.util.Locale;
import java.util.ResourceBundle;
import java.util.Scanner;
// === НОВЫЙ ИМПОРТ ===
import java.text.DateFormat;
import java.text.SimpleDateFormat;

public class main {
    private static Library library;
    private static LibraryConnector connector;
    private static final String DATA_FILE = "library_data.ser";
    private static Scanner scanner = new Scanner(System.in);
    
    // === НОВЫЕ ПЕРЕМЕННЫЕ ДЛЯ ЛОКАЛИЗАЦИИ ===
    private static Locale currentLocale;
    private static ResourceBundle messages;
    private static DateFormat dateFormat;

    public static void main(String[] args) {
        // === ОБРАБОТКА ПАРАМЕТРОВ КОМАНДНОЙ СТРОКИ ДЛЯ ЛОКАЛИЗАЦИИ ===
        if (args.length >= 2) {
            String language = args[0];
            String country = args[1];
            currentLocale = new Locale(language, country);
        } else {
            // Значение по умолчанию - русский, Россия
            currentLocale = new Locale("ru", "RU");
        }
        
        // === ИНИЦИАЛИЗАЦИЯ ЛОКАЛИЗАЦИИ ===
        messages = ResourceBundle.getBundle("Program6.messages", currentLocale);
        dateFormat = DateFormat.getDateTimeInstance(DateFormat.MEDIUM, DateFormat.MEDIUM, currentLocale);
        
        connector = new LibraryConnector(DATA_FILE);

        // Попытка загрузить библиотеку из файла при старте
        try {
            library = connector.loadLibrary();
            System.out.println(messages.getString("library_loaded"));
        } catch (RuntimeException e) {
            System.out.println(messages.getString("load_failed") + ": " + e.getMessage());
            System.out.println(messages.getString("new_library_created"));
            library = new Library();
        }

        boolean running = true;
        while (running) {
            printMenu();
            int choice = readIntInput(messages.getString("choose_option"));

            try {
                switch (choice) {
                    case 1:
                        addBookToCatalog();
                        break;
                    case 2:
                        registerReader();
                        break;
                    case 3:
                        createOrder();
                        break;
                    case 4:
                        completeOrder();
                        break;
                    case 5:
                        addToBlacklist();
                        break;
                    case 6:
                        searchBooks();
                        break;
                    case 7:
                        displayAllInfo();
                        break;
                    case 8:
                        connector.saveLibrary(library);
                        break;
                    case 0:
                        running = false;
                        System.out.println(messages.getString("exit_message"));
                        break;
                    default:
                        System.out.println(messages.getString("invalid_choice"));
                }
            } catch (Exception e) {
                System.out.println(messages.getString("error") + ": " + e.getMessage());
            }
            System.out.println();
        }
        scanner.close();
    }

    private static void printMenu() {
        System.out.println("=== " + messages.getString("system_title") + " ===");
        System.out.println("1. " + messages.getString("add_book"));
        System.out.println("2. " + messages.getString("register_reader"));
        System.out.println("3. " + messages.getString("create_order"));
        System.out.println("4. " + messages.getString("complete_order"));
        System.out.println("5. " + messages.getString("add_blacklist"));
        System.out.println("6. " + messages.getString("search_books"));
        System.out.println("7. " + messages.getString("show_all_info"));
        System.out.println("8. " + messages.getString("save_library"));
        System.out.println("0. " + messages.getString("exit"));
    }

    private static int readIntInput(String prompt) {
        System.out.print(prompt);
        while (!scanner.hasNextInt()) {
            System.out.println(messages.getString("please_enter_number"));
            scanner.next();
            System.out.print(prompt);
        }
        int input = scanner.nextInt();
        scanner.nextLine();
        return input;
    }

    private static String readStringInput(String prompt) {
        System.out.print(prompt);
        return scanner.nextLine();
    }

    private static void addBookToCatalog() {
        System.out.println("--- " + messages.getString("add_book_title") + " ---");
        String isbn = readStringInput(messages.getString("enter_isbn"));
        String title = readStringInput(messages.getString("enter_title"));
        String author = readStringInput(messages.getString("enter_author"));
        int year = readIntInput(messages.getString("enter_year"));

        Book book = new Book(isbn, title, author, year);
        library.getCatalog().addBook(book);
        System.out.println(messages.getString("book_added") + ": " + book.getTitle());
        
        // === НОВЫЙ ВЫВОД ДАТЫ СОЗДАНИЯ ===
        System.out.println(messages.getString("creation_time") + ": " + 
                          dateFormat.format(book.getCreationDate()));
    }

    private static void registerReader() {
        System.out.println("--- " + messages.getString("register_reader_title") + " ---");
        int readerId = readIntInput(messages.getString("enter_reader_id"));
        String fullName = readStringInput(messages.getString("enter_fullname"));
        String passport = readStringInput(messages.getString("enter_passport"));

        Reader reader = new Reader(readerId, fullName, passport);
        library.registerReader(reader);
        System.out.println(messages.getString("reader_registered") + ": " + reader.getFullName());
        
        // === НОВЫЙ ВЫВОД ДАТЫ СОЗДАНИЯ ===
        System.out.println(messages.getString("creation_time") + ": " + 
                          dateFormat.format(reader.getCreationDate()));
    }

    private static void createOrder() {
        System.out.println("--- " + messages.getString("create_order_title") + " ---");
        int readerId = readIntInput(messages.getString("enter_reader_id"));
        String isbn = readStringInput(messages.getString("enter_isbn"));
        String type = readStringInput(messages.getString("enter_order_type"));

        Order order = library.createOrder(readerId, isbn, type);
        System.out.println(messages.getString("order_created") + ": " + order);
        
        // === НОВЫЙ ВЫВОД ДАТЫ СОЗДАНИЯ ===
        System.out.println(messages.getString("creation_time") + ": " + 
                          dateFormat.format(order.getCreationDate()));
    }

    private static void completeOrder() {
        System.out.println("--- " + messages.getString("complete_order_title") + " ---");
        int orderId = readIntInput(messages.getString("enter_order_id"));

        library.completeOrder(orderId);
        System.out.println(messages.getString("order_completed") + " ID " + orderId);
    }

    private static void addToBlacklist() {
        System.out.println("--- " + messages.getString("add_blacklist_title") + " ---");
        int readerId = readIntInput(messages.getString("enter_reader_id"));

        library.addToBlacklist(readerId);
        System.out.println(messages.getString("reader_added_blacklist") + " " + readerId);
    }

    private static void searchBooks() {
        System.out.println("--- " + messages.getString("search_books_title") + " ---");
        String title = readStringInput(messages.getString("enter_search_title"));

        List<Book> foundBooks = library.getCatalog().searchByTitle(title);
        if (foundBooks.isEmpty()) {
            System.out.println(messages.getString("no_books_found"));
        } else {
            System.out.println(messages.getString("found_books"));
            for (Book book : foundBooks) {
                System.out.println("  - " + book.getTitle() + " (" + book.getAuthor() + ")");
                // === НОВЫЙ ВЫВОД ДАТЫ СОЗДАНИЯ ===
                System.out.println("    " + messages.getString("creation_time") + ": " + 
                                  dateFormat.format(book.getCreationDate()));
            }
        }
    }

    private static void displayAllInfo() {
        System.out.println("--- " + messages.getString("all_info_title") + " ---");

        System.out.println("\n" + messages.getString("catalog_books"));
        List<Book> books = library.getCatalog().getAllBooks();
        if (books.isEmpty()) {
            System.out.println("  " + messages.getString("catalog_empty"));
        } else {
            for (Book book : books) {
                System.out.println("  - " + book);
            }
        }

        System.out.println("\n" + messages.getString("registered_readers"));
        List<Reader> readers = library.getReaders();
        if (readers.isEmpty()) {
            System.out.println("  " + messages.getString("no_readers"));
        } else {
            for (Reader reader : readers) {
                System.out.println("  - " + reader);
            }
        }

        System.out.println("\n" + messages.getString("orders"));
        List<Order> orders = library.getOrders();
        if (orders.isEmpty()) {
            System.out.println("  " + messages.getString("no_orders"));
        } else {
            for (Order order : orders) {
                System.out.println("  - " + order);
            }
        }
        
        // === НОВЫЙ ВЫВОД ДАТЫ СОЗДАНИЯ БИБЛИОТЕКИ ===
        System.out.println("\n" + messages.getString("library_creation_time") + ": " + 
                          dateFormat.format(library.getCreationDate()));
    }
}