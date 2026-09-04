#include "EmployeeManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>

using namespace std;

string EmployeeManager::getDepartment(int deptId) {
    switch (deptId) {
        case 1011: return "IT";
        case 1012: return "Sales";
        case 1013: return "HR";
        case 1014: return "Finance";
        case 1015: return "Marketing";
        default: return "";
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
    if (!file) return false;

    string line;

    while (getline(file, line)) {
        if (line.empty()) continue;

        Employee employee = parseEmployee(line);

        if (employee.getEmpId() == id)
            return true;
    }

    return false;
}

vector<Employee> EmployeeManager::getAllEmployees() {
    vector<Employee> employees;
    ifstream file(fileName);

    if (!file) return employees;

    string line;

    while (getline(file, line)) {
        if (line.empty()) continue;
        employees.push_back(parseEmployee(line));
    }

    return employees;
}

bool EmployeeManager::getEmployeeById(int id, Employee& employee) {
    ifstream file(fileName);
    if (!file) return false;

    string line;

    while (getline(file, line)) {
        if (line.empty()) continue;

        Employee currentEmployee = parseEmployee(line);

        if (currentEmployee.getEmpId() == id) {
            employee = currentEmployee;
            return true;
        }
    }

    return false;
}

bool EmployeeManager::addEmployee(const Employee& employee) {
    if (employeeExists(employee.getEmpId()))
        return false;

    string department = getDepartment(employee.getDeptId());

    if (department.empty())
        return false;

    ofstream file(fileName, ios::app);

    if (!file)
        return false;

    file << employee.getEmpId() << ","
         << employee.getName() << ","
         << employee.getDeptId() << ","
         << department << ","
         << employee.getSalary() << "\n";

    return true;
}

bool EmployeeManager::updateEmployee(const Employee& updatedEmployee) {
    ifstream file(fileName);
    if (!file) return false;

    string department = getDepartment(updatedEmployee.getDeptId());

    if (department.empty())
        return false;

    ofstream tempFile("temp.csv");
    if (!tempFile) return false;

    string line;
    bool found = false;

    while (getline(file, line)) {
        if (line.empty()) continue;

        Employee employee = parseEmployee(line);

        if (employee.getEmpId() == updatedEmployee.getEmpId()) {
            found = true;

            tempFile << updatedEmployee.getEmpId() << ","
                     << updatedEmployee.getName() << ","
                     << updatedEmployee.getDeptId() << ","
                     << department << ","
                     << updatedEmployee.getSalary() << "\n";
        } else {
            tempFile << employee.getEmpId() << ","
                     << employee.getName() << ","
                     << employee.getDeptId() << ","
                     << employee.getDept() << ","
                     << employee.getSalary() << "\n";
        }
    }

    file.close();
    tempFile.close();

    if (!found) {
        remove("temp.csv");
        return false;
    }

    remove(fileName.c_str());
    rename("temp.csv", fileName.c_str());

    return true;
}

bool EmployeeManager::deleteEmployee(int id) {
    ifstream file(fileName);
    if (!file) return false;

    ofstream tempFile("temp.csv");
    if (!tempFile) return false;

    string line;
    bool found = false;

    while (getline(file, line)) {
        if (line.empty()) continue;

        Employee employee = parseEmployee(line);

        if (employee.getEmpId() == id) {
            found = true;
            continue;
        }

        tempFile << employee.getEmpId() << ","
                 << employee.getName() << ","
                 << employee.getDeptId() << ","
                 << employee.getDept() << ","
                 << employee.getSalary() << "\n";
    }

    file.close();
    tempFile.close();

    if (!found) {
        remove("temp.csv");
        return false;
    }

    remove(fileName.c_str());
    rename("temp.csv", fileName.c_str());

    return true;
}

void EmployeeManager::addEmployee() {
    int id, deptId, salary;
    string name;

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

    string department = getDepartment(deptId);

    if (department.empty()) {
        cout << "Invalid Department ID\n";
        return;
    }

    cout << "Enter Salary: ";
    cin >> salary;

    Employee employee(id, name, deptId, department, salary);

    if (addEmployee(employee))
        cout << "Employee added successfully\n";
    else
        cout << "Unable to add employee\n";
}

void EmployeeManager::displayEmployees() {
    vector<Employee> employees = getAllEmployees();

    if (employees.empty()) {
        cout << "No employee records found\n";
        return;
    }

    cout << "\n===== Employee Records =====\n";
    cout << "ID\tName\t\tDepartment ID\tDepartment\tSalary\n";
    cout << "---------------------------------------------------------------\n";

    for (const Employee& employee : employees)
        printEmployee(employee);
}

void EmployeeManager::deleteEmployee() {
    int id;

    cout << "Enter Employee ID to delete: ";
    cin >> id;

    if (deleteEmployee(id))
        cout << "Employee deleted successfully\n";
    else
        cout << "Employee not found\n";
}

void EmployeeManager::updateEmployee() {
    int id;

    cout << "Enter Employee ID: ";
    cin >> id;

    Employee oldEmployee;

    if (!getEmployeeById(id, oldEmployee)) {
        cout << "Employee not found\n";
        return;
    }

    string name;
    int deptId, salary;

    cin.ignore();

    cout << "Enter Employee Name: ";
    getline(cin, name);

    cout << "Enter Department ID: ";
    cin >> deptId;

    string department = getDepartment(deptId);

    if (department.empty()) {
        cout << "Invalid Department ID\n";
        return;
    }

    cout << "Enter Salary: ";
    cin >> salary;

    Employee updatedEmployee(id, name, deptId, department, salary);

    if (updateEmployee(updatedEmployee))
        cout << "Employee details updated successfully\n";
    else
        cout << "Unable to update employee\n";
}

void EmployeeManager::searchEmployee() {
    int id;

    cout << "Enter Employee ID: ";
    cin >> id;

    Employee employee;

    if (!getEmployeeById(id, employee)) {
        cout << "Employee not found\n";
        return;
    }

    cout << "\n===== Employee Record =====\n";
    cout << "ID\tName\t\tDepartment ID\tDepartment\tSalary\n";
    cout << "---------------------------------------------------------------\n";

    printEmployee(employee);
}