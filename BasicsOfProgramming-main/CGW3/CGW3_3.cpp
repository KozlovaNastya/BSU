#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <sstream>
#include <algorithm>
#include <windows.h>
using namespace std;
struct Book {
    int udcNumber;                // Номер УДК
    vector<string> authors;       // Список авторов (ФИО)
    string title;                 // Название
    int year;                     // Год издания
    // Оператор сравнения для упорядочивания книг по названию
    bool operator<(const Book& other) const {
        return title < other.title;
    }
};
// Функция для сортировки авторов по фамилиям
void sortAuthors(vector<string>& authors) {
    sort(authors.begin(), authors.end(), [](const string& a, const string& b) {
        return a < b;
        });
}
// Функция добавления книги
void add(set<Book>& library, const Book& newBook) {
    library.insert(newBook);
}
// Функция удаления книги по названию
void remove(set<Book>& library, const string& title) {
    auto it = find_if(library.begin(), library.end(), [&title](const Book& book) {
        return book.title == title;
        });
    if (it != library.end()) {
        library.erase(it);
        cout << "Книга удалена: " << title << endl;
    }
    else cout << "Книга не найдена: " << title << endl;
}
// Функция поиска книги по названию
void findTitle(const set<Book>& library, const string& title) {
    auto it = find_if(library.begin(), library.end(), [&title](const Book& book) {
        return book.title == title;
        });
    if (it != library.end()) {
        cout << "Найдена книга:" << endl;
        cout << "УДК: " << it->udcNumber << endl;
        cout << "Авторы: ";
        for (const auto& author : it->authors)
            cout << author << ", ";
        cout << endl;
        cout << "Название: " << it->title << endl;
        cout << "Год издания: " << it->year << endl << endl;
    }
    else cout << "Книга не найдена: " << title << endl;
}
// Функция поиска книг автора
void findAuthor(const set<Book>& library, const string& author) {
    cout << "Книги автора " << author << ":" << endl;
    for (const auto& book : library) {
        if (find(book.authors.begin(), book.authors.end(), author) != book.authors.end()) {
            cout << "УДК: " << book.udcNumber << endl;
            cout << "Название: " << book.title << endl;
            cout << "Год издания: " << book.year << endl << endl;
        }
    }
}
// Функция добавления автора к книге
void addAuthor(set<Book>& library, const string& title, const string& newAuthor) {
    auto it = find_if(library.begin(), library.end(), [&title](const Book& book) {
        return book.title == title;
        });
    if (it != library.end()) {
        Book updatedBook = *it;
        library.erase(it);
        updatedBook.authors.push_back(newAuthor);
        sortAuthors(updatedBook.authors);
        library.insert(updatedBook);
        cout << "Автор добавлен к книге: " << title << endl;
    }
    else cout << "Книга не найдена: " << title << endl;
}
// Функция удаления автора из книги
void removeAuthor(set<Book>& library, const string& title, const string& author) {
    auto it = find_if(library.begin(), library.end(), [&title](const Book& book) {
        return book.title == title;
        });
    if (it != library.end()) {
        Book updatedBook = *it;
        library.erase(it);
        updatedBook.authors.erase(remove(updatedBook.authors.begin(), updatedBook.authors.end(), author), updatedBook.authors.end());
        library.insert(updatedBook);
        cout << "Автор удалён из книги: " << title << endl;
    }
    else cout << "Книга не найдена: " << title << endl;
}
int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    ifstream inputFile("books.txt");
    if (!inputFile.is_open()) {
        cerr << "Не удалось открыть файл!" << endl;
        return 1;
    }
    if (inputFile.peek() == EOF) {
        cerr << "Файл пуст" << endl;
        return 1;
    }
    set<Book> library;
    string line;
    while (getline(inputFile, line)) {
        istringstream stream(line);
        Book book;
        string authorsLine;
        // Считываем данные о книге
        stream >> book.udcNumber;        
        stream.ignore();                
        getline(stream, authorsLine, ';'); 
        getline(stream, book.title, ';');  
        stream >> book.year;             
        // Разбиваем строку авторов на отдельные ФИО
        istringstream authorsStream(authorsLine);
        string author;
        while (getline(authorsStream, author, ',')) {
            book.authors.push_back(author);
        }
        sortAuthors(book.authors);
        library.insert(book);
    }
    inputFile.close();
    // Демонстрация работы функций
    cout << "Список книг в библиотеке:" << endl;
    for (const auto& book : library) {
        cout << "УДК: " << book.udcNumber << endl;
        cout << "Авторы: ";
        for (const auto& author : book.authors) {
            cout << author << ", ";
        }
        cout << endl;
        cout << "Название: " << book.title << endl;
        cout << "Год издания: " << book.year << endl << endl;
    }
    // Добавление книги
    Book newBook = { 99999, {"Новиков Иван Сергеевич"}, "Алгебра и теория чисел", 2023 };
    add(library, newBook);
    // Удаление книги
    remove(library, "Програмирование");
    // Поиск книги по названию
    findTitle(library, "Алгоритмы");
    // Поиск книг автора
    findAuthor(library, "Петров Петр Петрович");
    // Добавление автора к книге
    addAuthor(library, "Базы данных", "Кузнецов Андрей Андреевич");
    // Удаление автора из книги
    removeAuthor(library, "Базы данных", "Сидоров Сергей Сергеевич");
    cout << "\nИзмененный список книг в библиотеке:" << endl;
    for (const auto& book : library) {
        cout << "УДК: " << book.udcNumber << endl;
        cout << "Авторы: ";
        for (const auto& author : book.authors) {
            cout << author << ", ";
        }
        cout << endl;
        cout << "Название: " << book.title << endl;
        cout << "Год издания: " << book.year << endl << endl;
    }
    return 0;
}