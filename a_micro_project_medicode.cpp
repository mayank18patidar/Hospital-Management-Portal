#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <limits>

using namespace std;

struct Patient {
    int id = 0;
    string name;
    int age = 0;
    string disease;
};

int getValidInt(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
        cout << "Invalid input. Please enter a number.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

bool login() {
    string username, password;

    cout << "\n===== Login =====\n";
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    if (username == "medicode" && password == "1234") {
        cout << "\nLogin Successful!\n";
        return true;
    }

    cout << "\nInvalid Username or Password!\n";
    return false;
}

void registerPatient() {
    Patient p;
    ofstream file("patients.txt", ios::app);

    if (!file) {
        cout << "\nError opening file!\n";
        return;
    }

    cout << "\n===== Patient Registration =====\n";

    p.id = getValidInt("Patient ID: ");

    cout << "Patient Name: ";
    getline(cin, p.name);

    p.age = getValidInt("Age: ");

    cout << "Disease: ";
    getline(cin, p.disease);

    file << p.id << "|"
         << p.name << "|"
         << p.age << "|"
         << p.disease << "\n";

    file.close();

    cout << "\nPatient Registered Successfully!\n";
}

void viewPatients() {
    ifstream file("patients.txt");

    if (!file) {
        cout << "\nNo records found.\n";
        return;
    }

    string line;
    bool hasRecords = false;

    cout << "\n===== Patient Records =====\n";

    while (getline(file, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string id, name, age, disease;

        if (getline(ss, id, '|') &&
            getline(ss, name, '|') &&
            getline(ss, age, '|') &&
            getline(ss, disease)) {
            
            hasRecords = true;
            cout << "ID: " << id 
                 << " | Name: " << name 
                 << " | Age: " << age 
                 << " | Disease: " << disease << "\n";
        }
    }

    if (!hasRecords) {
        cout << "No valid patient records found.\n";
    }

    file.close();
}

void generateBill() {
    int id;
    float doctorFee, medicineFee, testFee, total;

    cout << "\n===== Billing =====\n";

    id = getValidInt("Patient ID: ");

    cout << "Doctor Fee: ";
    cin >> doctorFee;

    cout << "Medicine Charges: ";
    cin >> medicineFee;

    cout << "Test Charges: ";
    cin >> testFee;

    total = doctorFee + medicineFee + testFee;

    cout << "\n------ Bill ------\n";
    cout << "Patient ID : " << id << "\n";
    cout << "Doctor Fee : " << doctorFee << "\n";
    cout << "Medicine   : " << medicineFee << "\n";
    cout << "Tests      : " << testFee << "\n";
    cout << "------------------\n";
    cout << "Total Bill : " << total << "\n";
}

int main() {
    if (!login()) {
        return 0;
    }

    int choice;

    do {
        cout << "\n============================\n";
        cout << " Hospital Management System\n";
        cout << "============================\n";
        cout << "1. Register Patient\n";
        cout << "2. View Patients\n";
        cout << "3. Generate Bill\n";
        cout << "4. Exit\n";

        choice = getValidInt("Enter Choice: ");

        switch (choice) {
        case 1:
            registerPatient();
            break;

        case 2:
            viewPatients();
            break;

        case 3:
            generateBill();
            break;

        case 4:
            cout << "\nThank You!\n";
            break;

        default:
            cout << "\nInvalid Choice!\n";
        }

    } while (choice != 4);

    return 0;
}