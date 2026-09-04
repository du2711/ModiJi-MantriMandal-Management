#ifndef EMPLOYEE_MANAGER_H
#define EMPLOYEE_MANAGER_H

#include "Employee.h"
#include <string>
#include <vector>

using namespace std;

class EmployeeManager {

private:

    string fileName = "employee.csv";

    string getDepartment(int deptId);

    Employee parseEmployee(string line);

    void printEmployee(const Employee& employee);

public:

    // =========================
    // API / DATA METHODS
    // =========================

    vector<Employee> getAllEmployees();

    bool addEmployee(const Employee& employee);

    bool updateEmployee(const Employee& employee);

    bool deleteEmployee(int id);

    bool getEmployeeById(int id, Employee& employee);


    // =========================
    // EXISTING METHODS
    // =========================

    bool employeeExists(int id);

    void addEmployee();

    void displayEmployees();

    void deleteEmployee();

    void updateEmployee();

    void searchEmployee();
};

#endif