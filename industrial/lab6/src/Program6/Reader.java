package Program6;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;
// === НОВЫЙ ИМПОРТ ===
import java.util.Date;

public class Reader implements Serializable {
    private static final long serialVersionUID = 1L;

    private final int readerId;
    private String fullName;
    private String passportNumber;
    private boolean isInBlacklist;
    private transient List<Book> borrowedBooks;
    
    // === НОВОЕ ПОЛЕ ===
    private Date creationDate; // Время создания объекта

    public Reader(int readerId, String fullName, String passportNumber) {
        this.readerId = readerId;
        this.fullName = fullName;
        this.passportNumber = passportNumber;
        this.isInBlacklist = false;
        this.borrowedBooks = new ArrayList<>();
        
        // === НОВАЯ ИНИЦИАЛИЗАЦИЯ ===
        this.creationDate = new Date(); // Устанавливаем текущее время создания
    }

    // Геттеры и сеттеры
    public int getReaderId() {
        return readerId;
    }

    public String getFullName() {
        return fullName;
    }

    public void setFullName(String fullName) {
        this.fullName = fullName;
    }

    public String getPassportNumber() {
        return passportNumber;
    }

    public void setPassportNumber(String passportNumber) {
        this.passportNumber = passportNumber;
    }

    public boolean isInBlacklist() {
        return isInBlacklist;
    }

    public void setInBlacklist(boolean inBlacklist) {
        isInBlacklist = inBlacklist;
    }

    public List<Book> getBorrowedBooks() {
        return borrowedBooks;
    }
    
    // === НОВЫЙ ГЕТТЕР ===
    public Date getCreationDate() {
        return creationDate;
    }

    public void borrowBook(Book book) {
        if (book != null && book.isAvailable()) {
            borrowedBooks.add(book);
            book.setAvailable(false);
        }
    }

    public void returnBook(Book book) {
        if (borrowedBooks.remove(book)) {
            book.setAvailable(true);
        }
    }
    
    private void readObject(java.io.ObjectInputStream in) throws java.io.IOException, ClassNotFoundException {
        in.defaultReadObject();
        this.borrowedBooks = new ArrayList<>();
        if (creationDate == null) {
            creationDate = new Date();
        }
    }

    @Override
    public String toString() {
        return "Reader{" +
                "readerId=" + readerId +
                ", fullName='" + fullName + '\'' +
                ", passportNumber='" + passportNumber + '\'' +
                ", isInBlacklist=" + isInBlacklist +
                ", borrowedBooksCount=" + borrowedBooks.size() +
                // === НОВОЕ В toString() ===
                ", creationDate=" + creationDate +
                '}';
    }
}