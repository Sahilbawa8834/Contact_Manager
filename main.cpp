#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

// It define what contact would be a name with a phone number and an email 
class Contact {
public:
    string name;
    string phone;
    string email;

    // Constructor
    Contact(string n, string p, string e) {
        name = n;
        phone = p;
        email = e;
    }

    //   TO display contact info
    void display() {
        cout << "Name: " << name << endl;
        cout << "Phone: " << phone << endl;
        cout << "Email: " << email << endl << endl;
    }
};

// Function to add a new contact
void addContact(vector<Contact> &contacts) {
    string name, phone, email;

    cout << "Enter name: ";
    getline(cin >> ws, name);  // ws clears leftover newline
    cout << "Enter phone: ";
    getline(cin, phone);
    cout << "Enter email: ";
    getline(cin, email);

    Contact newContact(name, phone, email);
    contacts.push_back(newContact);
    cout << "Contact added successfully!\n";
}

// This is the function to view all contacts
void viewContacts(const vector<Contact> &contacts) {
    if (contacts.empty()) {
        cout << "No contacts available.\n";
        return;
    }

    cout << "\n--- Contact List ---\n";
    for (int i = 0; i < contacts.size(); i++) {
        cout << "Contact " << (i + 1) << ":\n";
        contacts[i].display();
    }
}

// This is the function to delete a contact by number
void deleteContact(vector<Contact> &contacts) {
    if (contacts.empty()) {
        cout << "No contacts to delete.\n";
        return;
    }

    int index;
    cout << "Enter contact number to delete (1 to " << contacts.size() << "): ";
    cin >> index;

    if (index < 1 || index > contacts.size()) {
        cout << "Invalid number.\n";
        return;
    }

    contacts.erase(contacts.begin() + index - 1);
    cout << "Contact deleted.\n";
}

// This is to save contacts to a file
void saveContacts(const vector<Contact> &contacts) {
    ofstream outFile("contacts.txt");

    for (const auto &c : contacts) {
        outFile << c.name << "," << c.phone << "," << c.email << endl;
    }

    outFile.close();
    cout << "Contacts saved to file.\n";
}

//  for loading contacts from a file
void loadContacts(vector<Contact> &contacts) {
    ifstream inFile("contacts.txt");
    string line;

    while (getline(inFile, line)) {
        size_t pos1 = line.find(',');
        size_t pos2 = line.find(',', pos1 + 1);

        if (pos1 == string::npos || pos2 == string::npos) continue;

        string name = line.substr(0, pos1);
        string phone = line.substr(pos1 + 1, pos2 - pos1 - 1);
        string email = line.substr(pos2 + 1);

        contacts.push_back(Contact(name, phone, email));
    }

    inFile.close();
}

// Main menu
int main() {
    vector<Contact> contacts;
    loadContacts(contacts);

    int choice;
    while (true) {
        cout << "\n<---- Contact Manager Menu ---->\n";
        cout << "1. Add Contact\n";
        cout << "2. View Contacts\n";
        cout << "3. Delete Contact\n";
        cout << "4. Exit\n";
        cout << "Enter your choice ";
        cin >> choice;

        switch (choice) {
            case 1:
                addContact(contacts);
                break;
            case 2:
                viewContacts(contacts);
                break;
            case 3:
                deleteContact(contacts);
                break;
            case 4:
                saveContacts(contacts);
                cout << "Exiting and saving contacts \n";
                return 0;
            default:
                cout << "Invalid choice. Try again \n";
        }
    }
}