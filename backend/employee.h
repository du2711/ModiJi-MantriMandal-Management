#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>
using namespace std;

class Employee {
private:
    int empId;
    string name;
    int deptId;
    string dept;
    int salary;

public:
    Employee();

    Employee(int empId, string name, int deptId, string dept, int salary);

    int getEmpId() const;
    string getName() const;
    int getDeptId() const;
    string getDept() const;
    int getSalary() const;

    void setEmpId(int id);
    void setName(string name);
    void setDeptId(int id);
    void setDept(string dept);
    void setSalary(int salary);
};

#endif