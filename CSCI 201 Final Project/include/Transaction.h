/* Program name: Transaction.h
* Author: Joshua Yin
* Date last updated: 7/24/2024
* Purpose: Define the transaction class
*/

#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <ctime>
#include <iostream>
#include <stdexcept>
#include <string>

#include "Book.h"

using namespace std;

class Transaction {
protected:
    string ISBN;
    int memberID;
    time_t transactionDate; // Time of transaction

public:
    Transaction(const string &ISBN, const int &memberID);

    virtual void process_transaction() = 0;

    // Getters
    virtual const Book& getBook() const = 0; // Pure virtual function because base class does not have its own book
    int getMemberID() const;
    time_t getTransactionDate() const;

    // Setters
    void setTransactionDate(const string &transactionDate);

    // Virtual function to display transaction details
    virtual void display() const;

    virtual ~Transaction();
};

#endif
