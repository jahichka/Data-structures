#include "account.cpp"
#include <iostream>
#include <map>

int main() {
  std::map<short, Account> accounts;
  short pin;
  Account *currentAccount;
  ATM transactions;
  int num;
  bool exit = false;

  accounts.insert(std::pair<short, Account>(1234, Account(50)));
  accounts.insert(std::pair<short, Account>(2345, Account(60)));
  accounts.insert(std::pair<short, Account>(3456, Account(70)));

  std::cout << "Insert PIN: ";
  std::cin>>pin;
  while (accounts.find(pin) == accounts.end()) {
    std::cout << "Wrong pin" << std::endl;
    std::cout << "Insert PIN: ";
    std::cin >> pin;
  }
  currentAccount = &accounts.find(pin)->second;

  while (1) {
    std::cout << std::string(30, '*') << std::endl;
    std::cout << "Actions:" << std::endl;
    std::cout << "\t1. New transaction" << std::endl;
    std::cout << "\t2. Apply transaction" << std::endl;
    std::cout << "\t3. Pending transaction" << std::endl;
    std::cout << "\t4. Discard pending transaction" << std::endl;
    std::cout << "\t5. Balance" << std::endl;
    std::cout << "\t6. Exit" << std::endl;
    std::cout << "Your choice? ";
    std::cin >> num;
    float amount;
    switch (num) {
    case 1:
      transactions.NewTransaction();
      break;

    case 2:
      transactions.ApplyTransaction(*currentAccount);
      break;

    case 3:
      transactions.PendingTransaction();
      break;

    case 4:
      transactions.DiscardPendingTransaction();
      break;

    case 5:
      transactions.Balance(*currentAccount);
      break;

    case 6:
      exit = true;
      break;
    }
    if (exit)
      break;
  }
}