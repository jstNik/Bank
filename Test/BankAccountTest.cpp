//
// Created by nicco on 28/11/2022.
//
#include "gtest/gtest.h"
#include "../BankAccount.h"

TEST(BankAccount, TestUsernameNotEmpty) {
    auto a = std::make_unique<AddressBook>();
    ASSERT_THROW(auto ba1 = BankAccount::createBankAccount("", "", "", 0, a.get()), MoreExceptions);
    ASSERT_THROW(auto ba1 = BankAccount::createBankAccount("Luca", "", "", 0, a.get()), MoreExceptions);
    ASSERT_THROW(auto ba1 = BankAccount::createBankAccount("", "Feltri", "", 0, a.get()), MoreExceptions);
    ASSERT_THROW(auto ba1 = BankAccount::createBankAccount("", "", "luca.feltri", 0, a.get()), MoreExceptions);
    ASSERT_THROW(auto ba1 = BankAccount::createBankAccount("", "", "luca.feltri", 0, a.get()), MoreExceptions);
    ASSERT_THROW(auto ba1 = BankAccount::createBankAccount("Luca", "Feltri", "luca.feltri", -10, a.get()), MoreExceptions);
    ASSERT_NO_THROW(auto ba1 = BankAccount::createBankAccount("Luca", "Feltri", "luca.feltri", 0, a.get()));

    auto ba1 = BankAccount::createBankAccount("Luca", "Feltri", "luca.feltri", 0, a.get());
    ASSERT_NE(ba1, nullptr);
    ASSERT_THROW(auto ba2 = BankAccount::createBankAccount("Luca", "Feltri", "luca.feltri", 0, a.get()), MoreExceptions);
}