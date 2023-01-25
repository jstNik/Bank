//
// Created by nicco on 28/11/2022.
//
#include <memory>

#include "gtest/gtest.h"
#include "../BankAccount.h"

class BankAccountSuite : public ::testing::Test {
protected:

    void SetUp() override {
        ad = std::make_unique<AddressBook>();
        ba1 = BankAccount::createBankAccount("Marco", "Rossi", "marco.rossi", 1000, ad.get());
        ba2 = BankAccount::createBankAccount("Laura", "Frizzi", "laura.frizzi", 100, ad.get());
        ba3 = BankAccount::createBankAccount("Laura", "Gelsi", "laura.gelsi", 300, ad.get());
    }

    std::unique_ptr<AddressBook> ad;
    std::unique_ptr<BankAccount> ba1;
    std::unique_ptr<BankAccount> ba2;
    std::unique_ptr<BankAccount> ba3;

    void TearDown() override {}
};


TEST_F(BankAccountSuite, TestSendMoney) {
    ASSERT_NO_THROW(ba1->transfer("laura.frizzi", 10));
    ASSERT_EQ(ba1->getBalance(), 1000 - 10);
    ASSERT_EQ(ba2->getBalance(), 100 + 10);
    ASSERT_NO_THROW(ba1->searchTransaction(1));
    ASSERT_NO_THROW(ba2->searchTransaction(1));
    ASSERT_EQ(ba1->searchTransaction(1), ba2->searchTransaction(1));
    ASSERT_NO_THROW(ba1->getTransactionFrom(1));
    ASSERT_EQ(ba1->getTransactionFrom(1), "marco.rossi");
    ASSERT_NO_THROW(ba2->getTransactionFrom(1));
    ASSERT_EQ(ba2->getTransactionFrom(1), "marco.rossi");
    ASSERT_NO_THROW(ba1->getTransactionTo(1));
    ASSERT_EQ(ba1->getTransactionTo(1), "laura.frizzi");
    ASSERT_NO_THROW(ba2->getTransactionTo(1));
    ASSERT_EQ(ba2->getTransactionTo(1), "laura.frizzi");
    ASSERT_NO_THROW(ba1->getTransactionAmount(1));
    ASSERT_EQ(ba1->getTransactionAmount(1), 10);
    ASSERT_NO_THROW(ba2->getTransactionAmount(1));
    ASSERT_EQ(ba2->getTransactionAmount(1), 10);
}

TEST_F(BankAccountSuite, TestCantSendMoneyToYourself) {
    ASSERT_NO_THROW(ba1->transfer("marco.rossi", 10));
    ASSERT_EQ(ba1->getBalance(), 1000);
    ASSERT_THROW(ba1->searchTransaction(1), MoreExceptions);
}

TEST_F(BankAccountSuite, TestNoEnoughFunds) {
    ASSERT_NO_THROW(ba1->transfer("laura.frizzi", 2000));
    ASSERT_EQ(ba1->getBalance(), 1000);
    ASSERT_EQ(ba2->getBalance(), 100);
    ASSERT_THROW(ba1->searchTransaction(1), MoreExceptions);
    ASSERT_THROW(ba2->searchTransaction(1), MoreExceptions);
}

TEST_F(BankAccountSuite, TestHaveTosendMoreThan0) {
    ASSERT_NO_THROW(ba1->transfer("laura.frizzi", 0));
    ASSERT_EQ(ba1->getBalance(), 1000);
    ASSERT_EQ(ba2->getBalance(), 100);
    ASSERT_THROW(ba1->searchTransaction(1), MoreExceptions);
    ASSERT_THROW(ba2->searchTransaction(1), MoreExceptions);
}

TEST_F(BankAccountSuite, TestEditTransactionFrom) {
    ba1->transfer("laura.frizzi", 50);
    ASSERT_NO_THROW(ba1->editTransactionFrom(1, "laura.gelsi"));
    ASSERT_THROW(ba1->searchTransaction(1), MoreExceptions);
    ASSERT_EQ(ba2->getTransactionFrom(1), "laura.gelsi");
    ASSERT_EQ(ba3->getTransactionFrom(1), "laura.gelsi");
    ASSERT_EQ(ba1->getBalance(), 1000);
    ASSERT_EQ(ba3->getBalance(), 300 - 50);
}

TEST_F(BankAccountSuite, TestEditTransactionTo) {
    ba1->transfer("laura.frizzi", 50);
    ASSERT_NO_THROW(ba1->editTransactionTo(1, "laura.gelsi"));
    ASSERT_EQ(ba1->getTransactionTo(1), "laura.gelsi");
    ASSERT_THROW(ba2->searchTransaction(1), MoreExceptions);
    ASSERT_EQ(ba3->getTransactionTo(1), "laura.gelsi");
    ASSERT_EQ(ba2->getBalance(), 100);
    ASSERT_EQ(ba3->getBalance(), 300 + 50);
}

TEST_F(BankAccountSuite, TestEditTransactionAmount) {
    ba1->transfer("laura.frizzi", 900);
    ASSERT_NO_THROW(ba1->editTransactionAmount(1, 800));
    ASSERT_EQ(ba1->getTransactionAmount(1), 800);
    ASSERT_EQ(ba2->getTransactionAmount(1), 800);
    ASSERT_EQ(ba1->getBalance(), 1000 - 800);
    ASSERT_EQ(ba2->getBalance(), 100 + 800);
    ASSERT_NO_THROW(ba1->editTransactionAmount(1, 0));
    ASSERT_THROW(ba1->searchTransaction(1), MoreExceptions);
    ASSERT_THROW(ba2->searchTransaction(1), MoreExceptions);
}

TEST_F(BankAccountSuite, TestEditTransactionAmountFailing) {
    ba1->transfer("laura.frizzi", 900);
    ba2->transfer("laura.gelsi", 1000);
    ASSERT_NO_THROW(ba1->editTransactionAmount(1, 800));
    ASSERT_NO_THROW(ba1->editTransactionAmount(1, 1100));
    ASSERT_NO_THROW(ba1->editTransactionAmount(1, 0));
    ASSERT_EQ(ba1->getBalance(), 1000 - 900);
    ASSERT_EQ(ba2->getBalance(), 100 + 900 - 1000);
}

TEST_F(BankAccountSuite, TestEditTransactionFromFailing) {
    ba1->transfer("laura.frizzi", 900);
    ASSERT_NO_THROW(ba1->editTransactionFrom(1, "laura.gelsi"));
    ASSERT_EQ(ba1->getBalance(), 1000 - 900);
    ASSERT_EQ(ba3->getBalance(), 300);
}

TEST_F(BankAccountSuite, TestEditTransactionToFailing) {
    ba1->transfer("laura.frizzi", 900);
    ba2->transfer("laura.gelsi", 1000);
    ASSERT_NO_THROW(ba1->editTransactionTo(1, "laura.gelsi"));
    ASSERT_EQ(ba2->getBalance(), 1000 - 1000);
    ASSERT_EQ(ba3->getBalance(), 300 + 1000);
}