
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>
using namespace std;

// Function for integer input
int readInt() {
    string input;
    int num;
    char extra;

    getline(cin, input);
    stringstream ss(input);

    if (ss >> num && !(ss >> extra)) {
        return num;
    }

    return -1;
}

// ======================================
// 1. BASE CLASS
// ======================================

class User {
protected:
    string name;
    string userID;

public:
    User(string n, string id) {
        name = n;
        userID = id;
    }

    virtual void displayRole() = 0;

    virtual ~User() {}
};

// ======================================
// 2. STUDENT CLASS
// ======================================

class Student : public User {
public:
    Student(string n, string id) : User(n, id) {}

    void displayRole() override {
        cout << "\nStudent Name: " << name;
        cout << "\nStudent ID: " << userID << endl;
    }
};

// ======================================
// 3. LIBRARIAN CLASS
// ======================================

class Librarian : public User {
public:
    Librarian(string n, string id) : User(n, id) {}

    void displayRole() override {
        cout << "\nLibrarian Name: " << name;
        cout << "\nEmployee ID: " << userID << endl;
    }
};

// ======================================
// 4. BOOK CLASS
// ======================================

class Book {
private:
    int bookID;
    string title;
    string author;
    int quantity;
    int available;

public:

    // Default constructor
    Book() {
        bookID = 0;
        title = "";
        author = "";
        quantity = 0;
        available = 0;
    }

    // Parameterized constructor
    Book(int id, string t, string a, int q) {
        bookID = id;
        title = t;
        author = a;
        quantity = q;
        available = q;
    }

    int getID() const {
        return bookID;
    }

    int getQuantity() const {
        return quantity;
    }

    int getAvailable() const {
        return available;
    }

    // Set available quantity
    void setAvailable(int a) {
        available = a;
    }

    // Update book details
    void updateBook(string t, string a, int q) {
        int issued = quantity - available;

        title = t;
        author = a;
        quantity = q;
        available = q - issued;
    }

    // Issue book
    void issueBook() {
        if (available > 0) {
            available--;
        }
    }

    // Return book
    void returnBook() {
        if (available < quantity) {
            available++;
        }
    }

    // Display book details
    void displayBook() const {
        cout << "\nBook ID: " << bookID;
        cout << "\nTitle: " << title;
        cout << "\nAuthor: " << author;
        cout << "\nTotal Quantity: " << quantity;
        cout << "\nAvailable Copies: " << available;

        if (available > 0) {
            cout << "\nStatus: Available";
        }
        else {
            cout << "\nStatus: Not Available";
        }

        cout << "\n--------------------------------\n";
    }

    // Save book data
    void saveBook(ofstream &file) const {
        file << bookID << " "
             << quoted(title) << " "
             << quoted(author) << " "
             << quantity << " "
             << available << endl;
    }

    // Load book data
    bool loadBook(ifstream &file) {
        return bool(file >> bookID
                     >> quoted(title)
                     >> quoted(author)
                     >> quantity
                     >> available);
    }
};

// ======================================
// 5. ISSUE RECORD CLASS
// ======================================

class IssueRecord {
private:
    int issueID;
    int bookID;
    string studentName;
    string studentID;

public:

    // Default constructor
    IssueRecord() {
        issueID = 0;
        bookID = 0;
        studentName = "";
        studentID = "";
    }

    // Parameterized constructor
    IssueRecord(int iid, int bid, string name, string sid) {
        issueID = iid;
        bookID = bid;
        studentName = name;
        studentID = sid;
    }

    int getIssueID() const {
        return issueID;
    }

    int getBookID() const {
        return bookID;
    }

    // Display issue record
    void displayRecord() const {
        cout << "\nIssue ID: " << issueID;
        cout << "\nBook ID: " << bookID;
        cout << "\nStudent Name: " << studentName;
        cout << "\nStudent ID: " << studentID;
        cout << "\n--------------------------------\n";
    }

    // Save issue record
    void saveRecord(ofstream &file) const {
        file << issueID << " "
             << bookID << " "
             << quoted(studentName) << " "
             << quoted(studentID) << endl;
    }

    // Load issue record
    bool loadRecord(ifstream &file) {
        return bool(file >> issueID
                     >> bookID
                     >> quoted(studentName)
                     >> quoted(studentID));
    }
};

// ======================================
// 6. LIBRARY CLASS
// ======================================

class Library {
private:

    Book books[100];
    IssueRecord issuedBooks[100];

    int bookCount;
    int issueCount;
    int nextIssueID;

    // Search book by ID
    int searchIndex(int id) const {
        for (int i = 0; i < bookCount; i++) {
            if (books[i].getID() == id) {
                return i;
            }
        }

        return -1;
    }

    // Correct available quantity using issue records
    void correctAvailability() {
        for (int i = 0; i < bookCount; i++) {

            int issued = 0;

            for (int j = 0; j < issueCount; j++) {

                if (books[i].getID() ==
                    issuedBooks[j].getBookID()) {
                    issued++;
                }
            }

            int available = books[i].getQuantity() - issued;

            if (available < 0) {
                available = 0;
            }

            books[i].setAvailable(available);
        }
    }

    // Save all data
    bool saveData() {
        ofstream bookFile("books.txt");

        if (!bookFile) {
            cout << "Error saving books!\n";
            return false;
        }

        for (int i = 0; i < bookCount; i++) {
            books[i].saveBook(bookFile);
        }

        bookFile.close();

        ofstream issueFile("issued.txt");

        if (!issueFile) {
            cout << "Error saving issue records!\n";
            return false;
        }

        for (int i = 0; i < issueCount; i++) {
            issuedBooks[i].saveRecord(issueFile);
        }

        issueFile.close();

        return true;
    }

    // Load data from files
    void loadData() {

        ifstream bookFile("books.txt");

        Book b;

        while (bookCount < 100 && b.loadBook(bookFile)) {
            books[bookCount] = b;
            bookCount++;
        }

        bookFile.close();

        ifstream issueFile("issued.txt");

        IssueRecord r;

        while (issueCount < 100 && r.loadRecord(issueFile)) {
            issuedBooks[issueCount] = r;
            issueCount++;

            if (r.getIssueID() >= nextIssueID) {
                nextIssueID = r.getIssueID() + 1;
            }
        }

        issueFile.close();

        // Recalculate available copies
        correctAvailability();

        // Save corrected data
        saveData();
    }

public:

    // Constructor
    Library() {
        bookCount = 0;
        issueCount = 0;
        nextIssueID = 1;

        loadData();
    }

    // Destructor
    ~Library() {
        saveData();
    }

    // ==================================
    // ADD BOOK
    // ==================================

    void addBook() {
        int id, q;
        string title, author;

        if (bookCount >= 100) {
            cout << "Library is full!\n";
            return;
        }

        cout << "\nEnter Book ID: ";
        id = readInt();

        if (id <= 0) {
            cout << "Invalid Book ID!\n";
            return;
        }

        if (searchIndex(id) != -1) {
            cout << "Book ID already exists!\n";
            return;
        }

        cout << "Enter Book Title: ";
        getline(cin, title);

        cout << "Enter Author Name: ";
        getline(cin, author);

        cout << "Enter Quantity: ";
        q = readInt();

        if (title.empty() || author.empty() || q <= 0) {
            cout << "Invalid book details!\n";
            return;
        }

        books[bookCount] = Book(id, title, author, q);
        bookCount++;

        if (saveData()) {
            cout << "\nBook added successfully!\n";
        }
    }

    // ==================================
    // DISPLAY ALL BOOKS
    // ==================================

    void displayBooks() const {
        if (bookCount == 0) {
            cout << "\nNo books available!\n";
            return;
        }

        cout << "\n========== BOOK DETAILS ==========\n";

        for (int i = 0; i < bookCount; i++) {
            books[i].displayBook();
        }
    }

    // ==================================
    // SEARCH BOOK
    // ==================================

    void searchBook() const {
        int id;

        cout << "\nEnter Book ID: ";
        id = readInt();

        int index = searchIndex(id);

        if (index == -1) {
            cout << "Book not found!\n";
        }
        else {
            cout << "\nBook found!\n";
            books[index].displayBook();
        }
    }

    // ==================================
    // UPDATE BOOK
    // ==================================

    void updateBook() {
        int id, q;
        string title, author;

        cout << "\nEnter Book ID to update: ";
        id = readInt();

        int index = searchIndex(id);

        if (index == -1) {
            cout << "Book not found!\n";
            return;
        }

        int issued = books[index].getQuantity()
                     - books[index].getAvailable();

        cout << "Enter New Title: ";
        getline(cin, title);

        cout << "Enter New Author: ";
        getline(cin, author);

        cout << "Enter New Total Quantity: ";
        q = readInt();

        if (title.empty() || author.empty() ||
            q <= 0 || q < issued) {

            cout << "Invalid details or quantity!\n";
            return;
        }

        books[index].updateBook(title, author, q);

        if (saveData()) {
            cout << "Book updated successfully!\n";
        }
    }

    // ==================================
    // DELETE BOOK
    // ==================================

    void deleteBook() {
        int id;

        cout << "\nEnter Book ID to delete: ";
        id = readInt();

        int index = searchIndex(id);

        if (index == -1) {
            cout << "Book not found!\n";
            return;
        }

        if (books[index].getAvailable() !=
            books[index].getQuantity()) {

            cout << "Cannot delete! Book is currently issued.\n";
            return;
        }

        for (int i = index; i < bookCount - 1; i++) {
            books[i] = books[i + 1];
        }

        bookCount--;

        if (saveData()) {
            cout << "Book deleted successfully!\n";
        }
    }

    // ==================================
    // ISSUE BOOK
    // ==================================

    void issueBook() {
        int id;
        string name, sid;

        if (issueCount >= 100) {
            cout << "Issue record limit reached!\n";
            return;
        }

        cout << "\nEnter Book ID: ";
        id = readInt();

        int index = searchIndex(id);

        if (index == -1) {
            cout << "Book not found!\n";
            return;
        }

        if (books[index].getAvailable() <= 0) {
            cout << "Book is not available!\n";
            return;
        }

        cout << "Enter Student Name: ";
        getline(cin, name);

        cout << "Enter Student ID: ";
        getline(cin, sid);

        if (name.empty() || sid.empty()) {
            cout << "Invalid student details!\n";
            return;
        }

        Student s(name, sid);

        cout << "\nStudent Details:";
        s.displayRole();

        books[index].issueBook();

        issuedBooks[issueCount] =
            IssueRecord(nextIssueID, id, name, sid);

        cout << "\nIssue ID: " << nextIssueID;

        nextIssueID++;
        issueCount++;

        if (saveData()) {
            cout << "\nBook issued successfully!\n";
        }
    }

    // ==================================
    // RETURN BOOK
    // ==================================

    void returnBook() {
        int id;

        cout << "\nEnter Issue ID: ";
        id = readInt();

        for (int i = 0; i < issueCount; i++) {

            if (issuedBooks[i].getIssueID() == id) {

                int bookIndex =
                    searchIndex(issuedBooks[i].getBookID());

                if (bookIndex == -1) {
                    cout << "Book record not found!\n";
                    return;
                }

                books[bookIndex].returnBook();

                for (int j = i; j < issueCount - 1; j++) {
                    issuedBooks[j] = issuedBooks[j + 1];
                }

                issueCount--;

                if (saveData()) {
                    cout << "Book returned successfully!\n";
                }

                return;
            }
        }

        cout << "Invalid Issue ID!\n";
    }

    // ==================================
    // DISPLAY ISSUED BOOKS
    // ==================================

    void displayIssuedBooks() const {
        if (issueCount == 0) {
            cout << "\nNo books are currently issued!\n";
            return;
        }

        cout << "\n========== ISSUED BOOKS ==========\n";

        for (int i = 0; i < issueCount; i++) {
            issuedBooks[i].displayRecord();
        }
    }

    // ==================================
    // MAIN MENU
    // ==================================

    void menu() {
        int choice;

        do {
            cout << "\n\n";
            cout << "====================================\n";
            cout << "       LIBRARY MANAGEMENT SYSTEM\n";
            cout << "====================================\n";

            cout << "1. Add Book\n";
            cout << "2. Display All Books\n";
            cout << "3. Search Book\n";
            cout << "4. Update Book\n";
            cout << "5. Delete Book\n";
            cout << "6. Issue Book\n";
            cout << "7. Return Book\n";
            cout << "8. Display Issued Books\n";
            cout << "0. Exit\n";

            cout << "====================================\n";
            cout << "Enter Your Choice: ";

            choice = readInt();

            switch (choice) {

                case 1:
                    addBook();
                    break;

                case 2:
                    displayBooks();
                    break;

                case 3:
                    searchBook();
                    break;

                case 4:
                    updateBook();
                    break;

                case 5:
                    deleteBook();
                    break;

                case 6:
                    issueBook();
                    break;

                case 7:
                    returnBook();
                    break;

                case 8:
                    displayIssuedBooks();
                    break;

                case 0:
                    cout << "\nThank you for using Library System!\n";
                    break;

                default:
                    cout << "\nInvalid choice! Try again.\n";
            }

        } while (choice != 0);
    }
};

// ======================================
// 7. MAIN FUNCTION
// ======================================

int main() {

    cout << "\nWelcome to Library Management System!\n";

    Librarian librarian("Admin", "L001");

    User *u = &librarian;
    u->displayRole();

    Library lib;

    lib.menu();

    return 0;
}

