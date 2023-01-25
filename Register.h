//
// Created by Utente on 25/11/2022.
//

#ifndef BANKACCOUNT_CPP_REGISTER_H
#define BANKACCOUNT_CPP_REGISTER_H

#include <sstream>
#include <fstream>
#include <dirent.h>
#include "Observer.h"
#include "BankAccount.h"

class Register : public Observer {
public:

    Register() = default;

    ~Register() override = default;

    void update(std::string theOtherUser, float amount, float currentBalance, bool isUnknown) override;

};


#endif //BANKACCOUNT_CPP_REGISTER_H
