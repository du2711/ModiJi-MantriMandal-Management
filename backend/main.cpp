#include <iostream>
#include "employeeManager.h"

using namespace std;

int main() {

    EmployeeManager manager;

    int choice;

    while (true) {

        cout << "\n===== Employee Management System =====\n\n";

        cout << "1. Add Employee\n";
        cout << "2. Display All Employees\n";
        cout << "3. Delete Employee\n";
        cout << "4. Update Employee\n";
        cout << "5. Search Employee\n";
        cout << "6. Exit\n\n";

        cout << "Enter Your Choice: ";
        cin >> choice;

        switch (choice) {

            case 1:
                manager.addEmployee();
                break;

            case 2:
                manager.displayEmployees();
                break;

            case 3:
                manager.deleteEmployee();
                break;

            case 4:
                manager.updateEmployee();
                break;

            case 5:
                manager.searchEmployee();
                break;

            case 6:
                cout << "Exiting program...\n";
                return 0;

            default:
                cout << "Enter a valid input\n";
        }
    }
}
