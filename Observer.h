//
// Created by Utente on 25/11/2022.
//

#ifndef BANKACCOUNT_CPP_OBSERVER_H
#define BANKACCOUNT_CPP_OBSERVER_H

class Observer {
public:

    virtual void update(std::string theOtherUser, float amount, float currentBalance, bool isUnknown) = 0;

    virtual ~Observer() = default;
};

#endif //BANKACCOUNT_CPP_OBSERVER_H
