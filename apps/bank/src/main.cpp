#include <iostream>
#include <iomanip>
#include "bank.hpp"

void BankAccount::recordTransaction(const std::string& description) {
    transactionHistory.push_back(description);
}

BankAccount::BankAccount(const std::string& owner, const std::string& accountNumber, double initialBalance)
    : owner(owner), accountNumber(accountNumber), balance(initialBalance) {
    recordTransaction("Account opened with balance: " + std::to_string(initialBalance));
}

std::string BankAccount::getOwner() const { return owner; }
std::string BankAccount::getAccountNumber() const { return accountNumber; }
double BankAccount::getBalance() const { return balance; }
std::vector<std::string> BankAccount::getTransactionHistory() const { return transactionHistory; }

bool BankAccount::deposit(double amount) {
    if (amount <= 0) return false;
    balance += amount;
    recordTransaction("Deposited: " + std::to_string(amount));
    return true;
}

bool BankAccount::withdraw(double amount) {
    if (amount <= 0 || amount > balance) return false;
    balance -= amount;
    recordTransaction("Withdrew: " + std::to_string(amount));
    return true;
}

bool BankAccount::transfer(BankAccount& target, double amount) {
    if (!withdraw(amount)) return false;
    target.deposit(amount);
    recordTransaction("Transferred " + std::to_string(amount) + " to " + target.getAccountNumber());
    return true;
}

void BankAccount::printInfo() const {
    std::cout << "=== Bank Account ===" << std::endl;
    std::cout << "Owner:   " << owner << std::endl;
    std::cout << "Account: " << accountNumber << std::endl;
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Balance: $" << balance << std::endl;
}

SavingsAccount::SavingsAccount(const std::string& owner, const std::string& accountNumber,
                                double initialBalance, double interestRate)
    : BankAccount(owner, accountNumber, initialBalance), interestRate(interestRate) {}

double SavingsAccount::getInterestRate() const { return interestRate; }

void SavingsAccount::applyInterest() {
    double interest = getBalance() * (interestRate / 100.0);
    deposit(interest);
    std::cout << "Interest applied: $" << std::fixed << std::setprecision(2) << interest << std::endl;
}

void SavingsAccount::printInfo() const {
    std::cout << "=== Savings Account ===" << std::endl;
    std::cout << "Owner:         " << getOwner() << std::endl;
    std::cout << "Account:       " << getAccountNumber() << std::endl;
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Balance:       $" << getBalance() << std::endl;
    std::cout << "Interest Rate: " << interestRate << "%" << std::endl;
}

CreditAccount::CreditAccount(const std::string& owner, const std::string& accountNumber,
                              double initialBalance, double creditLimit)
    : BankAccount(owner, accountNumber, initialBalance), creditLimit(creditLimit), debt(0.0) {}

double CreditAccount::getCreditLimit() const { return creditLimit; }
double CreditAccount::getDebt() const { return debt; }
double CreditAccount::getAvailableCredit() const { return creditLimit - debt; }

bool CreditAccount::borrow(double amount) {
    if (amount <= 0 || amount > getAvailableCredit()) return false;
    debt += amount;
    deposit(amount);
    std::cout << "Borrowed: $" << std::fixed << std::setprecision(2) << amount << std::endl;
    return true;
}

bool CreditAccount::repay(double amount) {
    if (amount <= 0 || amount > debt) return false;
    if (!withdraw(amount)) return false;
    debt -= amount;
    std::cout << "Repaid: $" << std::fixed << std::setprecision(2) << amount << std::endl;
    return true;
}

void CreditAccount::printInfo() const {
    std::cout << "=== Credit Account ===" << std::endl;
    std::cout << "Owner:            " << getOwner() << std::endl;
    std::cout << "Account:          " << getAccountNumber() << std::endl;
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Balance:          $" << getBalance() << std::endl;
    std::cout << "Credit Limit:     $" << creditLimit << std::endl;
    std::cout << "Debt:             $" << debt << std::endl;
    std::cout << "Available Credit: $" << getAvailableCredit() << std::endl;
}

int main() {
    std::cout << "--- Creating accounts ---" << std::endl;
    BankAccount basic("Alice Johnson", "ACC-001", 1000.00);
    SavingsAccount savings("Bob Smith", "SAV-001", 5000.00, 3.5);
    CreditAccount credit("Carol White", "CRE-001", 200.00, 2000.00);

    std::cout << std::endl;
    basic.printInfo();
    std::cout << std::endl;
    savings.printInfo();
    std::cout << std::endl;
    credit.printInfo();

    std::cout << std::endl << "--- Performing operations ---" << std::endl;

    basic.deposit(500.00);
    std::cout << "Alice deposited $500. New balance: $" << basic.getBalance() << std::endl;

    basic.withdraw(200.00);
    std::cout << "Alice withdrew $200. New balance: $" << basic.getBalance() << std::endl;

    std::cout << std::endl;
    savings.applyInterest();
    std::cout << "Bob's balance after interest: $" << savings.getBalance() << std::endl;

    std::cout << std::endl;
    credit.borrow(750.00);
    std::cout << "Carol's available credit after borrowing: $" << credit.getAvailableCredit() << std::endl;

    credit.repay(300.00);
    std::cout << "Carol's debt after partial repayment: $" << credit.getDebt() << std::endl;

    std::cout << std::endl << "--- Transfer between accounts ---" << std::endl;
    basic.transfer(savings, 300.00);
    std::cout << "Alice transferred $300 to Bob." << std::endl;
    std::cout << "Alice's balance: $" << basic.getBalance() << std::endl;
    std::cout << "Bob's balance:   $" << savings.getBalance() << std::endl;

    std::cout << std::endl << "--- Transaction History (Alice) ---" << std::endl;
    for (const auto& entry : basic.getTransactionHistory()) {
        std::cout << "  > " << entry << std::endl;
    }

    std::cout << std::endl << "--- Final State ---" << std::endl;
    basic.printInfo();
    std::cout << std::endl;
    savings.printInfo();
    std::cout << std::endl;
    credit.printInfo();

    return 0;
}