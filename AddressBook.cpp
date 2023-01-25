//
// Created by Utente on 25/11/2022.
//

#include <memory>
#include "AddressBook.h"
#include "BankAccount.h"

void AddressBook::addUsername(const std::string &username, BankAccount *address) {
    addresses.insert(std::make_pair(username, address));
}

void AddressBook::deleteUsername(const std::string &username) {
    addresses.erase(username);
}

BankAccount *AddressBook::searchAddress(const std::string &username) {
    if (username == addresses.find(username)->first)
        return addresses.find(username)->second;
    else
        throw MoreExceptions("Account does not exist.");
}

std::string AddressBook::searchUsername(const std::string &username) {
    if (username == addresses.find(username)->first)
        return addresses.find(username)->first;
    else
        throw MoreExceptions("Account does not exist.");
}

bool AddressBook::doesItExist(const std::string &username) {
    if (username == addresses.find(username)->first)
        return true;
    else
        return false;
}