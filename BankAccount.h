//
// Created by Utente on 13/10/2022.
//

#ifndef LABPROG_BANKACCOUNT_H
#define LABPROG_BANKACCOUNT_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <dirent.h>
#include "MoreExceptions.h"
#include "Subject.h"
#include "Observer.h"
#include "AddressBook.h"
#include "Transaction.h"

class BankAccount : public Subject {
public:

    static std::unique_ptr<BankAccount>
    createBankAccount(const std::string &name, const std::string &surname, const std::string &username, float deposit,
                      AddressBook *addressBook);

    ~BankAccount() override;

    BankAccount &operator=(BankAccount &right) = delete;

    explicit BankAccount(BankAccount &original) = delete;

    void transfer(std::string contact, float amount);

    float getBalance() const { return balance; }

    std::string getName() const { return name; }

    void setName(const std::string &newName) { name = newName; }

    std::string getSurname() const { return surname; }

    void setSurname(const std::string &newSurname) { surname = newSurname; }

    std::string getUsername() const { return myUsername; }

    void setUsername(const std::string &newUsername) { myUsername = newUsername; }

    void enableNotifications() override;

    void disableNotifications() override;

    void addContact(const std::string &contact, const std::string &username);

    void deleteContact(const std::string &contact);

    Transaction *searchTransaction(int id);

    void editTransactionFrom(int id, const std::string& newFrom);

    void editTransactionTo(int id, const std::string& newTo);

    void editTransactionAmount(int id, float newAmount);

    std::string getTransactionFrom(int id) const;

    std::string getTransactionTo(int id) const;

    float getTransactionAmount(int id) const;

    void printTransactions();

private:

    BankAccount(std::string name, std::string surname, std::string username, float deposit, AddressBook *addressBook);

    void transfer(std::string &username, BankAccount *to, float amount, bool isUnknown);

    void sendMoney(std::string &username, float sent, bool isUnknown);

    void getMoney(std::string username, float received);

    void setBalance(float newBalance);

    void addTransaction(int id, const std::shared_ptr<Transaction> &transaction);

    void deleteTransaction(int id);

    std::string myUsername;

    std::string name;

    std::string surname;

    float balance;

    std::unique_ptr<Observer> notificator;

    std::map<std::string, std::string> contacts;

    std::map<int, std::shared_ptr<Transaction>> transactions;

    AddressBook *addressBook;

    std::fstream transactionsPrinter;

};


#endif //LABPROG_BANKACCOUNT_H
