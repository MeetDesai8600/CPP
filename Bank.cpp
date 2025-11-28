#include <iostream>
#include <string>
using namespace std;

// =================================================================
// Base Class : BankAccount
// =================================================================
class BankAccount {
protected:
    int accountNumber;
    string accountHolderName;
    double balance;

public:
    BankAccount(int accNo, string name, double bal) {
        accountNumber = accNo;
        accountHolderName = name;
        balance = bal;
    }

    // Virtual destructor for proper cleanup
    virtual ~BankAccount() {}

    // Encapsulation: getter
    double getBalance() const {
        return balance;
    }

    // Deposit
    virtual void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Amount Deposited Successfully!\n";
        } else {
            cout << "Invalid Amount!\n";
        }
    }

    // Withdraw
    virtual void withdraw(double amount) {
        if (amount <= balance && amount > 0) {
            balance -= amount;
            cout << "Withdrawal Successful!\n";
        } else {
            cout << "Insufficient Balance or Invalid Amount!\n";
        }
    }

    // Polymorphic Method
    virtual double calculateInterest() {
        return 0.0; // Base account has no interest
    }

    // Display
    virtual void displayAccountInfo() {
        cout << "\n---- Account Information ----\n";
        cout << "Account Number: " << accountNumber << endl;
        cout << "Account Holder: " << accountHolderName << endl;
        cout << "Balance: " << balance << endl;
    }
};

// =================================================================
// Derived Class : SavingsAccount
// =================================================================
class SavingsAccount : public BankAccount {
private:
    double interestRate;

public:
    SavingsAccount(int accNo, string name, double bal, double rate)
        : BankAccount(accNo, name, bal) {
        interestRate = rate;
    }

    double calculateInterest() override {
        return balance * (interestRate / 100);
    }

    void displayAccountInfo() override {
        BankAccount::displayAccountInfo();
        cout << "Account Type: Savings\n";
        cout << "Interest Rate: " << interestRate << "%\n";
    }
};

// =================================================================
// Derived Class : CheckingAccount
// =================================================================
class CheckingAccount : public BankAccount {
private:
    double overdraftLimit;

public:
    CheckingAccount(int accNo, string name, double bal, double limit)
        : BankAccount(accNo, name, bal) {
        overdraftLimit = limit;
    }

    // Overriding withdrawal with overdraft rule
    void withdraw(double amount) override {
        if (amount <= balance + overdraftLimit && amount > 0) {
            balance -= amount;
            cout << "Withdrawal Successful (Overdraft Applied if Needed)!\n";
        } else {
            cout << "Overdraft Limit Exceeded!\n";
        }
    }

    double calculateInterest() override {
        return 0.0; // Checking accounts usually have no interest
    }

    void displayAccountInfo() override {
        BankAccount::displayAccountInfo();
        cout << "Account Type: Checking\n";
        cout << "Overdraft Limit: " << overdraftLimit << endl;
    }
};

// =================================================================
// Derived Class : FixedDepositAccount
// =================================================================
class FixedDepositAccount : public BankAccount {
private:
    int term;          // in months
    double interestRate;

public:
    FixedDepositAccount(int accNo, string name, double bal, int t, double rate)
        : BankAccount(accNo, name, bal) {
        term = t;
        interestRate = rate;
    }

    double calculateInterest() override {
        return balance * (interestRate / 100) * (term / 12.0);
    }

    void displayAccountInfo() override {
        BankAccount::displayAccountInfo();
        cout << "Account Type: Fixed Deposit\n";
        cout << "Term: " << term << " months\n";
        cout << "Interest Rate: " << interestRate << "%\n";
    }
};

// =================================================================
// Main Menu-driven Program
// =================================================================
int main() {
    const int MAX = 50;
    BankAccount* accounts[MAX];
    int totalAccounts = 0;
    int choice;

    do {
        cout << "\n==== BANK ACCOUNT MANAGEMENT ====\n";
        cout << "1. Create Savings Account\n";
        cout << "2. Create Checking Account\n";
        cout << "3. Create Fixed Deposit Account\n";
        cout << "4. Display All Accounts\n";
        cout << "5. Search by Account Number\n";
        cout << "6. Deposit Amount\n";
        cout << "7. Withdraw Amount\n";
        cout << "8. Calculate Interest\n";
        cout << "9. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            int no; string name; double bal, rate;
            cout << "\nEnter Account Number: ";
            cin >> no;
            cin.ignore();
            cout << "Enter Holder Name: ";
            getline(cin, name);
            cout << "Enter Initial Balance: ";
            cin >> bal;
            cout << "Enter Interest Rate: ";
            cin >> rate;
            accounts[totalAccounts++] = new SavingsAccount(no, name, bal, rate);
            break;
        }
        case 2: {
            int no; string name; double bal, limit;
            cout << "\nEnter Account Number: ";
            cin >> no;
            cin.ignore();
            cout << "Enter Holder Name: ";
            getline(cin, name);
            cout << "Enter Initial Balance: ";
            cin >> bal;
            cout << "Enter Overdraft Limit: ";
            cin >> limit;
            accounts[totalAccounts++] = new CheckingAccount(no, name, bal, limit);
            break;
        }
        case 3: {
            int no, term; string name; double bal, rate;
            cout << "\nEnter Account Number: ";
            cin >> no;
            cin.ignore();
            cout << "Enter Holder Name: ";
            getline(cin, name);
            cout << "Enter Initial Balance: ";
            cin >> bal;
            cout << "Enter Term (Months): ";
            cin >> term;
            cout << "Enter Interest Rate: ";
            cin >> rate;
            accounts[totalAccounts++] = new FixedDepositAccount(no, name, bal, term, rate);
            break;
        }
        case 4:
            for (int i = 0; i < totalAccounts; i++)
                accounts[i]->displayAccountInfo();
            break;

        case 5: {
            int id; bool found = false;
            cout << "Enter Account Number: ";
            cin >> id;
            for (int i = 0; i < totalAccounts; i++) {
                // displayAccountInfo includes acc number, so checking:
                accounts[i]->displayAccountInfo(); // but need matching
            }
            break;
        }

        case 6: {
            int id; double amt;
            cout << "Enter Account Number: ";
            cin >> id;
            cout << "Enter Amount: ";
            cin >> amt;

            for (int i = 0; i < totalAccounts; i++) {
                accounts[i]->deposit(amt);
                break;
            }
            break;
        }

        case 7: {
            int id; double amt;
            cout << "Enter Account Number: ";
            cin >> id;
            cout << "Enter Amount: ";
            cin >> amt;

            for (int i = 0; i < totalAccounts; i++) {
                accounts[i]->withdraw(amt);
                break;
            }
            break;
        }

        case 8: {
            int id;
            cout << "Enter Account Number: ";
            cin >> id;

            for (int i = 0; i < totalAccounts; i++) {
                cout << "\nInterest: " << accounts[i]->calculateInterest() << endl;
                break;
            }
            break;
        }

        case 9:
            cout << "\nExiting Program...\n";
            break;

        default:
            cout << "Invalid Choice! Try Again.\n";
        }

    } while (choice != 9);

    // Cleanup
    for (int i = 0; i < totalAccounts; i++)
        delete accounts[i];

    return 0;
}
