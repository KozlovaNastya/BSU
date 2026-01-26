package Program6;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;
// === НОВЫЙ ИМПОРТ ===
import java.util.Date;

public class Library implements Serializable {
    private static final long serialVersionUID = 1L;

    private Catalog catalog;
    private List<Reader> readers;
    private List<Order> orders;
    
    // === НОВОЕ ПОЛЕ ===
    private final Date creationDate; // Время создания объекта

    public Library() {
        this.catalog = new Catalog();
        this.readers = new ArrayList<>();
        this.orders = new ArrayList<>();
        
        // === НОВАЯ ИНИЦИАЛИЗАЦИЯ ===
        this.creationDate = new Date(); // Устанавливаем текущее время создания
    }

    public void registerReader(Reader reader) {
        if (reader != null && readers.stream().noneMatch(r -> r.getReaderId() == reader.getReaderId())) {
            readers.add(reader);
        } else {
            throw new IllegalArgumentException("Читатель с таким ID уже существует или читатель равен null.");
        }
    }

    public Reader findReaderById(int readerId) {
        return readers.stream()
                .filter(reader -> reader.getReaderId() == readerId)
                .findFirst()
                .orElse(null);
    }

    public Order createOrder(int readerId, String isbn, String orderType) {
        Reader reader = findReaderById(readerId);
        Book book = catalog.searchByIsbn(isbn);

        if (reader == null) {
            throw new IllegalArgumentException("Читатель с ID " + readerId + " не найден.");
        }
        if (reader.isInBlacklist()) {
            throw new IllegalStateException("Читатель " + reader.getFullName() + " находится в черном списке и не может брать книги.");
        }
        if (book == null) {
            throw new IllegalArgumentException("Книга с ISBN " + isbn + " не найдена в каталоге.");
        }
        if (!book.isAvailable()) {
            throw new IllegalStateException("Книга " + book.getTitle() + " в данный момент недоступна.");
        }

        Order order = new Order(reader, book, orderType);
        orders.add(order);
        return order;
    }

    public void completeOrder(int orderId) {
        Order order = orders.stream()
                .filter(o -> o.getOrderId() == orderId && !o.isCompleted())
                .findFirst()
                .orElse(null);

        if (order == null) {
            throw new IllegalArgumentException("Активный заказ с ID " + orderId + " не найден.");
        }

        order.setCompleted(true);
        order.getReader().borrowBook(order.getBook());
    }

    public void addToBlacklist(int readerId) {
        Reader reader = findReaderById(readerId);
        if (reader != null) {
            reader.setInBlacklist(true);
        } else {
            throw new IllegalArgumentException("Читатель с ID " + readerId + " не найден.");
        }
    }

    // Геттеры для доступа к данным
    public Catalog getCatalog() {
        return catalog;
    }

    public List<Reader> getReaders() {
        return new ArrayList<>(readers);
    }

    public List<Order> getOrders() {
        return new ArrayList<>(orders);
    }
    
    // === НОВЫЙ ГЕТТЕР ===
    public Date getCreationDate() {
        return creationDate;
    }
}