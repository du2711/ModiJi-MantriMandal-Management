#include "EmployeeManager.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>

using namespace std;

string EmployeeManager::getDepartment(int deptId) {

    switch (deptId) {
        case 1011:
            return "IT";

        case 1012:
            return "Sales";

        case 1013:
            return "HR";

        case 1014:
            return "Finance";

        case 1015:
            return "Marketing";

        default:
            return "";
    }
}

Employee EmployeeManager::parseEmployee(string line) {

    stringstream ss(line);
    string temp;

    Employee employee;

    getline(ss, temp, ',');
    employee.setEmpId(stoi(temp));

    getline(ss, temp, ',');
    employee.setName(temp);

    getline(ss, temp, ',');
    employee.setDeptId(stoi(temp));

    getline(ss, temp, ',');
    employee.setDept(temp);

    getline(ss, temp, ',');
    employee.setSalary(stoi(temp));

    return employee;
}

void EmployeeManager::printEmployee(const Employee& employee) {

    cout << employee.getEmpId() << "\t"
         << employee.getName() << "\t\t"
         << employee.getDeptId() << "\t\t"
         << employee.getDept() << "\t\t"
         << employee.getSalary() << "\n";
}

bool EmployeeManager::employeeExists(int id) {

    ifstream file(fileName);

    if (!file)
        return false;

    string line;

    while (getline(file, line)) {

        Employee employee = parseEmployee(line);

        if (employee.getEmpId() == id)
            return true;
    }

    return false;
}

void EmployeeManager::addEmployee() {

    Employee employee;

    int id;
    string name;
    int deptId;
    int salary;

    cout << "Enter Employee ID: ";
    cin >> id;

    if (employeeExists(id)) {
        cout << "Employee already exists\n";
        return;
    }

    cin.ignore();

    cout << "Enter Employee Name: ";
    getline(cin, name);

    cout << "Enter Department ID: ";
    cin >> deptId;

    string dept = getDepartment(deptId);

    if (dept.empty()) {
        cout << "Invalid Department ID\n";
        return;
    }

    cout << "Enter Salary: ";
    cin >> salary;

    employee.setEmpId(id);
    employee.setName(name);
    employee.setDeptId(deptId);
    employee.setDept(dept);
    employee.setSalary(salary);

    ofstream file(fileName, ios::app);

    if (!file) {
        cout << "Error opening file\n";
        return;
    }

    file << employee.getEmpId() << ","
         << employee.getName() << ","
         << employee.getDeptId() << ","
         << employee.getDept() << ","
         << employee.getSalary() << "\n";

    cout << "Employee added successfully\n";
}

void EmployeeManager::displayEmployees() {

    ifstream file(fileName);

    if (!file) {
        cout << "Error opening file\n";
        return;
    }

    cout << "\n===== Employee Records =====\n";

    cout << "ID\tName\t\tDepartment ID\tDepartment\tSalary\n";

    cout << "---------------------------------------------------------------\n";

    string line;

    while (getline(file, line)) {

        Employee employee = parseEmployee(line);

        printEmployee(employee);
    }
}

void EmployeeManager::deleteEmployee() {

    ifstream file(fileName);

    if (!file) {
        cout << "Error opening file\n";
        return;
    }

    int id;

    cout << "Enter Employee ID to delete: ";
    cin >> id;

    ofstream tempFile("temp.csv");

    string line;
    bool found = false;

    while (getline(file, line)) {

        Employee employee = parseEmployee(line);

        if (employee.getEmpId() != id) {

            tempFile << employee.getEmpId() << ","
                     << employee.getName() << ","
                     << employee.getDeptId() << ","
                     << employee.getDept() << ","
                     << employee.getSalary() << "\n";

        } else {
            found = true;
        }
    }

    file.close();
    tempFile.close();

    if (found) {

        remove(fileName.c_str());
        rename("temp.csv", fileName.c_str());

        cout << "Employee deleted successfully\n";

    } else {

        remove("temp.csv");

        cout << "Employee not found\n";
    }
}

void EmployeeManager::updateEmployee() {

    ifstream file(fileName);

    if (!file) {
        cout << "Error opening file\n";
        return;
    }

    int id;

    cout << "Enter Employee ID: ";
    cin >> id;

    ofstream tempFile("temp.csv");

    string line;
    bool found = false;

    while (getline(file, line)) {

        Employee employee = parseEmployee(line);

        if (employee.getEmpId() == id) {

            found = true;

            string name;
            int deptId;
            int salary;

            cin.ignore();

            cout << "Enter Employee Name: ";
            getline(cin, name);

            cout << "Enter Department ID: ";
            cin >> deptId;

            string dept = getDepartment(deptId);

            if (dept.empty()) {

                cout << "Invalid Department ID\n";

                file.close();
                tempFile.close();

                remove("temp.csv");

                return;
            }

            cout << "Enter Salary: ";
            cin >> salary;

            employee.setName(name);
            employee.setDeptId(deptId);
            employee.setDept(dept);
            employee.setSalary(salary);
        }

        tempFile << employee.getEmpId() << ","
                 << employee.getName() << ","
                 << employee.getDeptId() << ","
                 << employee.getDept() << ","
                 << employee.getSalary() << "\n";
    }

    file.close();
    tempFile.close();

    if (found) {

        remove(fileName.c_str());
        rename("temp.csv", fileName.c_str());

        cout << "Employee details updated successfully\n";

    } else {

        remove("temp.csv");

        cout << "Employee not found\n";
    }
}

void EmployeeManager::searchEmployee() {

    ifstream file(fileName);

    if (!file) {
        cout << "Error opening file\n";
        return;
    }

    int id;

    cout << "Enter Employee ID: ";
    cin >> id;

    string line;
    bool found = false;

    while (getline(file, line)) {

        Employee employee = parseEmployee(line);

        if (employee.getEmpId() == id) {

            cout << "\n===== Employee Record =====\n";

            cout << "ID\tName\t\tDepartment ID\tDepartment\tSalary\n";

            cout << "---------------------------------------------------------------\n";

            printEmployee(employee);

            found = true;

            break;
        }
    }

    if (!found)
        cout << "Employee not found\n";
}