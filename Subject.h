//
// Created by Utente on 25/11/2022.
//


#ifndef BANKACCOUNT_CPP_SUBJECT_H
#define BANKACCOUNT_CPP_SUBJECT_H

#endif //BANKACCOUNT_CPP_SUBJECT_H

class Subject {
public:

    virtual void enableNotifications() = 0;

    virtual void disableNotifications() = 0;

protected:

    virtual ~Subject() = default;
};