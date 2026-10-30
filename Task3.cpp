
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include <sstream>
#include <iomanip>

using namespace std;

// =================================
// TRANSACTION CLASS
// =================================

class Transaction
{
public:
    int transactionID;
    string type;
    double amount;
    string date;

    Transaction()
    {
        transactionID = 0;
        amount = 0;
    }

    Transaction(int id, string t, double a)
    {
        transactionID = id;
        type = t;
        amount = a;

        time_t now = time(0);
        date = ctime(&now);

        if (!date.empty() && date[date.length() - 1] == '\n')
            date.erase(date.length() - 1);
    }

    void displayTransaction()
    {
        cout << "\nTransaction ID: " << transactionID << endl;
        cout << "Type: " << type << endl;
        cout << "Amount: Rs. " << amount << endl;
        cout << "Date: " << date << endl;
        cout << "-------------------------\n";
    }
};

// =================================
// CUSTOMER CLASS
// =================================

class Customer
{
public:
    int customerID;
    string name;
    string phone;

    Customer()
    {
        customerID = 0;
    }

    Customer(int id, string n, string p)
    {
        customerID = id;
        name = n;
        phone = p;
    }

    void displayCustomer()
    {
        cout << "\nCustomer ID: " << customerID << endl;
        cout << "Name: " << name << endl;
        cout << "Phone: " << phone << endl;
    }
};

// =================================
// ACCOUNT CLASS
// =================================

class Account
{
public:
    int accountNumber;
    double balance;
    Customer customer;
    vector<Transaction> transactions;

    Account()
    {
        accountNumber = 0;
        balance = 0;
    }

    Account(int accNo, double bal, Customer c)
    {
        accountNumber = accNo;
        balance = bal;
        customer = c;
    }

    // Deposit Money
    bool deposit(double amount, int &counter)
    {
        if (amount <= 0)
        {
            cout << "Invalid deposit amount!\n";
            return false;
        }

        balance += amount;

        transactions.push_back(
            Transaction(counter++, "Deposit", amount)
        );

        cout << "\nDeposit Successful!\n";
        cout << "New Balance: Rs. " << balance << endl;

        return true;
    }

    // Withdraw Money
    bool withdraw(double amount, int &counter)
    {
        if (amount <= 0)
        {
            cout << "Invalid withdrawal amount!\n";
            return false;
        }

        if (amount > balance)
        {
            cout << "Insufficient Balance!\n";
            return false;
        }

        balance -= amount;

        transactions.push_back(
            Transaction(counter++, "Withdrawal", amount)
        );

        cout << "\nWithdrawal Successful!\n";
        cout << "New Balance: Rs. " << balance << endl;

        return true;
    }

    // Transfer Money
    bool transfer(Account &receiver, double amount, int &counter)
    {
        if (amount <= 0)
        {
            cout << "Invalid transfer amount!\n";
            return false;
        }

        if (amount > balance)
        {
            cout << "Insufficient Balance!\n";
            return false;
        }

        balance -= amount;
        receiver.balance += amount;

        transactions.push_back(
            Transaction(counter++, "Transfer Sent", amount)
        );

        receiver.transactions.push_back(
            Transaction(counter++, "Transfer Received", amount)
        );

        cout << "\nTransfer Successful!\n";
        cout << "Remaining Balance: Rs. " << balance << endl;

        return true;
    }

    // Display Account
    void displayAccount()
    {
        cout << "\n===== ACCOUNT INFORMATION =====\n";

        customer.displayCustomer();

        cout << "Account Number: " << accountNumber << endl;
        cout << "Balance: Rs. " << balance << endl;
    }

    // Display Transaction History
    void displayHistory()
    {
        cout << "\n===== TRANSACTION HISTORY =====\n";

        if (transactions.empty())
        {
            cout << "No transactions found.\n";
            return;
        }

        for (size_t i = 0; i < transactions.size(); i++)
        {
            transactions[i].displayTransaction();
        }
    }
};

// =================================
// INPUT FUNCTIONS
// =================================

int getInteger(string message)
{
    string input;
    int value;
    char extra;

    while (true)
    {
        cout << message;
        getline(cin, input);

        stringstream ss(input);

        if ((ss >> value) && !(ss >> extra))
            return value;

        cout << "Invalid input! Enter a number.\n";
    }
}

double getAmount(string message)
{
    string input;
    double value;
    char extra;

    while (true)
    {
        cout << message;
        getline(cin, input);

        stringstream ss(input);

        if ((ss >> value) && !(ss >> extra))
        {
            if (value > 0 && value < 1e15)
                return value;
        }

        cout << "Invalid amount! Try again.\n";
    }
}

// =================================
// FIND ACCOUNT
// =================================

int findAccount(vector<Account> &accounts, int accNo)
{
    for (size_t i = 0; i < accounts.size(); i++)
    {
        if (accounts[i].accountNumber == accNo)
            return (int)i;
    }

    return -1;
}

// =================================
// SAVE ACCOUNT DATA
// =================================

void saveAccounts(vector<Account> &accounts)
{
    ofstream file("accounts.txt");

    if (!file)
    {
        cout << "Error saving accounts!\n";
        return;
    }

    file << setprecision(15);

    for (size_t i = 0; i < accounts.size(); i++)
    {
        file << accounts[i].accountNumber << "|"
             << accounts[i].balance << "|"
             << accounts[i].customer.customerID << "|"
             << accounts[i].customer.name << "|"
             << accounts[i].customer.phone << endl;
    }

    file.close();
}

// =================================
// SAVE TRANSACTIONS
// =================================

void saveTransactions(vector<Account> &accounts)
{
    ofstream file("transactions.txt");

    if (!file)
    {
        cout << "Error saving transactions!\n";
        return;
    }

    file << setprecision(15);

    for (size_t i = 0; i < accounts.size(); i++)
    {
        for (size_t j = 0; j < accounts[i].transactions.size(); j++)
        {
            Transaction t = accounts[i].transactions[j];

            file << accounts[i].accountNumber << "|"
                 << t.transactionID << "|"
                 << t.type << "|"
                 << t.amount << "|"
                 << t.date << endl;
        }
    }

    file.close();
}

// =================================
// LOAD ACCOUNT DATA
// =================================

void loadAccounts(vector<Account> &accounts,
                  int &customerCounter,
                  int &accountCounter)
{
    ifstream file("accounts.txt");

    if (!file)
        return;

    string line;

    while (getline(file, line))
    {
        stringstream ss(line);

        string acc, bal, id, name, phone;

        if (!getline(ss, acc, '|')) continue;
        if (!getline(ss, bal, '|')) continue;
        if (!getline(ss, id, '|')) continue;
        if (!getline(ss, name, '|')) continue;
        if (!getline(ss, phone)) continue;

        stringstream a(acc), b(bal), c(id);

        Account temp;
        a >> temp.accountNumber;
        b >> temp.balance;
        c >> temp.customer.customerID;

        temp.customer.name = name;
        temp.customer.phone = phone;

        if (a.fail() || b.fail() || c.fail())
            continue;

        accounts.push_back(temp);

        if (temp.customer.customerID >= customerCounter)
            customerCounter = temp.customer.customerID + 1;

        if (temp.accountNumber >= accountCounter)
            accountCounter = temp.accountNumber + 1;
    }

    file.close();
}

// =================================
// LOAD TRANSACTIONS
// =================================

void loadTransactions(vector<Account> &accounts,
                      int &transactionCounter)
{
    ifstream file("transactions.txt");

    if (!file)
        return;

    string line;

    while (getline(file, line))
    {
        stringstream ss(line);

        string acc, id, type, amount, date;

        if (!getline(ss, acc, '|')) continue;
        if (!getline(ss, id, '|')) continue;
        if (!getline(ss, type, '|')) continue;
        if (!getline(ss, amount, '|')) continue;
        if (!getline(ss, date)) continue;

        int accNo;
        Transaction t;

        stringstream a(acc), b(id), c(amount);

        a >> accNo;
        b >> t.transactionID;
        c >> t.amount;

        if (a.fail() || b.fail() || c.fail())
            continue;

        t.type = type;
        t.date = date;

        int index = findAccount(accounts, accNo);

        if (index != -1)
        {
            accounts[index].transactions.push_back(t);
        }

        if (t.transactionID >= transactionCounter)
            transactionCounter = t.transactionID + 1;
    }

    file.close();
}

// =================================
// MAIN FUNCTION
// =================================

int main()
{
    vector<Account> accounts;

    int customerCounter = 1;
    int accountCounter = 1001;
    int transactionCounter = 1;

    // Load saved data
    loadAccounts(accounts, customerCounter, accountCounter);

    loadTransactions(accounts, transactionCounter);

    int choice;

    do
    {
        cout << "\n================================\n";
        cout << "          BANKING SYSTEM\n";
        cout << "================================\n";

        cout << "1. Create Customer and Account\n";
        cout << "2. Deposit Money\n";
        cout << "3. Withdraw Money\n";
        cout << "4. Transfer Money\n";
        cout << "5. Check Account Information\n";
        cout << "6. View Transaction History\n";
        cout << "7. Display All Accounts\n";
        cout << "8. Exit\n";

        choice = getInteger("\nEnter Your Choice: ");

        int accNo, receiverNo;
        int index;
        double amount;

        switch (choice)
        {
            // CREATE ACCOUNT
            case 1:
            {
                string name, phone;

                cout << "\nEnter Customer Name: ";
                getline(cin, name);

                cout << "Enter Phone Number: ";
                getline(cin, phone);

                if (name.empty() || phone.empty() ||
                    name.find('|') != string::npos ||
                    phone.find('|') != string::npos)
                {
                    cout << "Invalid customer information!\n";
                    break;
                }

                Customer c(customerCounter++, name, phone);

                Account a(accountCounter++, 0, c);

                accounts.push_back(a);

                saveAccounts(accounts);

                cout << "\nAccount Created Successfully!\n";
                cout << "Customer ID: " << c.customerID << endl;
                cout << "Account Number: " << a.accountNumber << endl;

                break;
            }

            // DEPOSIT
            case 2:
            {
                accNo = getInteger("Enter Account Number: ");

                index = findAccount(accounts, accNo);

                if (index == -1)
                {
                    cout << "Account Not Found!\n";
                    break;
                }

                amount = getAmount("Enter Deposit Amount: ");

                if (accounts[index].deposit(amount, transactionCounter))
                {
                    saveAccounts(accounts);
                    saveTransactions(accounts);
                }

                break;
            }

            // WITHDRAW
            case 3:
            {
                accNo = getInteger("Enter Account Number: ");

                index = findAccount(accounts, accNo);

                if (index == -1)
                {
                    cout << "Account Not Found!\n";
                    break;
                }

                amount = getAmount("Enter Withdrawal Amount: ");

                if (accounts[index].withdraw(amount, transactionCounter))
                {
                    saveAccounts(accounts);
                    saveTransactions(accounts);
                }

                break;
            }

            // TRANSFER
            case 4:
            {
                accNo = getInteger("Enter Sender Account Number: ");

                receiverNo = getInteger("Enter Receiver Account Number: ");

                int senderIndex = findAccount(accounts, accNo);
                int receiverIndex = findAccount(accounts, receiverNo);

                if (senderIndex == -1 || receiverIndex == -1)
                {
                    cout << "One or both accounts not found!\n";
                }
                else if (senderIndex == receiverIndex)
                {
                    cout << "Cannot transfer to the same account!\n";
                }
                else
                {
                    amount = getAmount("Enter Transfer Amount: ");

                    if (accounts[senderIndex].transfer(
                        accounts[receiverIndex],
                        amount,
                        transactionCounter))
                    {
                        saveAccounts(accounts);
                        saveTransactions(accounts);
                    }
                }

                break;
            }

            // ACCOUNT INFORMATION
            case 5:
            {
                accNo = getInteger("Enter Account Number: ");

                index = findAccount(accounts, accNo);

                if (index == -1)
                    cout << "Account Not Found!\n";
                else
                    accounts[index].displayAccount();

                break;
            }

            // TRANSACTION HISTORY
            case 6:
            {
                accNo = getInteger("Enter Account Number: ");

                index = findAccount(accounts, accNo);

                if (index == -1)
                    cout << "Account Not Found!\n";
                else
                    accounts[index].displayHistory();

                break;
            }

            // DISPLAY ALL ACCOUNTS
            case 7:
            {
                cout << "\n===== ALL BANK ACCOUNTS =====\n";

                if (accounts.empty())
                {
                    cout << "No accounts available.\n";
                }

                for (size_t i = 0; i < accounts.size(); i++)
                {
                    accounts[i].displayAccount();
                }

                break;
            }

            // EXIT
            case 8:
            {
                saveAccounts(accounts);
                saveTransactions(accounts);

                cout << "\nData Saved Successfully!\n";
                cout << "Thank You for Using Our Banking System!\n";

                break;
            }

            default:
            {
                cout << "Invalid Choice! Try Again.\n";
            }
        }

    } while (choice != 8);

    return 0;
}

