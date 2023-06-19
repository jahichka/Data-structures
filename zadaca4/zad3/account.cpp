#include <chrono>
#include <ctime>
#include <iostream>
#include <queue>
#include <time.h>

class Account {
private:
  float balance{0};

public:
  Account() {}
  Account(float amount) : balance(amount) {}
  void changeBallance(float amount) { balance += amount; }
  void print() { std::cout << balance << " KM" << std::endl; }
};

class Transaction {
private:
  // ttime = std::chrono::system_clock::now();
  float amount_{0};

public:
  Transaction(float amount) : amount_(amount) {}
  float getAmount() { return amount_; }
};

class ATM {
private:
  std::queue<Transaction> transactions;

public:
  ATM() {}
  void NewTransaction() {
    float amount;
    std::cout << "Input the amount: ";
    std::cin >> amount;
    transactions.push(Transaction(amount));
  }

  void ApplyTransaction(Account& currentAccount) {
    if(transactions.empty()) std::cout<<"No pending transactions"<<std::endl;
    else{
    currentAccount.changeBallance(transactions.front().getAmount());
    transactions.pop();
    }
  }

  void PendingTransaction() {
    if (transactions.empty())
      std::cout << "No pending transactions" << std::endl;
    else {
      std::cout << transactions.front().getAmount() << std::endl;
    }
  }

  void DiscardPendingTransaction() { transactions.pop(); }

  void Balance(Account currentAccount) { currentAccount.print(); }
};