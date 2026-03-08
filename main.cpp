#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

class Account {
public:
    int accountNumber;
    string name;
    double balance;

    Account() {}

    Account(int accNo, string accName, double bal) {
        accountNumber = accNo;
        name = accName;
        balance = bal;
    }

    void display() {
        cout << "Account Number: " << accountNumber << endl;
        cout << "Name: " << name << endl;
        cout << "Balance: " << balance << endl;
    }
};

vector<Account> accounts;

void saveAccounts() {
    ofstream file("accounts.txt");

    for (auto &acc : accounts) {
        file << acc.accountNumber << " "
             << acc.name << " "
             << acc.balance << endl;
    }

    file.close();
}

void loadAccounts() {
    ifstream file("accounts.txt");

    if (!file) return;

    Account acc;

    while (file >> acc.accountNumber >> acc.name >> acc.balance) {
        accounts.push_back(acc);
    }

    file.close();
}

Account* findAccount(int accNo) {
    for (auto &acc : accounts) {
        if (acc.accountNumber == accNo) {
            return &acc;
        }
    }
    return nullptr;
}

void createAccount() {
    int accNo;
    string name;
    double balance;

    cout << "Enter account number: ";
    cin >> accNo;

    cout << "Enter name: ";
    cin >> name;

    cout << "Enter initial balance: ";
    cin >> balance;

    accounts.push_back(Account(accNo, name, balance));

    saveAccounts();

    cout << "Account created successfully.\n";
}

void deposit() {
    int accNo;
    double amount;

    cout << "Enter account number: ";
    cin >> accNo;

    Account* acc = findAccount(accNo);

    if (acc) {
        cout << "Enter amount: ";
        cin >> amount;

        acc->balance += amount;

        saveAccounts();

        cout << "Deposit successful.\n";
    } else {
        cout << "Account not found.\n";
    }
}

void withdraw() {
    int accNo;
    double amount;

    cout << "Enter account number: ";
    cin >> accNo;

    Account* acc = findAccount(accNo);

    if (acc) {
        cout << "Enter amount: ";
        cin >> amount;

        if (amount > acc->balance) {
            cout << "Insufficient balance.\n";
        } else {
            acc->balance -= amount;

            saveAccounts();

            cout << "Withdrawal successful.\n";
        }
    } else {
        cout << "Account not found.\n";
    }
}

void transfer() {
    int fromAcc, toAcc;
    double amount;

    cout << "Enter sender account number: ";
    cin >> fromAcc;

    cout << "Enter receiver account number: ";
    cin >> toAcc;

    cout << "Enter amount: ";
    cin >> amount;

    Account* sender = findAccount(fromAcc);
    Account* receiver = findAccount(toAcc);

    if (!sender || !receiver) {
        cout << "One of the accounts was not found.\n";
        return;
    }

    if (sender->balance < amount) {
        cout << "Insufficient balance.\n";
        return;
    }

    sender->balance -= amount;
    receiver->balance += amount;

    saveAccounts();

    cout << "Transfer successful.\n";
}

void viewAccount() {
    int accNo;

    cout << "Enter account number: ";
    cin >> accNo;

    Account* acc = findAccount(accNo);

    if (acc) {
        acc->display();
    } else {
        cout << "Account not found.\n";
    }
}

int main() {

    loadAccounts();

    int choice;

    while (true) {

        cout << "\n=== Banking System ===\n";
        cout << "1. Create Account\n";
        cout << "2. Deposit\n";
        cout << "3. Withdraw\n";
        cout << "4. Transfer\n";
        cout << "5. View Account\n";
        cout << "6. Exit\n";

        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

            case 1:
                createAccount();
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
                viewAccount();
                break;

            case 6:
                cout << "Goodbye.\n";
                return 0;

            default:
                cout << "Invalid option.\n";
        }
    }
}