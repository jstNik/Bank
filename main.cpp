#include <iostream>
#include <unistd.h>
#include "AddressBook.h"
#include "BankAccount.h"

int main() {
    auto ad = std::make_unique<AddressBook>();
    std::unique_ptr<BankAccount> ba1;
    std::unique_ptr<BankAccount> ba2;
    std::unique_ptr<BankAccount> ba3;
    try {
        ba1 = BankAccount::createBankAccount("Marco", "Rossi", "marco.rossi", 1000, ad.get());
    }
    catch (MoreExceptions &e) {
        std::cerr << e.what() << std::endl;
    }
    try {
        ba2 = BankAccount::createBankAccount("Laura", "Frizzi", "laura.frizzi", 800, ad.get());
    }
    catch (MoreExceptions &e) {
        std::cerr << e.what() << std::endl;
    }
    try {
        ba3 = BankAccount::createBankAccount("Nicola", "Piccolini", "nicola.piccolini", 600, ad.get());
    }
    catch (MoreExceptions &e) {
        std::cerr << e.what() << std::endl;
    }

    sleep(2);
    ba1->addContact("Laura", "laura.frizzi");

    std::cout << std::endl;
    sleep(2);

    ba1->disableNotifications();    //  tracking disabled
    ba1->transfer("nicola.piccolini", 10);
    ba1->enableNotifications();  //  tracking enabled

    ba1->transfer("Laura", 100);    //  to a known user
    ba1->transfer("nicola.piccolini", 50);  //  to an unknown user
    ba2->transfer("marco.rossi", 50);   //  from a known user
    ba3->transfer("marco.rossi", 20);   // from an unknown user

    std::cout << std::endl;
    sleep(2);

    //  Illegal actions
    ba1->transfer("marco.rossi", 10);
    ba1->transfer("Laura", -10);
    ba1->transfer("Laura", 10000);
    //

    ba1->printTransactions();
    ba1->editTransactionAmount(1, 50);
    ba1->editTransactionFrom(2, "laura.frizzi");
    ba1->editTransactionFrom(2, "nicola.piccolini");
    ba1->editTransactionTo(4, "nicola.piccolini");


    std::cout << std::endl;
    ba1->printTransactions();
    ba2->printTransactions();
    ba3->printTransactions();
    sleep(2);


    std::cout << "Marco Rossi started with €1000. Current balance: €" << ba1->getBalance() << "." << std::endl;
    std::cout << "Laura Frizzi started with €800. Current balance: €" << ba2->getBalance() << "." << std::endl;
    std::cout << "Nicola Piccolini started with €600. Current balance: €" << ba3->getBalance() << "." << std::endl;

    return 0;
}
