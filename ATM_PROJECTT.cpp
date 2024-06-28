#include <iostream>
#include <iomanip>
#include <string>
#include <map>
using namespace std;
class Account {
private:
    string accountNumber;
    string pin;
    double balance;
public:
    Account(string accNum, string pinNum, double initialBalance) {
        accountNumber = accNum;
        pin = pinNum;
        balance = initialBalance;
    }
    string getAccountNumber() {
        return accountNumber;
    }
    bool validatePin(string enteredPin) {
        return pin == enteredPin;
    }
    double getBalance() {
        return balance;
    }
    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Deposit successful. Current balance is: " << fixed << setprecision(2) << balance << endl;
        }
        else {
            cout << "Invalid amount." << endl;
        }
    }
    bool withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            cout << "Withdrawal successful. Current balance is: " << fixed << setprecision(2) << balance << endl;
            return true;
        }
        else {
            cout << "Invalid amount or insufficient balance." << endl;
            return false;
        }
    }
};

class ATM {
private:
    map<string, Account> accounts;

public:
    void addAccount(string accNum, string pin, double balance) {
        Account newAccount(accNum, pin, balance);
        accounts.insert({ accNum, newAccount });
    }

    void displayMenu() {
        cout << "ATM Interface" << endl;
        cout << "1. Check Balance" << endl;
        cout << "2. Withdraw" << endl;
        cout << "3. Deposit" << endl;
        cout << "4. Exit" << endl;
        cout << "Choose an option: ";
    }

    Account* getAccount(string accNum) {
        auto it = accounts.find(accNum);
        if (it != accounts.end()) {
            return &it->second;
        }
        return nullptr;
    }
};

int main() {
    ATM atm;
    atm.addAccount("123456", "1234", 100000.0);
    string enteredAccNum, enteredPin;
    int option;
    double amount;

    cout << "Enter your account number: ";
    cin >> enteredAccNum;
    cout << "Enter your PIN: ";
    cin >> enteredPin;

    Account* currentAccount = atm.getAccount(enteredAccNum);
    if (currentAccount == nullptr || !currentAccount->validatePin(enteredPin)) {
        cout << "Invalid account number or PIN. Exiting..." << endl;
        return 1;
    }
    do {
        atm.displayMenu();
        cin >> option;
        switch (option) {
        case 1:
            cout << "Your balance is: " << fixed << setprecision(2) << currentAccount->getBalance() << endl;
            break;
        case 2:
            cout << "Enter amount to withdraw: ";
            cin >> amount;
            currentAccount->withdraw(amount);
            break;
        case 3:
            cout << "Enter amount to deposit: ";
            cin >> amount;
            currentAccount->deposit(amount);
            break;
        case 4:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid option." << endl;
        }

    } while (option != 4);
}