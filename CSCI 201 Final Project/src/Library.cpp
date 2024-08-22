/* Program name: Library.cpp
* Author: Joshua Yin
* Date last updated: 7/24/2024
* Purpose: Implement the library class methods
*/

#include <algorithm>
#include <iostream>
#include <fstream>
#include <map>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "Library.h"

using namespace std;

/* Helper Functions */
// Helper function to convert genre to string representation (only used for saving genre to file)
string genreToString(genreType genre) {
  map<genreType, string>::const_iterator it = genreNames.find(genre);
    if (it != genreNames.end()) {
      return it->second;
    }
  return "Unknown Genre"; // Fallback
}

// Helper function to convert string to genre representation (only used for loading genre from file)
genreType stringToGenreType(const string& genreStr) {
  map<genreType, string>::const_iterator it;
  for (it = genreNames.begin(); it != genreNames.end(); ++it) {
    if (it->second == genreStr) {
      return it->first;
    }
  }
  throw invalid_argument("Unknown genre: " + genreStr);
}

/* Book Methods */
void Library::addBook(const Book &book) {
  books.push_back(book);
  cout << "Book added successfully." << endl;
}

void Library::editBook(const string &isbn, const Book &updatedBook) {
  for (size_t i = 0; i < books.size(); ++i) {
    if (books[i].getISBN() == isbn) {
      if (books[i].getIsBorrowed()) { // Can't edit if book is currently borrowed
        cout << "Book is borrowed. Cannot edit currently borrowed books." << endl;
        return;
      } else {
        books[i] = updatedBook;
        cout << "Book edited successfully." << endl;
        return;
      }
    }
  }
  cout << "Book not found." << endl;
}

void Library::deleteBook(const string &isbn) {
  for (size_t i = 0; i < books.size(); ++i) {
    if (books[i].getISBN() == isbn) {
      if (books[i].getIsBorrowed()) { // Can't edit if book is currently borrowed
        cout << "Book is borrowed. Cannot delete currently borrowed books." << endl;
        return;
      } else {
        books.erase(books.begin() + i);
        cout << "Book deleted successfully." << endl;
      }
      return;
    }
  }
  cout << "Book not found." << endl;
}

void Library::displayBooks() const {
  if (books.empty()) {
    cout << "The library has no books." << endl;
    return;
  }

  cout << "Books in the Library:" << endl;
  for (vector<Book>::const_iterator it = books.begin(); it != books.end(); ++it) {
    it->display();
  }
}

void Library::borrowBook(const string &isbn, const int &memberID) {
  for (size_t i = 0; i < books.size(); ++i) {
    if (books[i].getISBN() == isbn) {
      // Check if book is already borrowed
      if (books[i].getIsBorrowed()) {
        cout << "Book is already borrowed." << endl;
        return;
      }

      // Check if the book is reserved
      map<string, int>::const_iterator it = reservations.find(isbn);
      if (it != reservations.end()) {
        if (it->second == memberID) {
          // Book is reserved by the borrowing member
          cancelReservation(isbn, memberID);

          // Borrow the book
          Borrow* transaction = new Borrow(books[i], memberID);
          transaction->process_transaction();
          transactions.push_back(transaction);
        } else {
          // Book is reserved by another member
          cout << "This book is reserved by another member." << endl;
        }
      } else {
        // Book is not reserved; borrow it directly
        Borrow* transaction = new Borrow(books[i], memberID);
        transaction->process_transaction();
        transactions.push_back(transaction);
      }
      return;
    }
  }
  cout << "Book not found." << endl;
}

void Library::returnBook(const string &isbn, const int &memberID) {
  // Find the book with the given ISBN
  for (size_t i = 0; i < books.size(); ++i) {
    if (books[i].getISBN() == isbn) {
      // Check if the book is currently borrowed
      if (!books[i].getIsBorrowed()) {
        cout << "Book is not currently borrowed." << endl;
        return;
      }

      // Check if the member ID matches the one who borrowed the book
      bool foundBorrowingTransaction = false;
      for (size_t j = 0; j < transactions.size(); ++j) {
        if (Borrow* borrowTransaction = dynamic_cast<Borrow*>(transactions[j])) {
          if (borrowTransaction->getBook().getISBN() == isbn && borrowTransaction->getMemberID() == memberID) {
            foundBorrowingTransaction = true;
            // Create a return transaction
            Return* transaction = new Return(books[i], memberID);
            transaction->process_transaction();
            transactions.push_back(transaction);
            return;
          }
        }
      }

      if (!foundBorrowingTransaction) {
        // If no matching borrowing transaction is found
        cout << "Member with ID " << memberID << " is not the one who borrowed this book." << endl;
     }

      return;
    }
  }
  cout << "Book not found." << endl;
}

void Library::searchBook(const string &query, const string &searchType) const {
  bool found = false;

  // Display full search query
  cout << "Searching " << query << " by " << searchType << ":" << endl;

  for (vector<Book>::const_iterator it = books.begin(); it != books.end(); ++it) {
    const Book& book = *it;

    bool match = false;

    // Check based on the search type or default to "any"
    if (searchType == "title" && book.getTitle() == query) {                // Search by title
      match = true;
    } else if (searchType == "author" && book.getAuthor() == query) {       // Search by author
      match = true;
    } else if (searchType == "isbn" && book.getISBN() == query) {           // Search by ISBN
      match = true;
    } else if (searchType == "callnumber" && book.getCallNum() == query) {  // Search by call number
      match = true;
    } else if (searchType == "genre") {                                     // Search by genre
      try {
        genreType genre = stringToGenreType(query);
        if (book.getGenre() == genre) {
          match = true;
        }
      } catch (const invalid_argument&) {
        // Invalid genre string, skip this criterion
      }
    } else if (searchType == "pubdate") {                                   // Search by publication date
      // We need to convert user's string input to an integer
      int pubDate;
      stringstream ss(query);
      ss >> pubDate;
      if (book.getPubDate() == pubDate) {
        match = true;
      }
    } else if (searchType == "any") {                                       // Search by any
      // Default search by title, author, or ISBN
      if (book.getTitle() == query || book.getAuthor() == query || book.getISBN() == query) {
        match = true;
      }
    }

    if (match) {
      book.display();
      found = true;
    }
  }

  if (!found) {
      cout << "No book matching the query was found." << endl;
  }
}

/* (Library) Member Methods */
void Library::registerMember(const Member &member) {
  members.push_back(member);
  cout << "Member registered successfully." << endl;
}

void Library::editMember(int id, const Member &updatedMember) {
  for (size_t i = 0; i < members.size(); ++i) {
    if (members[i].getMemberID() == id) {
      members[i] = updatedMember;
      cout << "Member edited successfully." << endl;
      return;
    }
  }
  cout << "Member not found." << endl;
}

void Library::deleteMember(int id) {
  // Check if user is currently borrowing anything
  for (size_t i = 0; i < transactions.size(); ++i) {
    Borrow* borrowTransaction = dynamic_cast<Borrow*>(transactions[i]);
    if (borrowTransaction != nullptr && borrowTransaction->getMemberID() == id) {
      cout << "Cannot delete member with ID " << id << " because they have at least one book borrowed." << endl;
      return;
    }
  }

  // Check if user is currently reserving anything
  for (map<string, int>::const_iterator it = reservations.begin(); it != reservations.end(); ++it) {
    if (it->second == id) {
      cout << "Cannot delete member with ID " << id << " because they have at least one reservation." << endl;
      return;
    }
  }

  // If no active borrowings or reservations, proceed with deletion
  for (size_t i = 0; i < members.size(); ++i) {
    if (members[i].getMemberID() == id) {
      members.erase(members.begin() + i);
      cout << "Member deleted successfully." << endl;
      return;
    }
  }

  cout << "Member not found." << endl;
}

void Library::displayMembers() const {
  if (members.empty()) {
    cout << "There are no members in the library." << endl;
    return;
  }

  cout << "Members in the Library:" << endl;
  for (vector<Member>::const_iterator it = members.begin(); it != members.end(); ++it) {
    it->display();
  }
}

/* Reservation Methods*/
void Library::reserveBook(const string &isbn, const int &memberID) {
  for (size_t i = 0; i < books.size(); ++i) {
    if (books[i].getISBN() == isbn) {
      if (books[i].getIsBorrowed()) { // If book is already borrowed
        map<string, int>::iterator it = reservations.find(isbn);
        if (it != reservations.end()) { // If book is already reserved
          if (it->second == memberID) { // Reserved by this member
            cout << "Book is already reserved by this member." << endl;
          } else { // Reserved by another member
            cout << "Book is already reserved by another member." << endl;
          }
        } else { // No reservation exists, proceed with reservation
          reservations[isbn] = memberID;
          cout << "Book reserved successfully." << endl;
        }
      } else { // Book is not borrowed, no need to reserve
          cout << "Book is available, no need to reserve." << endl;
      }
      return;
    }
  }
  cout << "Book not found." << endl;
}

void Library::cancelReservation(const string &isbn, const int &memberID) {
  map<string, int>::iterator it = reservations.find(isbn);
  if (it != reservations.end() && it->second == memberID) {
    // Reservation found and matches the memberID
    reservations.erase(it);
    cout << "Reservation cancelled successfully." << endl;
  } else {
    // Reservation not found or memberID does not match
    cout << "Reservation not found or you are not the one who reserved it." << endl;
  }
}

void Library::displayReservations() const {
  if (reservations.empty()) {
    cout << "No books are currently reserved." << endl;
    return;
  }

  cout << "Current Reservations:" << endl;
  for (map<string, int>::const_iterator it = reservations.begin(); it != reservations.end(); ++it) {
    string isbn = it->first;
    int memberID = it->second;

    cout << "ISBN: " << isbn << ", Reserved by Member ID: " << memberID << endl;
  }
}

/* Transaction Methods */
void Library::displayTransactions() const {
  if (transactions.empty()) {
    cout << "There are no transactions yet." << endl;
    return;
  }
  cout << "Transaction History:" << endl;
  for (size_t i = 0; i < transactions.size(); ++i) {
    transactions[i]->display();
  }
}

void Library::deleteTransactionHistory() {
  // Free the memory for each transaction pointer in the vector
  for (Transaction* transaction : transactions) {
    delete transaction;
  }
  // Clear the vector
  transactions.clear();
  cout << "Transaction history deleted successfully." << endl;
}

/* File Methods */
// Save library data to file (separated by newlines)
void Library::saveToFile(const string &filename) {
  ofstream file(filename);
  if (!file) { // Check for file errors
    cerr << "Error opening file for writing: " << filename << endl;
    return;
  }

  try {
    // Save books
    file << books.size() << endl;                   // Write size of books vector
    for (vector<Book>::const_iterator it = books.begin(); it != books.end(); ++it) {
      const Book& book = *it; // Dereference iterator to get books
      file << book.getTitle() << endl               // Write title
          << book.getAuthor() << endl               // Write author
          << book.getISBN() << endl                 // Write ISBN
          << book.getPubDate() << endl              // Write publication date
          << book.getCallNum() << endl              // Write call number
          << genreToString(book.getGenre()) << endl // Write genre (as string)
          << book.getIsBorrowed() << endl           // Write borrowed status
          << book.getDueDate() << endl;             // Write due date
    }

    // Save members
    file << members.size() << endl;         // Write size of members vector
    for (vector<Member>::const_iterator it = members.begin(); it != members.end(); ++it) {
      const Member& member = *it; // Dereference iterator to get members
      file << member.getName() << endl      // Write name
          << member.getMemberID() << endl   // Write id
          << member.getPhone() << endl      // Write phone number
          << member.getEmail() << endl      // Write email
          << member.getAddress() << endl;   // Write address
    }

    // Save transactions
    file << transactions.size() << endl;                         // Write size of transactions vector
    for (vector<Transaction*>::const_iterator it = transactions.begin(); it != transactions.end(); ++it) {
      Transaction* transaction = *it; // Dereference iterator to get the transaction
      if (Borrow* borrowTransaction = dynamic_cast<Borrow*>(transaction)) { // If transaction is of borrow class
        file << "borrow" << endl;                                // Write "borrow" to indicate borrow type transaction
        file << borrowTransaction->getBook().getISBN() << endl   // Write ISBN of borrowed book
            << borrowTransaction->getMemberID() << endl          // Write ID of borrowing member
            << borrowTransaction->getTransactionDate() << endl   // Write date of transaction (UNIX)
            << borrowTransaction->getDueDate() << endl;          // Write due date of book
      } else if (Return* returnTransaction = dynamic_cast<Return*>(transaction)) { // If transaction is of return class
        file << "return" << endl;                                // Write "return" to indicate return type transaction
        file << returnTransaction->getBook().getISBN() << endl   // Write ISBN of returned book
            << returnTransaction->getMemberID() << endl          // Write ID of member returning the book
            << returnTransaction->getTransactionDate() << endl;  // Write date of transaction (UNIX)
      }
    }
      
    // Save reservations
    file << reservations.size() << endl;    // Write size of reservations map
    for (map<string, int>::const_iterator it = reservations.begin(); it != reservations.end(); ++it) {
      const string& isbn = it->first; // Get book ISBN
      const int& memberID = it->second; // Get member ID

      file << isbn << endl                  // Write book ISBN
          << memberID << endl;              // Write member ID
    }
  }
  catch (const exception &e) {
    cerr << "An error occurred while saving data: " << e.what() << endl;
  }

  file.close();
  cout << "Library data saved successfully." << endl;
}

// Load library data from file
void Library::loadFromFile(const string &filename) {
  ifstream file(filename);
  if (!file) { // Check for file errors
    cerr << "Error opening file for reading: " << filename << endl;
    return;
  }

  try {
    // Clear existing vectors and map
    books.clear();
    members.clear();
    transactions.clear();
    reservations.clear();

    size_t size; // Size variable that will be reused whenever loading size of each vector and the map

    // Load books
    file >> size;                     // Read size of books vector
    file.ignore();
    for (size_t i = 0; i < size; ++i) { // For each book:
      string title, author, isbn, callNum, genreStr, dueDate;
      int pubDate;
      bool isBorrowed;

      getline(file, title);           // Read title
      getline(file, author);          // Read author
      getline(file, isbn);            // Read isbn
      file >> pubDate;                // Read publication date
      file.ignore();          
      getline(file, callNum);         // Read call number
      file >> genreStr >> isBorrowed; // Read genre (as string) and borrowed status
      file.ignore();
      getline(file, dueDate);         // Read due date of book

      genreType genre = stringToGenreType(genreStr); // Convert genre string to enum type

      books.push_back(Book(title, author, isbn, pubDate, callNum, genre)); // Add book to vector (with title, author, isbn, and genre)
      books.back().setIsBorrowed(isBorrowed);  // Set borrowed status
      books.back().setDueDate(dueDate); // Set due date
    }
    
    // Load members
    file >> size;             // Read size of members vector
    file.ignore();
    for (size_t i = 0; i < size; ++i) { // For each member:
      string name, phone, email, address;
      int memberID;

      getline(file, name);    // Read name
      file >> memberID;       // Read member id
      file.ignore();
      getline(file, phone);   // Read phone number
      getline(file, email);   // Read email
      getline(file, address); // Read address

      members.push_back(Member(name, memberID, phone, email, address)); // Add member to vector
    }

    // Load transactions
    file >> size;                     // Read size of transactions vector
    file.ignore();
    for (size_t i = 0; i < size; ++i) { // For each transaction:
      string type, isbn, transactionDate;
      int memberID;

      getline(file, type);            // Read type of transaction ("borrow" or "return")
      getline(file, isbn);            // Read isbn of the book in the transaction
      file >> memberID;               // Read id of the member in the transaction
      file.ignore();
      getline(file, transactionDate); // Read date of transaction

      // Check if a book with the isbn exists
      Book* book = nullptr;
      for (vector<Book>::iterator it = books.begin(); it != books.end(); ++it) {
        Book& b = *it; // Dereference iterator to get the book
        if (b.getISBN() == isbn) {
          // Book found
          book = &b; // Initialize book to the book with the isbn
          break;
        }
      }
      if (!book) {
        // Book not found
        throw runtime_error("Book with ISBN " + isbn + " not found.");
      }

      // Create the transaction object
      Transaction* transaction = nullptr;
      if (type == "borrow") { // If transaction type is borrow
        string dueDate;
        getline(file, dueDate);     // Read due date
        transaction = new Borrow(*book, memberID);
      } else if (type == "return") { // If transaction type is return
        transaction = new Return(*book, memberID);
      } else {
        throw runtime_error("Unknown transaction type: " + type);
      }

      // Set the transaction date
      transaction->setTransactionDate(transactionDate);

      // Add the transaction to the vector
      transactions.push_back(transaction);
    }

    // Load reservations
    file >> size;          // Read number of reservations
    file.ignore();
    for (size_t i = 0; i < size; ++i) { // For each reservation
      string isbn;
      int memberID;
      getline(file, isbn); // Read book ISBN
      file >> memberID;    // Read member id
      file.ignore();
      reservations[isbn] = memberID;
    }
  }
  catch (const exception &e) {
    cerr << "An error occurred while loading data: " << e.what() << endl;
  }

  file.close();
  cout << "Library data loaded successfully." << endl;
}

// Getters
vector<Book> Library::getBooks() const { return books; }
vector<Member> Library::getMembers() const { return members; }
map<string, int> Library::getReservations() const { return reservations; }
vector<Transaction*> Library::getTransactions() const { return transactions; }

// Setters
void Library::setBooks(const vector<Book> &books) { this->books = books; }
void Library::setMembers(const vector<Member> &members) { this->members = members; }
void Library::setReservations(const map<string, int> &reservations) { this->reservations = reservations; }
void Library::setTransactions(const vector<Transaction*> &transactions) { this->transactions = transactions; }

// Destructor
Library::~Library() {
  // Deallocate memory for transactions
  for (size_t i = 0; i < transactions.size(); ++i) {
    delete transactions[i];
  }
}
