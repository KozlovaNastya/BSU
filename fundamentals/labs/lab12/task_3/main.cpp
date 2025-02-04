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
    int udcNumber;
    vector<string> authors;
    string title;
    int year; 
    bool operator<(const Book& other) const {
        return title < other.title;
    }
};

void sortAuthors(vector<string>& authors) {
    sort(authors.begin(), authors.end(), [](const string& a, const string& b) {
        return a < b;
    });
}

void add(set<Book>& library, const Book& newBook) {
    library.insert(newBook);
}

void remove(set<Book>& library, const string& title) {
    auto it = find_if(library.begin(), library.end(), [&title](const Book& book) {
        return book.title == title;
    });
    if (it != library.end()) {
        library.erase(it);
        cout << "Book removed: " << title << endl;
    }
    else cout << "Book not found: " << title << endl;
}

void findTitle(const set<Book>& library, const string& title) {
    auto it = find_if(library.begin(), library.end(), [&title](const Book& book) {
        return book.title == title;
    });
    if (it != library.end()) {
        cout << "Book found:" << endl;
        cout << "UDC: " << it->udcNumber << endl;
        cout << "Authors: ";
        for (const auto& author : it->authors)
            cout << author << ", ";
        cout << endl;
        cout << "Title: " << it->title << endl;
        cout << "Year of publication: " << it->year << endl << endl;
    }
    else cout << "Book not found: " << title << endl;
}

void findAuthor(const set<Book>& library, const string& author) {
    cout << "Books by the author " << author << ":" << endl;
    for (const auto& book : library) {
        if (find(book.authors.begin(), book.authors.end(), author) != book.authors.end()) {
            cout << "UDC: " << book.udcNumber << endl;
            cout << "Title: " << book.title << endl;
            cout << "Year of publication: " << book.year << endl << endl;
        }
    }
}

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
        cout << "Author added to book: " << title << endl;
    }
    else cout << "Book not found: " << title << endl;
}

void removeAuthor(set<Book>& library, const string& title, const string& author) {
    auto it = find_if(library.begin(), library.end(), [&title](const Book& book) {
        return book.title == title;
    });
    if (it != library.end()) {
        Book updatedBook = *it;
        library.erase(it);
        updatedBook.authors.erase(remove(updatedBook.authors.begin(), updatedBook.authors.end(), author), updatedBook.authors.end());
        library.insert(updatedBook);
        cout << "Author removed from book: " << title << endl;
    }
    else cout << "Book not found: " << title << endl;
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    ifstream inputFile("books.txt");
    if (!inputFile.is_open()) {
        cerr << "Failed to open file!" << endl;
        return 1;
    }

    if (inputFile.peek() == EOF) {
        cerr << "File is empty" << endl;
        return 1;
    }

    set<Book> library;
    string line;
    while (getline(inputFile, line)) {
        istringstream stream(line);
        Book book;
        string authorsLine;
        
        // Read book data
        stream >> book.udcNumber;        
        stream.ignore();                
        getline(stream, authorsLine, ';'); 
        getline(stream, book.title, ';');  
        stream >> book.year;             
        
        // Split the author string into individual names
        istringstream authorsStream(authorsLine);
        string author;
        while (getline(authorsStream, author, ',')) {
            book.authors.push_back(author);
        }

        sortAuthors(book.authors);
        library.insert(book);
    }
    
    inputFile.close();

    cout << "List of books in the library:" << endl;
    for (const auto& book : library) {
        cout << "UDC: " << book.udcNumber << endl;
        cout << "Authors: ";
        for (const auto& author : book.authors) {
            cout << author << ", ";
        }
        cout << endl;
        cout << "Title: " << book.title << endl;
        cout << "Year of publication: " << book.year << endl << endl;
    }

    // Example operations
    Book newBook = { 99999, {"Novikov Ivan Sergeevich"}, "Algebra and Number Theory", 2023 };
    add(library, newBook);
    remove(library, "Programming");
    findTitle(library, "Algorithms");
    findAuthor(library, "Petrov Petr Petrovich");
    addAuthor(library, "Databases", "Kuznetsov Andrey Andreevich");
    removeAuthor(library, "Databases", "Sidorov Sergey Sergeevich");

    cout << "\nUpdated list of books in the library:" << endl;
    for (const auto& book : library) {
        cout << "UDC: " << book.udcNumber << endl;
        cout << "Authors: ";
        for (const auto& author : book.authors) {
            cout << author << ", ";
        }
        cout << endl;
        cout << "Title: " << book.title << endl;
        cout << "Year of publication: " << book.year << endl << endl;
    }

    return 0;
}
