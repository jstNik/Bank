//
// Created by Utente on 13/10/2022.
//
#include <ctime>
#include <iomanip>
#include <memory>
#include <sys/stat.h>
#include "BankAccount.h"
#include "Register.h"

BankAccount::BankAccount(std::string name, std::string surname, std::string username, float deposit,
                         AddressBook *addressBook) : name(std::move(name)), surname(std::move(surname)),
                                                     myUsername(std::move(username)), balance(deposit),
                                                     addressBook(addressBook) {
    notificator = std::make_unique<Register>();
    (this->addressBook)->addUsername(myUsername, this);
    std::cout << "Your account has been created. Username: " << this->getUsername() << ", Deposit: "
              << this->getBalance() << "€"
              << std::endl;
}

BankAccount::~BankAccount() {
    addressBook->deleteUsername(myUsername);
}

std::unique_ptr<BankAccount>
BankAccount::createBankAccount(const std::string &name, const std::string &surname, const std::string &username,
                               float deposit,
                               AddressBook *addressBook) {
    if (name.empty() || surname.empty() || username.empty())
        throw MoreExceptions("Name, surname or username can not be empty.");
    if (deposit < 0)
        throw MoreExceptions("Invalid deposit amount.");
    if (addressBook->doesItExist(username))
        throw MoreExceptions("username already exists.");
    else
        return std::unique_ptr<BankAccount>(new BankAccount(name, surname, username, deposit, addressBook));
}

void BankAccount::transfer(std::string contact, float amount) {
    try {
        if (contact == contacts.find(contact)->first) {
            std::string to = contacts.find(contact)->second;
            this->transfer(contact, addressBook->searchAddress(to), amount, false);
        } else {
            this->transfer(contact, addressBook->searchAddress(contact), amount, true);
        }
    }
    catch (MoreExceptions &e) {
        std::cerr << e.what() << std::endl;
    }
}

void BankAccount::transfer(std::string &username, BankAccount *to, float amount, bool isUnknown) {
    if (this->getBalance() < amount)
        throw MoreExceptions("Not enough funds.");
    if (to == this)
        throw MoreExceptions("You can not send money to yourself.");
    if (amount <= 0)
        throw MoreExceptions("You have to send more than €0.");
    this->sendMoney(username, amount, isUnknown);
    to->getMoney(myUsername, amount);
    addressBook->incrementTransactions();
    time_t rawTime = time(nullptr);
    std::string date = ctime(&rawTime);
    std::string toUsername = to->getUsername();
    int id = addressBook->getCountTransactions();
    auto t = std::make_shared<Transaction>(myUsername, amount, toUsername, date);
    transactions.insert(std::make_pair(id, t));
    to->addTransaction(id, t);
}

void BankAccount::sendMoney(std::string &username, float sent, bool isUnknown) {
    balance -= sent;
    if (notificator)
        notificator->update(username, -sent, getBalance(), isUnknown);
}

void BankAccount::getMoney(std::string username, float received) {
    balance += received;
    bool isUnknown;
    auto itr = contacts.begin();
    while (itr->second != username && itr != contacts.end()) {
        itr++;
    }
    if (itr->second == username) {
        username = itr->first;
        isUnknown = false;
    } else
        isUnknown = true;
    if (notificator)
        notificator->update(username, received, getBalance(), isUnknown);
}

void BankAccount::enableNotifications() {
    if (!notificator) {
        notificator = std::make_unique<Register>();
        std::cout << "Notifications enabled." << std::endl;
    } else
        std::cout << "Notifications are already enabled." << std::endl;

}

void BankAccount::disableNotifications() {
    if (notificator) {
        notificator = nullptr;
        std::cout << "Notifications disabled." << std::endl;
    } else
        std::cerr << "Notifications are already disabled." << std::endl;
}

void BankAccount::addContact(const std::string &contact, const std::string &username) {
    if (contact != contacts.find(contact)->first) {
        auto search = contacts.begin();
        while (search->second != username && search != contacts.end())
            search++;
        if (search == contacts.end())
            contacts.insert(std::make_pair(contact, addressBook->searchUsername(username)));
        else
            std::cerr << "User already in your contacts" << std::endl;
    } else
        std::cerr << "Name already in your contacts" << std::endl;
}

void BankAccount::deleteContact(const std::string &contact) {
    if (contact == contacts.find(contact)->first)
        contacts.erase(contact);
    else
        std::cerr << "Contact not found." << std::endl;
}

void BankAccount::editTransactionFrom(int id, const std::string &newFrom) {
    try {
        auto search = transactions.find(id);
        if (search != transactions.end()) {
            if (newFrom != search->second->getFrom()) {
                if (newFrom != search->second->getTo()) {
                    if (addressBook->doesItExist(newFrom)) {
                        BankAccount *newFromAddress = addressBook->searchAddress(newFrom);
                        newFromAddress->setBalance(newFromAddress->getBalance() - search->second->getAmount());
                        BankAccount *oldFromAddress = addressBook->searchAddress(search->second->getFrom());
                        oldFromAddress->setBalance(oldFromAddress->getBalance() + search->second->getAmount());
                        search->second->setFrom(newFrom);
                        oldFromAddress->deleteTransaction(id);
                        newFromAddress->addTransaction(id, search->second);
                    } else
                        std::cerr << "Account does not exist." << std::endl;
                } else
                    std::cerr << "The sender and the receiver can not be the same." << std::endl;
            } else
                std::cerr << "You have to change the transaction's sender." << std::endl;
        } else
            std::cerr << "Transaction ID not valid." << std::endl;
    }
    catch (MoreExceptions &e) {
        std::cerr << e.what() << std::endl;
    }
}

void BankAccount::editTransactionTo(int id, const std::string &newTo) {
    try {
        auto search = transactions.find(id);
        if (search != transactions.end()) {
            if (newTo != search->second->getTo()) {
                if (newTo != search->second->getFrom()) {
                    if (addressBook->doesItExist(newTo)) {
                        BankAccount *oldToAddress = addressBook->searchAddress(search->second->getTo());
                        BankAccount *newToAddress = addressBook->searchAddress(newTo);
                        oldToAddress->setBalance(oldToAddress->getBalance() - search->second->getAmount());
                        newToAddress->setBalance(newToAddress->getBalance() + search->second->getAmount());
                        search->second->setTo(newTo);
                        oldToAddress->deleteTransaction(id);
                        newToAddress->addTransaction(id, search->second);
                    } else
                        std::cerr << "Account does not exist." << std::endl;
                } else
                    std::cerr << "The sender and the receiver can not be the same." << std::endl;
            } else
                std::cerr << "You have to change the transaction's receiver." << std::endl;
        } else
            std::cerr << "Transaction ID not valid." << std::endl;
    }
    catch (MoreExceptions &e) {
        std::cerr << e.what() << std::endl;
    }
}

void BankAccount::editTransactionAmount(int id, float newAmount) {
    try {
        auto search = transactions.find(id);
        if (search != transactions.end()) {
            if (newAmount != search->second->getAmount()) {
                BankAccount *to = addressBook->searchAddress(search->second->getTo());
                float oldAmount = search->second->getAmount();
                if (newAmount < oldAmount) {
                    to->setBalance(to->getBalance() + newAmount - oldAmount);
                    setBalance(getBalance() + oldAmount - newAmount);
                    search->second->setAmount(newAmount);
                }
                if (newAmount > oldAmount) {
                    setBalance(getBalance() + oldAmount - newAmount);
                    to->setBalance(to->getBalance() + newAmount - oldAmount);
                    search->second->setAmount(newAmount);
                }
                if (newAmount == 0) {
                    to->setBalance(to->getBalance() - search->second->getAmount());
                    setBalance(getBalance() + search->second->getAmount());
                    deleteTransaction(id);
                    to->deleteTransaction(id);
                }
            } else
                std::cerr << "You have to change the transaction's amount." << std::endl;
        } else
            std::cerr << "Transaction ID not valid." << std::endl;
    }
    catch (MoreExceptions &e) {
        std::cerr << e.what() << std::endl;
    }
}

void BankAccount::setBalance(float newBalance) {
    if (newBalance >= 0)
        balance = newBalance;
    else
        throw MoreExceptions("Balance can not be lower than 0");
}

void BankAccount::addTransaction(int id, const std::shared_ptr<Transaction> &transaction) {
    transactions.insert(std::make_pair(id, transaction));
}

void BankAccount::deleteTransaction(int id) {
    auto search = transactions.find(id);
    if (search != transactions.end()) {
        transactions.erase(id);
    } else
        throw MoreExceptions("Transaction ID not valid.");
}

void BankAccount::printTransactions() {
    mkdir("../AllTransactionsDirectory", ACCESSPERMS);
    std::string fileName = "../AllTransactionsDirectory/Transactions Register Of " + name + " " + surname + ".txt";
    std::ofstream outfile(fileName);
    transactionsPrinter.open(fileName);
    for (const auto &itr: transactions)
        transactionsPrinter << "ID: " << itr.first << "\t|\t" << itr.second->getFrom() << " ► " << itr.second->getTo()
                            << "   € " << itr.second->getAmount() << "    " << itr.second->getDate() << std::endl;
    transactionsPrinter.close();
}

std::string BankAccount::getTransactionFrom(int id) const {
    auto search = transactions.find(id);
    if (search != transactions.end())
        return search->second->getFrom();
    else
        throw MoreExceptions("Transaction ID not valid.");
}

std::string BankAccount::getTransactionTo(int id) const {
    auto search = transactions.find(id);
    if (search != transactions.end())
        return search->second->getTo();
    else
        throw MoreExceptions("Transaction ID not valid.");
}

float BankAccount::getTransactionAmount(int id) const {
    auto search = transactions.find(id);
    if (search != transactions.end())
        return search->second->getAmount();
    else
        throw MoreExceptions("Transaction ID not valid.");
}

Transaction *BankAccount::searchTransaction(int id) {
    auto search = transactions.find(id);
    if (search != transactions.end())
        return search->second.get();
    else
        throw MoreExceptions("Transaction ID not valid.");
}
