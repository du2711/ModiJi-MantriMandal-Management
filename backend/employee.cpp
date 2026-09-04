#include "Employee.h"

Employee::Employee() {
    empId = 0;
    deptId = 0;
    salary = 0;
}

Employee::Employee(
    int empId,
    string name,
    int deptId,
    string dept,
    int salary
) {
    this->empId = empId;
    this->name = name;
    this->deptId = deptId;
    this->dept = dept;
    this->salary = salary;
}

int Employee::getEmpId() const {
    return empId;
}

string Employee::getName() const {
    return name;
}

int Employee::getDeptId() const {
    return deptId;
}

string Employee::getDept() const {
    return dept;
}

int Employee::getSalary() const {
    return salary;
}

void Employee::setEmpId(int id) {
    empId = id;
}

void Employee::setName(string name) {
    this->name = name;
}

void Employee::setDeptId(int id) {
    deptId = id;
}

void Employee::setDept(string dept) {
    this->dept = dept;
}

void Employee::setSalary(int salary) {
    this->salary = salary;
}