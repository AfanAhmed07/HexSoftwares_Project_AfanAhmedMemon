#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <ctime>
using namespace std;

struct Transaction {
    string type;
    double amount;
    double balance;
};

class ATM {
private:
    string name, accountNumber;
    int pin;
    double balance;
    vector<Transaction> history;

public:
    ATM(string n, string acc, int p, double b) {
        name = n;
        accountNumber = acc;
        pin = p;
        balance = b;
    }

    bool login() {
        int enteredPin, attempts = 0;

        while (attempts < 3) {
            cout << "Enter your PIN: ";
            cin >> enteredPin;

            if (enteredPin == pin) {
                cout << "\nLogin Successful! Welcome, " << name << "!\n";
                return true;
            }

            attempts++;
            cout << "Incorrect PIN. Attempts left: "
                 << 3 - attempts << "\n";
        }

        cout << "\nAccount locked due to too many failed attempts.\n";
        return false;
    }

    void checkBalance() {
        cout << "\nCurrent Balance: Rs. "
             << fixed << setprecision(2) << balance << "\n";
    }

    void deposit() {
        double amount;

        cout << "\nEnter amount to deposit: Rs. ";
        cin >> amount;

        if (amount <= 0) {
            cout << "Invalid amount.\n";
            return;
        }

        balance += amount;
        history.push_back({"Deposit", amount, balance});

        cout << "Deposit successful!\n";
        cout << "New Balance: Rs. " << balance << "\n";
    }

    void withdraw() {
        double amount;

        cout << "\nEnter amount to withdraw: Rs. ";
        cin >> amount;

        if (amount <= 0) {
            cout << "Invalid amount.\n";
        }
        else if (amount > balance) {
            cout << "Insufficient balance.\n";
        }
        else if (amount > 50000) {
            cout << "Maximum withdrawal limit is Rs. 50,000.\n";
        }
        else {
            balance -= amount;
            history.push_back({"Withdrawal", amount, balance});

            cout << "Please collect your cash.\n";
            cout << "Remaining Balance: Rs. " << balance << "\n";
        }
    }

    void transfer() {
        string receiver;
        double amount;

        cout << "\nEnter receiver account number: ";
        cin >> receiver;

        cout << "Enter amount to transfer: Rs. ";
        cin >> amount;

        if (amount <= 0) {
            cout << "Invalid amount.\n";
        }
        else if (amount > balance) {
            cout << "Insufficient balance.\n";
        }
        else {
            balance -= amount;
            history.push_back({"Transfer", amount, balance});

            cout << "Transfer successful!\n";
            cout << "Transferred to: " << receiver << "\n";
            cout << "Remaining Balance: Rs. " << balance << "\n";
        }
    }

    void accountInfo() {
        cout << "\n========== ACCOUNT INFORMATION ==========\n";
        cout << "Account Holder : " << name << "\n";
        cout << "Account Number : " << accountNumber << "\n";
        cout << "Balance        : Rs. " << fixed
             << setprecision(2) << balance << "\n";
        cout << "=========================================\n";
    }

    void transactionHistory() {
        cout << "\n========== TRANSACTION HISTORY ==========\n";

        if (history.empty()) {
            cout << "No transactions available.\n";
            return;
        }

        for (int i = 0; i < history.size(); i++) {
            cout << i + 1 << ". "
                 << history[i].type
                 << " | Amount: Rs. "
                 << fixed << setprecision(2)
                 << history[i].amount
                 << " | Balance: Rs. "
                 << history[i].balance << "\n";
        }
    }

    void changePin() {
        int oldPin, newPin, confirmPin;

        cout << "\nEnter current PIN: ";
        cin >> oldPin;

        if (oldPin != pin) {
            cout << "Incorrect PIN.\n";
            return;
        }

        cout << "Enter new 4-digit PIN: ";
        cin >> newPin;

        if (newPin < 1000 || newPin > 9999) {
            cout << "PIN must contain 4 digits.\n";
            return;
        }

        cout << "Confirm new PIN: ";
        cin >> confirmPin;

        if (newPin != confirmPin) {
            cout << "PINs do not match.\n";
            return;
        }

        pin = newPin;
        cout << "PIN changed successfully!\n";
    }

    void menu() {
        int choice;

        do {
            cout << "\n====================================\n";
            cout << "           ATM SIMULATOR\n";
            cout << "====================================\n";
            cout << "1. Check Balance\n";
            cout << "2. Deposit Money\n";
            cout << "3. Withdraw Money\n";
            cout << "4. Transfer Money\n";
            cout << "5. Account Information\n";
            cout << "6. Transaction History\n";
            cout << "7. Change PIN\n";
            cout << "8. Exit\n";
            cout << "====================================\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    checkBalance();
                    break;

                case 2:
                    deposit();
                    break;

                case 3:
                    withdraw();
                    break;

                case 4:
                    transfer();
                    break;

                case 5:
                    accountInfo();
                    break;

                case 6:
                    transactionHistory();
                    break;

                case 7:
                    changePin();
                    break;

                case 8:
                    cout << "\nThank you for using the ATM!\n";
                    cout << "Have a nice day!\n";
                    break;

                default:
                    cout << "Invalid choice. Please try again.\n";
            }

        } while (choice != 8);
    }
};

int main() {
    ATM user(
        "Afan Ahmed Memon",
        "PK001234567",
        1234,
        100000.00
    );

    cout << "====================================\n";
    cout << "       WELCOME TO ATM SIMULATOR\n";
    cout << "       HEX SOFTWARE - PROJECT 01\n";
    cout << "====================================\n\n";

    if (user.login()) {
        user.menu();
    }

    return 0;
}
