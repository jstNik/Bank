//
// Created by nicco on 27/11/2022.
//

#ifndef ADDRESSBOOK_H_MOREEXCEPTIONS_H
#define ADDRESSBOOK_H_MOREEXCEPTIONS_H

#include <exception>
#include <string>
#include <utility>


class MoreExceptions : public std::exception {
public:
    explicit MoreExceptions(const char *message) noexcept: msg(message) {}

    ~MoreExceptions() noexcept override = default;

    const char *what() { return msg; }

private:
    const char *msg;
};


#endif //ADDRESSBOOK_H_MOREEXCEPTIONS_H
