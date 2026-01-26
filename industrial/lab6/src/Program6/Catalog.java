package Program6;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;
// === НОВЫЙ ИМПОРТ ===
import java.util.Date;

public class Catalog implements Serializable {
    private static final long serialVersionUID = 1L;

    private List<Book> books;
    
    // === НОВОЕ ПОЛЕ ===
    private final Date creationDate; // Время создания объекта

    public Catalog() {
        this.books = new ArrayList<>();
        
        // === НОВАЯ ИНИЦИАЛИЗАЦИЯ ===
        this.creationDate = new Date(); // Устанавливаем текущее время создания
    }

    public List<Book> searchByTitle(String title) {
        return books.stream()
                .filter(book -> book.getTitle().toLowerCase().contains(title.toLowerCase()))
                .collect(Collectors.toList());
    }

    public Book searchByIsbn(String isbn) {
        return books.stream()
                .filter(book -> book.getIsbn().equals(isbn))
                .findFirst()
                .orElse(null);
    }

    public void addBook(Book book) {
        if (book != null && searchByIsbn(book.getIsbn()) == null) {
            books.add(book);
        } else {
            throw new IllegalArgumentException("Книга с таким ISBN уже существует в каталоге или книга равна null.");
        }
    }

    public boolean removeBook(Book book) {
        return books.remove(book);
    }

    public List<Book> getAllBooks() {
        return new ArrayList<>(books);
    }
    
    // === НОВЫЙ ГЕТТЕР ===
    public Date getCreationDate() {
        return creationDate;
    }
}