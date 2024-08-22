/* Program name: Borrow.h
* Author: Joshua Yin
* Date last updated: 7/24/2024
* Purpose: Define the borrow class
*/

#ifndef BORROW_H
#define BORROW_H

#include <ctime>
#include <iostream>
#include <string>

#include "Book.h"
#include "Transaction.h"

using namespace std;

class Borrow : public Transaction {
private:
    Book &book;
    string dueDate;

    string calculateDueDate();

public:
    Borrow(Book &book, const int &memberID);

    void process_transaction() override;

    // Getters
    const Book& getBook() const override;
    virtual string getDueDate() const;

    // Setters
    void setDueDate(string dueDate);

    // Display borrow details
    void display() const override;

    ~Borrow();
};

#endif