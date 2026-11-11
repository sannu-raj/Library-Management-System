# Library Management System

## 1. Introduction

The Library Management System is a console-based application developed using C++ and Object-Oriented Programming (OOP). It is designed to help a librarian manage books and student book transactions in a simple and organised way.

The system provides facilities to add, display, search, update and delete book records. It also manages issuing and returning books while maintaining their availability.

## 2. Objectives

- To manage library book records efficiently.
- To maintain book details such as Book ID, Title, Author and Quantity.
- To manage book issuing and returning.
- To track available copies of books.
- To store records permanently using file handling.
- To apply Object-Oriented Programming concepts in a practical project.

## 3. Features

1. Add new books.
2. Display all available book records.
3. Search books using Book ID.
4. Update book information.
5. Delete book records.
6. Issue books to students.
7. Return issued books.
8. Display issued book records.
9. Maintain book availability.
10. Store and retrieve records using file handling.

## 4. Software Requirements

- Programming Language: C++
- IDE: Visual Studio Code
- Compiler: GCC (G++)
- Operating System: Windows
- Storage: File Handling

## 5. OOP Concepts Used

- **Classes and Objects:** Used to represent books, users and library operations.
- **Encapsulation:** Data members are protected through access control.
- **Inheritance:** Student and Librarian classes inherit from the User class.
- **Polymorphism:** Virtual functions are used to demonstrate runtime polymorphism.
- **Abstraction:** Abstract User class provides a common interface for different users.
- **Constructors and Destructors:** Used for object initialisation and cleanup.

## 6. File Handling

The application uses file handling to preserve records between program executions.

The following files are used:

- `books.txt` – stores book information.
- `issued.txt` – stores issued book records.

These data files are generated automatically when the program runs. They are not included in this public repository because they contain runtime records.

## 7. How to Compile and Run

1. Clone or download this repository.
2. Open the project folder in Visual Studio Code.
3. Open the terminal.
4. Compile the program:

```bash
g++ -std=c++17 libraryManagementSystem.cpp -o libraryManagementSystem
```

5. Run the program on Windows:

```bash
.\libraryManagementSystem.exe
```

## 8. Project Team

- Sannu Raj
- Saksham
- Shagun Dhiman

## 9. Academic Details

**Project:** Library Management System  
**College:** Guru Nanak Dev Engineering College, Ludhiana  
**Project Type:** Academic Mini Project  
**Subject Area:** C++ and Object-Oriented Programming

## 10. Conclusion

This project demonstrates how C++ and Object-Oriented Programming can be used to develop a basic library management application. It provides practical experience in classes, inheritance, polymorphism, abstraction, arrays and file handling.

The project can be enhanced in the future by adding a graphical user interface, database connectivity, fine calculation and advanced student management features.

---

**Developed as an academic mini project.**
