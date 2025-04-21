#include <iostream>
#include <string>

using namespace std;

struct Student {
    string name;
    int roll;
    Student* next;

    // Constructor
    Student(string n, int r){
    	name = n;
    	roll = r;
    	next = NULL;
	} 
};

class StudentList {
private:
    Student* head;

public:
    // Constructor
    StudentList() {
    	head = NULL;
	} 

    // Destructor
    ~StudentList() {
        while (head) {
            Student* temp = head;
            head = head->next;
            delete temp;
        }
    }

    // Insert a student in sorted order
    void insertStudent(string name, int roll) {
        Student* newStudent = new Student(name, roll);
        
        if (!head || roll < head->roll) {  // Insert at head
            newStudent->next = head;
            head = newStudent;
            return;
        }

        // Find position to insert
        Student* current = head;
        while (current->next && current->next->roll < roll)
            current = current->next;

        newStudent->next = current->next;
        current->next = newStudent;
    }

    // Delete a student by roll number
    void deleteStudent(int roll) {
        if (!head) return;

        if (head->roll == roll) {  // If head is to be deleted
            Student* temp = head;
            head = head->next;
            delete temp;
            return;
        }

        Student* current = head;
        while (current->next && current->next->roll != roll)
            current = current->next;

        if (current->next) {
            Student* temp = current->next;
            current->next = temp->next;
            delete temp;
        }
    }

    // Display student records
    void displayStudents() {
        Student* current = head;
        while (current) {
            cout << "Name: " << current->name << ", Roll No: " << current->roll << endl;
            current = current->next;
        }
    }
};

int main() {
    StudentList sList;

    sList.insertStudent("Alice", 3);
    sList.insertStudent("Bob", 1);
    sList.insertStudent("Charlie", 2);

    cout << "Student Records:\n";
    sList.displayStudents();

    cout << "\nDeleting Roll No 2...\n";
    sList.deleteStudent(2);

    cout << "Updated Records:\n";
    sList.displayStudents();

    return 0;
}

