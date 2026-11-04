
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// Book class
class Book {
private:
    string title;
    string author;
    int pages;
    string id;
    bool borrowed;

public:
    // Constructor
    Book(string t, string a, int p, string i, bool b) {
        title = t;
        author = a;
        pages = p;
        id = i;
        borrowed = b;
    }

    // Display book information
    void displayBook() {
        cout << "\nTitle: " << title;
        cout << "\nAuthor: " << author;
        cout << "\nPages: " << pages;
        cout << "\nBook ID: " << id;
        cout << "\nStatus: " << (borrowed ? "Borrowed" : "Available");
        cout << "\n-----------------------------\n";
    }

    // Get book ID
    string getID() {
        return id;
    }

    // Borrow a book
    void borrowBook() {
        if (!borrowed) {
            borrowed = true;
            cout << "Book borrowed successfully!\n";
        } else {
            cout << "This book is already borrowed.\n";
        }
    }

    // Return a book
    void returnBook() {
        if (borrowed) {
            borrowed = false;
            cout << "Book returned successfully!\n";
        } else {
            cout << "This book is already available.\n";
        }
    }
};

// Load books from file
void loadBooks(vector<Book>& books) {
    ifstream file("bookData.txt");

    if (!file.is_open()) {
        cout << "Error: Could not open bookData.txt\n";
        return;
    }

    string line;

    while (getline(file, line)) {
        stringstream ss(line);

        string title, author, id, borrowedText;
        int pages;

        getline(ss, title, ',');
        getline(ss, author, ',');
        ss >> pages;
        ss.ignore(1, ',');
        getline(ss, id, ',');
        getline(ss, borrowedText);

        bool borrowed = (borrowedText == "true");

        books.push_back(Book(title, author, pages, id, borrowed));
    }

    file.close();
}

// Display all books
void displayAllBooks(vector<Book>& books) {
    if (books.empty()) {
        cout << "No books found.\n";
        return;
    }

    for (int i = 0; i < books.size(); i++) {
        books[i].displayBook();
    }
}

// Find a book using its ID
void findBook(vector<Book>& books) {
    string searchID;

    cout << "Enter book ID (e.g. 001): ";
    cin >> searchID;

    for (int i = 0; i < books.size(); i++) {
        if (books[i].getID() == searchID) {
            books[i].displayBook();
            return;
        }
    }

    cout << "Book not found.\n";
}

// Main program
int main() {
    vector<Book> books;

    loadBooks(books);

    if (books.empty()) {
        cout << "No books loaded. Check bookData.txt.\n";
        return 1;
    }

    int choice;

    do {
        cout << "\n===== BOOK MANAGER =====\n";
        cout << "1. View all books\n";
        cout << "2. Find a book by ID\n";
        cout << "3. Borrow a book\n";
        cout << "4. Return a book\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";

        cin >> choice;

        if (choice == 1) {
            displayAllBooks(books);
        }
        else if (choice == 2) {
            findBook(books);
        }
        else if (choice == 3 || choice == 4) {
            string searchID;
            bool found = false;

            cout << "Enter book ID (e.g. 001): ";
            cin >> searchID;

            for (int i = 0; i < books.size(); i++) {
                if (books[i].getID() == searchID) {
                    if (choice == 3) {
                        books[i].borrowBook();
                    } else {
                        books[i].returnBook();
                    }

                    found = true;
                    break;
                }
            }

            if (!found) {
                cout << "Book not found.\n";
            }
        }
        else if (choice == 5) {
            cout << "Goodbye!\n";
        }
        else {
            cout << "Invalid option. Please try again.\n";
        }

    } while (choice != 5);

    return 0;
}
