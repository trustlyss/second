#pragma once
#include <string>
#include <vector>

class BankAccount {
private:
    std::string owner;
    std::string accountNumber;
    double balance;
    std::vector<std::string> transactionHistory;

    void recordTransaction(const std::string& description);

public:
    BankAccount(const std::string& owner, const std::string& accountNumber, double initialBalance);

    std::string getOwner() const;
    std::string getAccountNumber() const;
    double getBalance() const;
    std::vector<std::string> getTransactionHistory() const;

    bool deposit(double amount);
    bool withdraw(double amount);
    bool transfer(BankAccount& target, double amount);

    void printInfo() const;
};

class SavingsAccount : public BankAccount {
private:
    double interestRate;

public:
    SavingsAccount(const std::string& owner, const std::string& accountNumber,
                   double initialBalance, double interestRate);

    double getInterestRate() const;
    void applyInterest();
    void printInfo() const;
};

class CreditAccount : public BankAccount {
private:
    double creditLimit;
    double debt;

public:
    CreditAccount(const std::string& owner, const std::string& accountNumber,
                  double initialBalance, double creditLimit);

    double getCreditLimit() const;
    double getDebt() const;
    double getAvailableCredit() const;

    bool borrow(double amount);
    bool repay(double amount);

    void printInfo() const;
};