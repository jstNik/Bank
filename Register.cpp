//
// Created by Utente on 25/11/2022.
//

#include "Register.h"

void Register::update(std::string theOtherUser, float amount, float currentBalance, bool isUnknown) {
    if (!isUnknown) {
        if (amount < 0)
            std::cout << "€ " << -amount << " have been sent to " << theOtherUser << ". Current balance : € " << currentBalance << std::endl;
        if (amount > 0)
            std::cout << "You received € " << amount << " from " << theOtherUser << ". Current balance: € "<< currentBalance << std::endl;
    } else {
        if (amount < 0)
            std::cout << "€ " << -amount << " has been sent to an unknown user (" << theOtherUser << "). Current balance: € " << currentBalance << std::endl;
        if (amount > 0)
            std::cout << "You received € " << amount << " from an unknown user (" << theOtherUser << "). Current balance: € " << currentBalance << std::endl;
    }
}
