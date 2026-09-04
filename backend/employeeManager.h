#ifndef EMPLOYEE_MANAGER_H
#define EMPLOYEE_MANAGER_H

#include "Employee.h"
#include <string>

using namespace std;

class EmployeeManager {

private:
    string fileName = "employee.csv";

    string getDepartment(int deptId);
    Employee parseEmployee(string line);
    void printEmployee(const Employee& employee);

public:
    bool employeeExists(int id);

    void addEmployee();
    void displayEmployees();
    void deleteEmployee();
    void updateEmployee();
    void searchEmployee();
};

#endif