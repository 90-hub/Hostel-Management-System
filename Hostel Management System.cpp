#include <iostream>
#include <string>
using namespace std;

class Person {
protected:
    int id; 
    string name;

public:
    void setPerson(int i, string n) {
        id = i;
        name = n;
    }

    virtual void display() {
        cout << "ID: " << id << "\nName: " << name << endl;
    }
};

class Student : public Person {
private:
    string contactNumber;
    int roomNumber;
    float feeAmount;
    bool feePaid;

public:
    void setStudent(int i, string n, string c, int r, float f, bool paid) {
        setPerson(i, n);
        contactNumber = c;
        roomNumber = r;
        feeAmount = f;
        feePaid = paid;
    }

    int getId() { 
	    return id; }
    int getRoom() { 
	    return roomNumber; }
    bool isFeePaid() { 
	    return feePaid; }

    void updateFees(float f) {
        feeAmount = f;
        feePaid = true;
    }

    void display() {
        cout << "\n--- Student Details ---\n";
        cout << "ID         : " << id << endl;
        cout << "Name       : " << name << endl;
        cout << "Contact    : " << contactNumber << endl;
        cout << "Room No    : " << roomNumber << endl;
        cout << "Fees Paid  : " << (feePaid ? "Yes" : "No") << endl;
    }
};

class Room {
private:
    int roomNumber;
    bool isAvailable;

public:
    Room() {
        isAvailable = true;
    }

    void assignRoom(int r) {
        roomNumber = r;
        isAvailable = false;
    }

    void freeRoom() {
        isAvailable = true;
    }

    bool available() {
        return isAvailable;
    }

    int getRoomNumber() {
        return roomNumber;
    }

    void display() {
        cout << "Room " << roomNumber
             << "  Available: " << (isAvailable ? "Yes" : "No") << endl;
    }
};

class Screen {
public:
    virtual void show() = 0;
};

class StudentScreen : public Screen {
private:
    Student students[50];
    Room rooms[50];
    int totalStudents;
    int totalRooms;

public:
    StudentScreen() {
        totalStudents = 0;
        totalRooms = 0;
        for(int i = 0; i < 20; i++) {
            rooms[i].assignRoom(i + 1);
            rooms[i].freeRoom();
            totalRooms++;
        }
    }

    void addStudent() {
        int id, room;
        float fees;
        string name, contact;
        bool paid;

        cout << "\nEnter Student ID: ";
        cin >> id;

        cout << "Enter Student Name: ";
        cin >> name;

        cout << "Enter Contact Number: ";
        cin >> contact;

        cout << "Available Rooms:\n";
        for(int i = 0; i < totalRooms; i++) {
            if(rooms[i].available()) {
                cout << rooms[i].getRoomNumber() << " ";
            }
        }

        cout << "\nChoose a Room Number: ";
        cin >> room;

        bool validRoom = false;
        for(int i = 0; i < totalRooms; i++) {
            if(rooms[i].getRoomNumber() == room && rooms[i].available()) {
                rooms[i].assignRoom(room);
                validRoom = true;
                break;
            }
        }

        if(!validRoom) {
            cout << "Room is not available!\n";
            return;
        }

        cout << "Enter Fees Amount: ";
        cin >> fees;

        cout << "Has student paid fees? (1=Yes, 0=No): ";
        cin >> paid;

        students[totalStudents].setStudent(id, name, contact, room, fees, paid);
        totalStudents++;

        cout << "\n>> Student Added Successfully!\n";
    }

    void viewStudents() {
        if(totalStudents == 0) {
            cout << "\nNo students.\n";
            return;
        }
        for(int i = 0; i < totalStudents; i++) {
            students[i].display();
        }
    }

    void viewRooms() {
        cout << "\nRoom Status:\n";
        for(int i = 0; i < totalRooms; i++) {
            rooms[i].display();
        }
    }

    void updateFees() {
        int id;
        float newFee;

        cout << "Enter Student ID to update fees: ";
        cin >> id;

        for(int i = 0; i < totalStudents; i++) {
            if(students[i].getId() == id) {
                cout << "Enter new fee amount: ";
                cin >> newFee;
                students[i].updateFees(newFee);
                cout << ">> Fees updated successfully!\n";
                return;
            }
        }
        cout << "Student not found!\n";
    }

    void deleteStudent() {
        int id;
        cout << "Enter Student ID to delete: ";
        cin >> id;

        for(int i = 0; i < totalStudents; i++) {
            if(students[i].getId() == id) {
                int roomNum = students[i].getRoom();

                for(int j = 0; j < totalRooms; j++) {
                    if(rooms[j].getRoomNumber() == roomNum) {
                        rooms[j].freeRoom();
                        break;
                    }
                }

                for(int j = i; j < totalStudents - 1; j++) {
                    students[j] = students[j + 1];
                }
                totalStudents--;

                cout << ">> Student deleted successfully!\n";
                return;
            }
        }
        cout << "Student not found!\n";
    }

    void show() {
        int choice;
        do {
            cout << "\n--- Hostel Management System ---\n";
            cout << "1. Add Student\n";
            cout << "2. View Students\n";
            cout << "3. Update Fees\n";
            cout << "4. Delete Student\n";
            cout << "5. View Rooms Status\n";
            cout << "6. Exit\n";
            cout << "Enter choice: ";
            cin >> choice;

            switch(choice) {
                case 1: addStudent(); break;
                case 2: viewStudents(); break;
                case 3: updateFees(); break;
                case 4: deleteStudent(); break;
                case 5: viewRooms(); break;
                case 6: cout << "System exist!\n"; break;
                default: cout << "Invalid choice! Try again.\n";
            }
        } while(choice != 6);
    }
};

int main() {
    StudentScreen screen;
    screen.show();
    return 0;
}

