/* Program name: Book.cpp
* Author: Joshua Yin
* Date last updated: 7/24/2024
* Purpose: Implement the book class methods
*/

#include <iostream>
#include <map>
#include <string>

#include "Book.h"

using namespace std;

// Define and initialize genre type to string representation map
map<genreType, string> genreNames = {
    {FANTASY, "Fantasy"},
    {FICTION, "Fiction"},
    {HISTORY, "History"},
    {HORROR, "Horror"},
    {MYSTERY, "Mystery"},
    {NON_FICTION, "Non-Fiction"},
    {ROMANCE, "Romance"},
    {SCIENCE, "Science"},
    {SCIENCE_FICTION, "Science Fiction"}
};

Book::Book(string t, string a, string i, int p, string c, genreType g)
    : title(t), author(a), ISBN(i), pubDate(p), callNum(c), genre(g), isBorrowed(false), dueDate("None") {}

// Getters
string Book::getTitle() const { return title; }
string Book::getAuthor() const { return author; }
string Book::getISBN() const { return ISBN; }
int Book::getPubDate() const { return pubDate; }
string Book::getCallNum() const {return callNum; }
genreType Book::getGenre() const { return genre; }
bool Book::getIsBorrowed() const { return isBorrowed; }
string Book::getDueDate() const { return dueDate; }

// Setters
void Book::setTitle(const string &t) { title = t; }
void Book::setAuthor(const string &a) { author = a; }
void Book::setISBN(const string &i) { ISBN = i; }
void Book::setPubDate(const int &p) { pubDate = p; }
void Book::setCallNum(const string &c) { callNum = c; }
void Book::setGenre(genreType g) { genre = g; }
void Book::setIsBorrowed(bool b) { isBorrowed = b; }
void Book::setDueDate(const string &d) { dueDate = d; }

// Display book details
void Book::display() const {
    cout << "--------------------\n"
        << "Title: " << title << "\n"
        << "Author: " << author << "\n"
        << "Genre: " << genreNames.at(genre) << "\n"
        << "ISBN: " << ISBN << "\n"
        << "Publication Date: " << pubDate << "\n"
        << "Call Number: " << callNum << "\n"
        << "Borrowed: " << (isBorrowed ? "Yes" : "No") << "\n"
        << "Due Date: " << dueDate << endl;
}
