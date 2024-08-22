/* Program name: Return.cpp
* Author: Joshua Yin
* Date last updated: 7/24/2024
* Purpose: Implement the return class methods
*/

#include <iostream>
#include <string>

#include "Return.h"

using namespace std;

Return::Return(Book &book, const int &memberId)
    : Transaction(book.getISBN(), memberId), book(book) {}

void Return::process_transaction() {
    if (book.getIsBorrowed()) {
        book.setIsBorrowed(false);
        book.setDueDate("None");
        cout << "Book returned successfully." << endl;
    } else {
        cout << "Book is not borrowed." << endl;
    }
}

// Getters
const Book& Return::getBook() const { return book; }

// Display return details
void Return::display() const {
    cout << "Type: Return, ";
    Transaction::display();
    cout << endl;
}

Return::~Return() {}
