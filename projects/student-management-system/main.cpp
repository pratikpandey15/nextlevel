#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>   // for remove & rename

using namespace std;

class Student {
public:
    int roll;
    string name;
    float marks;

    void input() {
        cout << "Enter Roll Number: ";
        cin >> roll;
        cin.ignore();

        cout << "Enter Name: ";
        getline(cin, name);

        cout << "Enter Marks: ";
        cin >> marks;
    }

    void display() const {
        cout << "Roll: " << roll
             << " | Name: " << name
             << " | Marks: " << marks << endl;
    }
};

void addStudent() {
    Student s;
    s.input();

    ofstream file("students.txt", ios::app);
    if (!file) {
        cout << "Error opening file!\n";
        return;
    }

    file << s.roll << endl;
    file << s.name << endl;
    file << s.marks << endl;

    file.close();
    cout << "Student Added Successfully!\n";
}

void displayStudents() {
    ifstream file("students.txt");
    if (!file) {
        cout << "No records found!\n";
        return;
    }

    Student s;
    cout << "\n---- Student Records ----\n";

    while (file >> s.roll) {
        file.ignore();
        getline(file, s.name);
        file >> s.marks;
        file.ignore();

        s.display();
    }

    file.close();
}

void searchStudent() {
    int searchRoll;
    cout << "Enter Roll Number to Search: ";
    cin >> searchRoll;

    ifstream file("students.txt");
    if (!file) {
        cout << "No records found!\n";
        return;
    }

    Student s;
    bool found = false;

    while (file >> s.roll) {
        file.ignore();
        getline(file, s.name);
        file >> s.marks;
        file.ignore();

        if (s.roll == searchRoll) {
            s.display();
            found = true;
            break;
        }
    }

    if (!found)
        cout << "Student Not Found!\n";

    file.close();
}

void deleteStudent() {
    int deleteRoll;
    cout << "Enter Roll Number to Delete: ";
    cin >> deleteRoll;

    ifstream file("students.txt");
    ofstream temp("temp.txt");

    if (!file || !temp) {
        cout << "Error handling files!\n";
        return;
    }

    Student s;
    bool found = false;

    while (file >> s.roll) {
        file.ignore();
        getline(file, s.name);
        file >> s.marks;
        file.ignore();

        if (s.roll != deleteRoll) {
            temp << s.roll << endl;
            temp << s.name << endl;
            temp << s.marks << endl;
        } else {
            found = true;
        }
    }

    file.close();
    temp.close();

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (found)
        cout << "Student Deleted Successfully!\n";
    else
        cout << "Student Not Found!\n";
}

int main() {
    int choice;

    do {
        cout << "\n--- Student Management System ---\n";
        cout << "1. Add Student\n";
        cout << "2. Display Students\n";
        cout << "3. Search Student\n";
        cout << "4. Delete Student\n";
        cout << "5. Exit\n";
        cout << "Enter Choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: deleteStudent(); break;
            case 5: cout << "Exiting...\n"; break;
            default: cout << "Invalid Choice!\n";
        }

    } while (choice != 5);

    return 0;
}
