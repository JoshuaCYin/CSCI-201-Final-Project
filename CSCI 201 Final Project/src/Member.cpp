/* Program name: Member.cpp
* Author: Joshua Yin
* Date last updated: 7/24/2024
* Purpose: Implement the member class methods
*/

#include <iostream>
#include <string>

#include "Member.h"

using namespace std;

// Constructor
Member::Member(string n, int i, string p, string e, string a)
    : name(n), memberID(i), phone(p), email(e), address(a) {}

// Getters
string Member::getName() const { return name; }
int Member::getMemberID() const { return memberID; }
string Member::getPhone() const { return phone; }
string Member::getEmail() const { return email; }
string Member::getAddress() const { return address; }

// Setters
void Member::setName(const string &n) { name = n; }
void Member::setMemberID(int i) { memberID = i; }
void Member::setPhone(const string &p) { phone = p; }
void Member::setEmail(const string &e) { email = e; }
void Member::setAddress(const string &a) { address = a; }

// Display member details
void Member::display() const {
    cout << "--------------------\n"
        << "Member Name: " << name << "\n"
        << "ID: " << memberID << "\n"
        << "Phone: " << phone << "\n"
        << "Email: " << email << "\n"
        << "Address: " << address << endl;
}
