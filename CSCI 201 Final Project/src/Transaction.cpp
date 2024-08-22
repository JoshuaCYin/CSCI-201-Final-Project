/* Program name: Transaction.cpp
* Author: Joshua Yin
* Date last updated: 7/24/2024
* Purpose: Implement the transaction class methods
*/

#include <ctime>
#include <iostream>
#include <stdexcept>
#include <string>

#include "Transaction.h"

using namespace std;

Transaction::Transaction(const string &ISBN, const int &memberID)
    : ISBN(ISBN), memberID(memberID) {
    transactionDate = time(nullptr); // Current time
}

// Getters
int Transaction::getMemberID() const { return memberID; }
time_t Transaction::getTransactionDate() const { return transactionDate; }

// Setters
void Transaction::setTransactionDate(const string &transactionDateStr) {
    // Convert the string to a time_t value
    try {
        this->transactionDate = static_cast<time_t>(stoll(transactionDateStr));
    } catch (const invalid_argument &e) {
        throw invalid_argument("Failed to parse date string.");
    }
}

// Display transaction details (overriden by borrow and return classes)
void Transaction::display() const {
    // Convert transactionDate to a string using ctime
    string dateStr = ctime(&transactionDate);
    
    // Remove the newline character from the end of the date string
    if (!dateStr.empty() && dateStr.back() == '\n') {
        dateStr.pop_back();
    }

    cout << "ISBN: " << ISBN
        << ", Member ID: " << memberID
        << ", Transaction Date: " << dateStr;
}

Transaction::~Transaction() {}
