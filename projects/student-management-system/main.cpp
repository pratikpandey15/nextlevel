#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class Student {
public:
    int roll;
    string name;
    float marks;

    void input() {
        cout << "Enter Roll Number: ";
        cin >> roll;
        cout << "Enter Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter Marks: ";
        cin >> marks;
    }

    void display() {
        cout << "Roll: " << roll 
             << " | Name: " << name 
             << " | Marks: " << marks << endl;
    }
};

void addStudent() {
    Student s;
    s.input();

    ofstream file("students.txt", ios::app);
    file << s.roll << " " << s.name << " " << s.marks << endl;
    file.close();

    cout << "Student Added Successfully!\n";
}

void displayStudents() {
    ifstream file("students.txt");
    Student s;

    while (file >> s.roll >> s.name >> s.marks) {
        s.display();
    }
    file.close();
}

void searchStudent() {
    int roll;
    cout << "Enter Roll Number to Search: ";
    cin >> roll;

    ifstream file("students.txt");
    Student s;
    bool found = false;

    while (file >> s.roll >> s.name >> s.marks) {
        if (s.roll == roll) {
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
    int roll;
    cout << "Enter Roll Number to Delete: ";
    cin >> roll;

    ifstream file("students.txt");
    ofstream temp("temp.txt");

    Student s;
    bool found = false;

    while (file >> s.roll >> s.name >> s.marks) {
        if (s.roll != roll) {
            temp << s.roll << " " << s.name << " " << s.marks << endl;
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
