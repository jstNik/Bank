//
// Created by nicco on 18/01/2023.
//

#ifndef MAIN_CPP_TRANSACTION_H
#define MAIN_CPP_TRANSACTION_H

#include "AddressBook.h"


class Transaction {
public:

    Transaction(std::string &from, float amount, std::string &to, std::string &date);

    explicit Transaction(Transaction &original) = delete;

    Transaction &operator=(Transaction &right) = delete;

    std::string getFrom() const { return from; }

    void setFrom(const std::string &newFrom) { from=newFrom; }

    std::string getTo() const { return to; }

    void setTo(const std::string &newTo) { to=newTo; }

    float getAmount() const { return amount; }

    void setAmount(float newAmount) { amount=newAmount; }

    std::string getDate() const { return date; }

private:

    std::string from, to, date;

    float amount;

};


#endif //MAIN_CPP_TRANSACTION_H
