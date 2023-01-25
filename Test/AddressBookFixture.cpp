//
// Created by nicco on 10/01/2023.
//

#include <memory>
#include "gtest/gtest.h"
#include "../AddressBook.h"
#include "../BankAccount.h"

class AddressBookSuite : public ::testing::Test {
protected:

    void SetUp() override {
        ad = std::make_unique<AddressBook>();
        ba = BankAccount::createBankAccount("Marco", "Rossi", "marco.rossi", 1000, ad.get());
        username = ba->getUsername();
    }

    std::unique_ptr<AddressBook> ad;
    std::unique_ptr<BankAccount> ba;
    std::string username;

    void TearDown() override {}

};

TEST_F(AddressBookSuite, TestAddAccount) {
    ad->addUsername(username, ba.get());
    ASSERT_EQ(ad->searchUsername(username), username);
    ASSERT_EQ(ad->searchAddress(username), ba.get());
}

TEST_F(AddressBookSuite, TestDeleteAccount) {
    ad->addUsername(username, ba.get());
    ad->deleteUsername(username);
    ASSERT_THROW(ad->searchUsername(username), MoreExceptions);
    ASSERT_THROW(ad->searchAddress(username), MoreExceptions);
}

TEST_F(AddressBookSuite, TestSearchAccount) {
    ad->addUsername(username, ba.get());
    ASSERT_NO_THROW(ad->searchUsername(username));
    ASSERT_NO_THROW(ad->searchAddress(username));
    ASSERT_THROW(ad->searchUsername("laura.frizzi"), MoreExceptions);
    ASSERT_THROW(ad->searchAddress("laura.frizzi"), MoreExceptions);
}

