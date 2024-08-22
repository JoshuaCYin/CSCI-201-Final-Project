/* Program name: Library.h
* Author: Joshua Yin
* Date last updated: 7/24/2024
* Purpose: Define the library class
*/

#ifndef LIBRARY_H
#define LIBRARY_H

#include <iostream>
#include <fstream>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>

#include "Member.h"
#include "Book.h"
#include "Transaction.h"
#include "Return.h"
#include "Borrow.h"

using namespace std;

class Library {
private:
    vector<Book> books;
    vector<Member> members;
    vector<Transaction*> transactions;

    map<string, int> reservations;

public:
    // Book methods
    void addBook(const Book &book);
    void editBook(const string &isbn, const Book &updatedBook);
    void deleteBook(const string &isbn);
    void displayBooks() const;

    void borrowBook(const string &isbn, const int &memberId);
    void returnBook(const string &isbn, const int &memberId);
    void searchBook(const string &query, const string &searchType) const;
    
    // (Library) Member methods
    void registerMember(const Member &member);
    void editMember(int id, const Member &updatedMember);
    void deleteMember(int id);
    void displayMembers() const;
    
    // Reservation methods
    void reserveBook(const string &isbn, const int &memberId);
    void cancelReservation(const string &isbn, const int &memberId);
    void displayReservations() const;

    // Transaction methods
    void displayTransactions() const;
    void deleteTransactionHistory();

    // File methods
    void saveToFile(const string& filename);
    void loadFromFile(const string& filename);

    // Getters
    vector<Book> getBooks() const;
    vector<Member> getMembers() const;
    map<string, int> getReservations() const;
    vector<Transaction*> getTransactions() const;
    
    // Setters
    void setBooks(const vector<Book> &books);
    void setMembers(const vector<Member> &members);
    void setReservations(const map<string, int> &reservations);
    void setTransactions(const vector<Transaction*> &transactions);

    ~Library();
};

#endif
