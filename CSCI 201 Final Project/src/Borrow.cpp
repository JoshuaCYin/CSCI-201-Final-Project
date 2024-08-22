/* Program name: Borrow.cpp
* Author: Joshua Yin
* Date last updated: 7/24/2024
* Purpose: Implement the borrow class methods
*/

#include <ctime>
#include <iostream>
#include <string>

#include "Borrow.h"

using namespace std;

// Method to determine due date
string Borrow::calculateDueDate() {
    // 14-day borrowing period
    time_t due = transactionDate + 14 * 24 * 60 * 60;
    char buffer[80];
    strftime(buffer, 80, "%Y-%m-%d", localtime(&due)); // Format is YYYY-MM-DD
    return string(buffer);
}

Borrow::Borrow(Book &book, const int &memberID)
        : Transaction(book.getISBN(), memberID), book(book) {
        dueDate = calculateDueDate();
    }

void Borrow::process_transaction() {
    if (!book.getIsBorrowed()) {
        book.setIsBorrowed(true);
        book.setDueDate(dueDate);
        cout << "Book borrowed successfully. Due date: " << dueDate << endl;
    } else {
        cout << "Book is already borrowed." << endl;
    }
}

// Getters
const Book& Borrow::getBook() const { return book; }
string Borrow::getDueDate() const { return dueDate; }

// Setters
void Borrow::setDueDate(string dueDate) { this->dueDate = dueDate; }

// Display borrow details
void Borrow::display() const {
    cout << "Type: Borrow, ";
    Transaction::display();
    cout << ", Due Date: " << dueDate << endl;
}

Borrow::~Borrow() {}
