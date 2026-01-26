package Program6;

import java.io.Serializable;
// === НОВЫЙ ИМПОРТ ===
import java.util.Date;

public class Book implements Serializable {
    private static final long serialVersionUID = 1L;

    private final String isbn;
    private String title;
    private String author;
    private int year;
    private boolean isAvailable;
    private transient String availabilityStatus;
    
    // === НОВОЕ ПОЛЕ ===
    private Date creationDate; // Время создания объекта

    public Book(String isbn, String title, String author, int year) {
        this.isbn = isbn;
        this.title = title;
        this.author = author;
        setYear(year);
        this.isAvailable = true;
        
        // === НОВАЯ ИНИЦИАЛИЗАЦИЯ ===
        this.creationDate = new Date(); // Устанавливаем текущее время создания
        
        calculateAvailabilityStatus();
    }

    // Геттеры и сеттеры
    public String getIsbn() {
        return isbn;
    }

    public String getTitle() {
        return title;
    }

    public void setTitle(String title) {
        this.title = title;
    }

    public String getAuthor() {
        return author;
    }

    public void setAuthor(String author) {
        this.author = author;
    }

    public int getYear() {
        return year;
    }

    public void setYear(int year) {
        if (year < 1450 || year > java.time.Year.now().getValue()) {
            throw new IllegalArgumentException("Недопустимый год издания: " + year);
        }
        this.year = year;
    }

    public boolean isAvailable() {
        return isAvailable;
    }

    public void setAvailable(boolean available) {
        isAvailable = available;
        calculateAvailabilityStatus();
    }

    public String getAvailabilityStatus() {
        return availabilityStatus;
    }
    
    // === НОВЫЙ ГЕТТЕР ===
    public Date getCreationDate() {
        return creationDate;
    }

    private void calculateAvailabilityStatus() {
        this.availabilityStatus = isAvailable ? "Доступна" : "Выдана";
    }
    
    private void readObject(java.io.ObjectInputStream in) throws java.io.IOException, ClassNotFoundException {
        in.defaultReadObject();
        calculateAvailabilityStatus();
        if (creationDate == null) {
            creationDate = new Date();
        }
    }


    @Override
    public String toString() {
        return "Book{" +
                "isbn='" + isbn + '\'' +
                ", title='" + title + '\'' +
                ", author='" + author + '\'' +
                ", year=" + year +
                ", availabilityStatus='" + availabilityStatus + '\'' +
                // === НОВОЕ В toString() ===
                ", creationDate=" + creationDate +
                '}';
    }
}