/* Program name: Book.h
* Author: Joshua Yin
* Date last updated: 7/24/2024
* Purpose: Define the book class
*/

#ifndef BOOK_H
#define BOOK_H

#include <iostream>
#include <map>
#include <string>

using namespace std;

// Enums for genres
enum genreType {
    FANTASY,
    FICTION,
    HISTORY,
    HORROR,
    MYSTERY,
    NON_FICTION,
    ROMANCE,
    SCIENCE,
    SCIENCE_FICTION
};

// Declare map for enum values and their string representations
extern map<genreType, string> genreNames; // Use extern because it's a global map

class Book {
private:
    string title;
    string author;
    string ISBN;
    int pubDate;
    string callNum;
    genreType genre;
    bool isBorrowed;
    string dueDate;

public:
    Book(string title, string author, string ISBN, int pubDate, string callNum, genreType genre);

    // Getters
    string getTitle() const;
    string getAuthor() const;
    string getISBN() const;
    int getPubDate() const;
    string getCallNum() const;
    genreType getGenre() const;
    bool getIsBorrowed() const;
    string getDueDate() const;

    // Setters
    void setTitle(const string &title);
    void setAuthor(const string &author);
    void setISBN(const string &ISBN);
    void setPubDate(const int &pubDate);
    void setCallNum(const string &callNum);
    void setGenre(genreType genre);
    void setIsBorrowed(bool isBorrowed);
    void setDueDate(const string &dueDate);

    // Display book details
    void display() const;
};

#endif
