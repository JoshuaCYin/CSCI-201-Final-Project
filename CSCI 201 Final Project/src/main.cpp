/* Program name: main.cpp
* Author: Joshua Yin
* Date last updated: 7/24/2024
* Purpose: See project proposal. Allow the user to navigate menus and
* select options and manipulate the components of the library.
*/

#include <algorithm>
#include <ctime>
#include <fstream>
#include <iostream>
#include <map>
#include <limits>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "Library.h"
#include "Member.h"
#include "Book.h"
#include "Transaction.h"
#include "Borrow.h"
#include "Return.h"

using namespace std;

/*================*/
/* Menu Functions */
/*================*/

// Function to display the main menu
void displayMainMenu() {
    cout << endl; // Add line break for clarity
    cout << "-------------------------\n";
    cout << "Library Management System\n";
    cout << "-------------------------\n";
    cout << "1. Manage Books\n";
    cout << "2. Manage Members\n";
    cout << "3. Borrow Book\n";
    cout << "4. Return Book\n";
    cout << "5. Search Book\n";
    cout << "6. Manage Reservations\n";
    cout << "7. Manage Transactions\n";
    cout << "0. Exit Library\n";
    cout << "-------------------------" << endl;
    cout << "Choose an option: ";
}

// Function to display the book management sub-menu
void displayBookMenu() {
    cout << endl; // Add line break for clarity
    cout << "--------------------\n";
    cout << "Manage Books\n";
    cout << "--------------------\n";
    cout << "1. Add Book\n";
    cout << "2. Edit Book\n";
    cout << "3. Delete Book\n";
    cout << "4. Display Books\n";
    cout << "0. Back to Main Menu\n";
    cout << "--------------------" << endl;
    cout << "Choose an option: ";
}

// Function to display the member management sub-menu
void displayMemberMenu() {
    cout << endl; // Add line break for clarity
    cout << "--------------------\n";
    cout << "Manage Members\n";
    cout << "--------------------\n";
    cout << "1. Register Member\n";
    cout << "2. Edit Member\n";
    cout << "3. Delete Member\n";
    cout << "4. Display Members\n";
    cout << "0. Back to Main Menu\n";
    cout << "--------------------" << endl;
    cout << "Choose an option: ";
}

// Function to display the reservation management sub-menu
void displayReservationMenu() {
    cout << endl; // Add line break for clarity
    cout << "-------------------\n";
    cout << "Manage Reservations\n";
    cout << "-------------------\n";
    cout << "1. Make Reservations\n";
    cout << "2. Cancel Reservations\n";
    cout << "3. Display Reservations\n";
    cout << "0. Back to Main Menu\n";
    cout << "-------------------" << endl;
    cout << "Choose an option: ";
}

// Function to display the transaction management sub-menu
void displayTransactionMenu() {
    cout << endl; // Add line break for clarity
    cout << "-------------------\n";
    cout << "Manage Transactions\n";
    cout << "-------------------\n";
    cout << "1. Display Transactions\n";
    cout << "2. Delete Transaction History\n";
    cout << "0. Back to Main Menu\n";
    cout << "-------------------" << endl;
    cout << "Choose an option: ";
}

// Function to display list of search options
void displaySearchMenu() {
    cout << endl; // Add line break for clarity
    cout << "------------\n";
    cout << "Search Menu:\n";
    cout << "------------\n";
    cout << "1. Search by Title\n";
    cout << "2. Search by Author\n";
    cout << "3. Search by ISBN\n";
    cout << "4. Search by Call Number\n";
    cout << "5. Search by Genre\n";
    cout << "6. Search by Publication Date\n";
    cout << "7. Search by Any (Title, Author, ISBN)\n";
    cout << "------------" << endl;
    cout << "Enter your choice: ";
}

// Function to display list of genre types
void displayGenreMenu() {
    cout << endl; // Add line break for clarity
    cout << "-----------\n";
    cout << "Genre Menu:\n";
    cout << "-----------\n";
    cout << "1. Fantasy\n";
    cout << "2. Fiction\n";
    cout << "3. History\n";
    cout << "4. Horror\n";
    cout << "5. Mystery\n";
    cout << "6. Non-Fiction\n";
    cout << "7. Romance\n";
    cout << "8. Science\n";
    cout << "9. Science Fiction\n";
    cout << "-----------" << endl;
}

/*==================*/
/* Helper Functions */
/*==================*/

// Function to check if an ISBN exists in the library
bool isbnExists(const vector<Book> &books, const string &isbn) {
    for (vector<Book>::const_iterator it = books.begin(); it != books.end(); ++it) {
        if (it->getISBN() == isbn) {
            return true;
        }
    }
    return false;
}

// Function to check if a member ID exists in the library
bool memberIdExists(const vector<Member> &members, int id) {
    for (vector<Member>::const_iterator it = members.begin(); it != members.end(); ++it) {
        if (it->getMemberID() == id) {
            return true;
        }
    }
    return false;
}

// Function to get string inputs
string getStrInput(const string& prompt) {
    string input;
    do {
        cout << prompt;
        getline(cin, input);
        if (input.empty()) {
            cout << "Input cannot be empty. Please try again." << endl;
        }
    } while (input.empty()); // Continue prompting until input is not empty

    return input;
}

// Function to get memberID inputs
int getIdInput(const string& prompt) {
    int input;
    string line;
    while (true) {
        cout << prompt;
        getline(cin, line); // Read entire line of input

        // Check if input is empty or contains only whitespace
        if (line.empty() || line.find_first_not_of(' ') == string::npos) {
            cout << "Input cannot be empty. Please try again." << endl;
            continue;
        }

        // Try to convert the input to an integer
        stringstream ss(line);
        if (ss >> input) {
            // Ensure there are no leftover characters in the stream
            if (ss.eof()) {
                return input;
            }
        }

        cout << "Invalid input. Please enter a valid integer." << endl;
    }
}

// Function to get menu choices
int getMenuChoice(void (*menuFunction)()) {
    string input;
    int menuChoice;
    
    do {
        menuFunction();
        getline(cin, input);

        stringstream ss(input);
        if (ss >> menuChoice && ss.eof()) {
            return menuChoice; // Valid integer input with no extra characters
        } else {
            cout << "Invalid input. Please enter a valid option." << endl;
        }
    } while (true);
}


/*=================================*/
/* Library Functionality Functions */
/*=================================*/

// Function to allow user to manage books (implementing book management)
void manageBooks(Library& library) {
    while (true) {
        // Get menu choice (with input validation)
        int bookMenuChoice = getMenuChoice(displayBookMenu);

        switch (bookMenuChoice) {
            case 0: { // Exit book menu
                return;
            }
            case 1: { // Add book
                string title, author, isbn, callNum;
                int pubDate, genre;

                // Get title
                title = getStrInput("Enter title: ");

                // Get author
                author = getStrInput("Enter author: ");

                // Get ISBN
                isbn = getStrInput("Enter ISBN: ");

                // Check if the ISBN already exists before continuing
                if (isbnExists(library.getBooks(), isbn)) {
                    cout << "Error: A book with this ISBN already exists.\n";
                    cout << "Returning to book menu." << endl;
                    continue; // Return to book menu since title and author may need to be reentered
                }

                // Get publication date
                while (true) {
                    cout << "Enter publication date: ";
                    if (cin >> pubDate && pubDate > 0) { // Valid input
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore rest of input (here, it is a newline character)
                        break;
                    } else { // Invalid input
                        cout << "Invalid input. Please enter a valid year." << endl;
                        cin.clear(); // Clear error flag
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore rest of input
                    }
                }

                // Get call number
                callNum = getStrInput("Enter call number: ");

                // Get genres
                displayGenreMenu();
                while (true) {
                    cout << "Enter genre choice: ";
                    if (cin >> genre && genre >= 1 && genre <= static_cast<int>(genreType::SCIENCE_FICTION) + 1) {
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore rest of input (newline character)
                        break; // Input is valid
                    } else {
                        cout << "Invalid genre. Please enter a number between 1 and 9." << endl;
                        cin.clear(); // Clear error state
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore rest of input
                    }
                }

                // Create a new book object and add it to the library
                library.addBook(Book(title, author, isbn, pubDate, callNum, static_cast<genreType>(genre - 1)));
                break;
            }
            case 2: { // Edit book
                string title, author, isbn, callNum;
                int genre, pubDate;

                // Get ISBN of book to edit
                isbn = getStrInput("Enter ISBN of the book to edit: ");

                // Check if the ISBN exists before proceeding
                if (!isbnExists(library.getBooks(), isbn)) {
                    cout << "ISBN not found. Please try again.\n";
                    continue; // Return to book menu since there might be no books in the library
                }

                // Get new title
                title = getStrInput("Enter new title: ");

                // Get new author
                author = getStrInput("Enter new author: ");

                // Get new publication date
                while (true) {
                    cout << "Enter new publication date: ";
                    if (cin >> pubDate && pubDate > 0) { // Valid input
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore rest of input (here, it is a newline character)
                        break;
                    } else { // Invalid input
                        cout << "Invalid input. Please enter a valid year." << endl;
                        cin.clear(); // Clear error flag
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore rest of input
                    }
                }

                // Get new call number
                callNum = getStrInput("Enter new call number: ");

                // Get new genre
                displayGenreMenu();
                while (true) {
                    cout << "Enter new genre option: ";
                    if (cin >> genre && genre >= 1 && genre <= static_cast<int>(genreType::SCIENCE_FICTION) + 1) {
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore rest of input (newline character)
                        break; // Input is valid
                    } else {
                        cout << "Invalid genre. Please enter a numbe between 1 and 9." << endl;
                        cin.clear(); // Clear error state
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore rest of input
                    }
                }

                // Create a new book object and add it to the library
                library.editBook(isbn, Book(title, author, isbn, pubDate, callNum, static_cast<genreType>(genre - 1)));
                break;
            }
            case 3: { // Delete book
                string isbn;

                // Get ISBN of book to delete
                isbn = getStrInput("Enter ISBN of the book to delete: ");

                // Check if the ISBN exists before proceeding
                if (!isbnExists(library.getBooks(), isbn)) {
                    cout << "ISBN not found. Please try again." << endl;
                    continue; // Return to book menu since there might be no books in the library to delete
                }

                library.deleteBook(isbn);
                break;
            }
            case 4: { // Display books
                library.displayBooks();
                break;
            }
            default: cout << "Invalid option. Please try again." << endl;
        }
    }
}

// Function to allow user to manage members (implementing member management)
void manageMembers(Library& library) {
    while (true) {
        // Get menu choice (with input validation)
        int memberMenuChoice = getMenuChoice(displayMemberMenu);

        switch (memberMenuChoice) {
            case 0: { // Exit member menu
                return;
            }
            case 1: { // Register member
                string name, phone, email, address;
                int id;

                // Get member name
                name = getStrInput("Enter member name: ");

                // Get member ID (with input validation)
                id = getIdInput("Enter member ID: ");

                // Check if the member ID exists before proceeding
                if (memberIdExists(library.getMembers(), id)) {
                    cout << "Member ID already exists. Please try again." << endl;
                    continue; // Return to member menu since name may need to be reentered
                }

                // Get phone number
                phone = getStrInput("Enter phone: ");

                // Get email address
                email = getStrInput("Enter email: ");

                // Get home address
                address = getStrInput("Enter address: ");

                library.registerMember(Member(name, id, phone, email, address));
                break;
            }
            case 2: { // Edit member
                string name, phone, email, address;
                int id;
                
                // Get member ID (with input validation)
                id = getIdInput("Enter ID of member to edit: ");

                // Check if the member ID exists before proceeding
                if (!memberIdExists(library.getMembers(), id)) {
                    cout << "Member ID not found. Please try again." << endl;
                    continue; // Return to member menu since there may not be any members in the library
                }

                // Get new name
                name = getStrInput("Enter new name: ");

                // Get new phone number
                phone = getStrInput("Enter new phone: ");

                // Get new email address
                email = getStrInput("Enter new email: ");

                // Get new home address
                address = getStrInput("Enter new address: ");

                library.editMember(id, Member(name, id, phone, email, address));
                break;
            }
            case 3: { // Delete member
                int id;

                // Get member ID (with input validation)
                id = getIdInput("Enter ID of member to delete: ");

                // Check if the member ID exists before proceeding
                if (!memberIdExists(library.getMembers(), id)) {
                    cout << "Member ID not found. Please try again." << endl;
                    continue;
                }

                library.deleteMember(id);
                break;
            }
            case 4: { // Display members
                library.displayMembers();
                break;
            }
            default: cout << "Invalid option. Please try again." << endl;
        }
    }
}

void doBorrow(Library& library) {
    string isbn;
    int memberID;

    // Get ISBN of book to borrow
    isbn = getStrInput("Enter ISBN of the book to borrow: ");

    // Check if the ISBN exists before proceeding
    if (!isbnExists(library.getBooks(), isbn)) {
        cout << "ISBN not found. Please try again." << endl;
        return;
    }

    // Get member ID
    memberID = getIdInput("Enter member ID: ");

    // Check if member exists before proceeding
    if (!memberIdExists(library.getMembers(), memberID)) {
        cout << "Member not found. Please try again." << endl;
        return;
    }

    library.borrowBook(isbn, memberID);
}

void doReturn(Library& library) {
    string isbn;
    int memberID;

    // Get ISBN of book to return
    isbn = getStrInput("Enter ISBN of the book to return: ");

    // Check if the ISBN exists before proceeding
    if (!isbnExists(library.getBooks(), isbn)) {
        cout << "ISBN not found. Please try again." << endl;
        return;
    }

    // Get member ID
    memberID = getIdInput("Enter member ID: ");

    // Check if member exists before proceeding
    if (!memberIdExists(library.getMembers(), memberID)) {
        cout << "Member not found. Please try again." << endl;
        return;
    }

    library.returnBook(isbn, memberID);
}

// Function to allow user to search library for books
void doSearch(Library& library) {
    // Get search menu choice (with input validation)
    int searchChoice = getMenuChoice(displaySearchMenu);

    // Get search query
    string query = getStrInput("Enter your search query: ");

    // Perform the search based on user choice
    switch (searchChoice) {
        case 1:
            library.searchBook(query, "title");
            break;
        case 2:
            library.searchBook(query, "author");
            break;
        case 3:
            library.searchBook(query, "isbn");
            break;
        case 4:
            library.searchBook(query, "callnumber");
            break;
        case 5:
            library.searchBook(query, "genre");
            break;
        case 6:
            library.searchBook(query, "pubdate");
            break;
        case 7:
            library.searchBook(query, "any");
            break;
        default:
            cout << "Invalid option. Please select a number between 1 and 7." << endl;
            break;
    }
}

// Function to allow user to manage reservations
void manageReservations(Library& library) {
    while (true) {
        // Get menu choice (with input validation)
        int reservationMenuChoice = getMenuChoice(displayReservationMenu);

        switch (reservationMenuChoice) {
            case 0: { // Exit reservation menu
                return;
            }
            case 1: { // Make reservation
                string isbn;
                int memberID;

                // Get ISBN of book to reserve
                isbn = getStrInput("Enter ISBN of the book to reserve: ");

                // Check if the ISBN exists before proceeding
                if (!isbnExists(library.getBooks(), isbn)) {
                    cout << "ISBN not found. Please try again." << endl;
                    continue;
                }

                // Get member ID
                memberID = getIdInput("Enter member ID: ");

                // Check if member exists before proceeding
                if (!memberIdExists(library.getMembers(), memberID)) {
                    cout << "Member not found. Please try again." << endl;
                    continue;
                }

                library.reserveBook(isbn, memberID);
                break;
            }
            case 2: { // Cancel reservation
                string isbn;
                int memberID;

                // Get ISBN of book to cancel reservation for
                isbn = getStrInput("Enter ISBN of the book to cancel reservation for: ");

                // Check if the ISBN exists before proceeding
                if (!isbnExists(library.getBooks(), isbn)) {
                    cout << "ISBN not found. Please try again." << endl;
                    continue;
                }

                // Get member ID
                memberID = getIdInput("Enter member ID to cancel reservation for: ");

                // Check if member exists before proceeding
                if (!memberIdExists(library.getMembers(), memberID)) {
                    cout << "Member not found. Please try again." << endl;
                    continue;
                }

                library.cancelReservation(isbn, memberID);
                break;
            }
            case 3: { // Display reservations
                try {
                    library.displayReservations();
                } catch (const exception &e) {
                    cout << "Error: " << e.what() << endl;
                }
                break;
            }
            default: cout << "Invalid option. Please try again." << endl;
        }
    }
}

// Function to allow user to manage transactions
void manageTransactions(Library& library) {
    while (true) {
        // Get menu choice (with input validation)
        int transactionMenuChoice = getMenuChoice(displayTransactionMenu);

        switch (transactionMenuChoice) {
            case 0: // Exit transactions menu
                return;
            case 1: // Display transactions
                library.displayTransactions();
                break;
            case 2: // Delete transaction history
                library.deleteTransactionHistory();
                break;
            default: cout << "Invalid option. Please try again." << endl;
        }
    }
}

int main() {
    Library library;
    bool running = true;
    const string filename = "library_data.txt";

    // Check if the file exists
    ifstream file(filename);
    if (file.good()) {
        // Load data from file
        try {
            library.loadFromFile(filename);
        }
        catch (const exception &e) {
            cout << "Error: " << e.what() << endl;
        }
    } else {
        cout << "Error: File '" << filename << "' does not exist. It will be automatically created when the program exits." << endl;
    }

    while (running) {
        // Get main menu choice (with input validation)
        int mainMenuChoice = getMenuChoice(displayMainMenu);

        switch (mainMenuChoice) {
            case 0: {
                // Save data to file
                try {
                    library.saveToFile(filename);
                } catch (const exception &e) {
                    cout << "Error: " << e.what() << endl;
                }
                cout << "Exiting library." << endl;
                running = false;
                break;
            }
            case 1: // Book sub-menu
                manageBooks(library);
                break;
            case 2: // Member sub-menu
                manageMembers(library);
                break;
            case 3: // Borrow book
                doBorrow(library);
                break;
            case 4: // Return book
                doReturn(library);
                break;
            case 5: // Search book
                doSearch(library);
                break;
            case 6: // Reservations sub-menu
                manageReservations(library);
                break;
            case 7: // Transactions sub-menu
                manageTransactions(library);
                break;
            default: cout << "Invalid option. Please try again." << endl;
        }
    }
    return 0;
}
