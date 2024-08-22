/* Program name: Member.h
* Author: Joshua Yin
* Date last updated: 7/24/2024
* Purpose: Define the member class
*/

#ifndef MEMBER_H
#define MEMBER_H

#include <iostream>
#include <string>

using namespace std;

class Member {
private:
    string name;
    int memberID;
    string phone;
    string email;
    string address;

public:
    // Constructor
    Member(string name, int memberID, string phone, string email, string address);

    // Getters
    string getName() const;
    int getMemberID() const;
    string getPhone() const;
    string getEmail() const;
    string getAddress() const;

    // Setters
    void setName(const string &name);
    void setMemberID(int memberID);
    void setPhone(const string &phone);
    void setEmail(const string &email);
    void setAddress(const string &address);

    // Display member details
    void display() const;
};

#endif
