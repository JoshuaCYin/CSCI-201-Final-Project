/* Program name: Return.h
* Author: Joshua Yin
* Date last updated: 7/24/2024
* Purpose: Define the return class
*/

#ifndef RETURN_H
#define RETURN_H

#include <iostream>
#include <string>

#include "Book.h"
#include "Transaction.h"

using namespace std;

class Return : public Transaction {
private:
    Book &book;

public:
    Return(Book &book, const int &memberId);

    void process_transaction() override;

    // Getters
    const Book& getBook() const override;

    // Display return details
    void display() const override ;

    ~Return();
};

#endif