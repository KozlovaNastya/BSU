package Program6;

import java.io.Serializable;
import java.time.LocalDate;
// === НОВЫЙ ИМПОРТ ===
import java.util.Date;

public class Order implements Serializable {
    private static final long serialVersionUID = 1L;

    private final int orderId;
    private final Reader reader;
    private final Book book;
    private final LocalDate orderDate;
    private final String type;
    private boolean isCompleted;
    
    // === НОВОЕ ПОЛЕ ===
    private final Date creationDate; // Время создания объекта

    private static int nextOrderId = 1;

    public Order(Reader reader, Book book, String type) {
        this.orderId = nextOrderId++;
        this.reader = reader;
        this.book = book;
        this.orderDate = LocalDate.now();
        
        if (!"абонемент".equals(type) && !"читальный зал".equals(type)) {
            throw new IllegalArgumentException("Тип заказа должен быть 'абонемент' или 'читальный зал'");
        }
        this.type = type;
        this.isCompleted = false;
        
        // === НОВАЯ ИНИЦИАЛИЗАЦИЯ ===
        this.creationDate = new Date(); // Устанавливаем текущее время создания
    }

    // Геттеры
    public int getOrderId() {
        return orderId;
    }

    public Reader getReader() {
        return reader;
    }

    public Book getBook() {
        return book;
    }

    public LocalDate getOrderDate() {
        return orderDate;
    }

    public String getType() {
        return type;
    }

    public boolean isCompleted() {
        return isCompleted;
    }

    public void setCompleted(boolean completed) {
        isCompleted = completed;
    }
    
    // === НОВЫЙ ГЕТТЕР ===
    public Date getCreationDate() {
        return creationDate;
    }

    @Override
    public String toString() {
        return "Order{" +
                "orderId=" + orderId +
                ", reader=" + reader.getFullName() +
                ", book=" + book.getTitle() +
                ", orderDate=" + orderDate +
                ", type='" + type + '\'' +
                ", isCompleted=" + isCompleted +
                // === НОВОЕ В toString() ===
                ", creationDate=" + creationDate +
                '}';
    }
}