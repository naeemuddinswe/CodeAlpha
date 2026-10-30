#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Function for user registration
void registerUser()
{
    string username, password;
    string savedUsername, savedPassword;

    cout << "\n===== USER REGISTRATION =====\n";

    cout << "Enter Username: ";
    cin >> username;

    cout << "Enter Password: ";
    cin >> password;

    // Check empty input
    if (username.empty() || password.empty())
    {
        cout << "Username and Password cannot be empty!\n";
        return;
    }

    // Check for duplicate username
    ifstream readFile("users.txt");

    while (readFile >> savedUsername >> savedPassword)
    {
        if (savedUsername == username)
        {
            cout << "Username already exists! Try another.\n";
            readFile.close();
            return;
        }
    }

    readFile.close();

    // Save new user credentials
    ofstream writeFile("users.txt", ios::app);

    writeFile << username << " " << password << endl;

    writeFile.close();

    cout << "\nRegistration Successful!\n";
}

// Function for user login
void loginUser()
{
    string username, password;
    string savedUsername, savedPassword;
    bool found = false;

    cout << "\n===== USER LOGIN =====\n";

    cout << "Enter Username: ";
    cin >> username;

    cout << "Enter Password: ";
    cin >> password;

    // Read credentials from file
    ifstream readFile("users.txt");

    while (readFile >> savedUsername >> savedPassword)
    {
        if (savedUsername == username &&
            savedPassword == password)
        {
            found = true;
            break;
        }
    }

    readFile.close();

    // Verify login
    if (found)
    {
        cout << "\nLogin Successful!\n";
        cout << "Welcome, " << username << "!\n";
    }
    else
    {
        cout << "\nInvalid Username or Password!\n";
    }
}

// Main function
int main()
{
    int choice;

    do
    {
        cout << "\n============================\n";
        cout << " LOGIN AND REGISTRATION SYSTEM\n";
        cout << "============================\n";

        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";

        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                registerUser();
                break;

            case 2:
                loginUser();
                break;

            case 3:
                cout << "\nThank you for using the system!\n";
                break;

            default:
                cout << "\nInvalid Choice! Try Again.\n";
        }

    } while (choice != 3);

    return 0;
}


