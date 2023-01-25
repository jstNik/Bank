//
// Created by Utente on 25/11/2022.
//

#ifndef BANKACCOUNT_CPP_ADDRESSBOOK_H
#define BANKACCOUNT_CPP_ADDRESSBOOK_H

#include <iostream>
#include <memory>
#include <map>

class BankAccount;

class AddressBook {
public:

    void addUsername(const std::string &username, BankAccount *address);

    void deleteUsername(const std::string &username);

    BankAccount *searchAddress(const std::string &username);

    std::string searchUsername(const std::string &username);

    bool doesItExist(const std::string &username);

    int getCountTransactions() const { return countTransactions; }

    void incrementTransactions() { countTransactions += 1; }

    ~AddressBook() = default;

private:

    int countTransactions;

    std::map<std::string, BankAccount *> addresses;

};


#endif //BANKACCOUNT_CPP_ADDRESSBOOK_H
