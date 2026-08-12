#include<iostream>
#include<vector>
#include<fstream>
#include<sstream>
using namespace std;

typedef struct{
    public:
    int empId;
    string name;
    int deptId;
    string dept;
    int salary;
}emp;

typedef struct{
    public:
    string IT="IT";
    string Sales="Sales";
    string HR="HR";
    string Finance="Finance";
    string Marketing="Marketing";
}deptName;

void addEmployee(){
    ofstream ptr("employee.csv",ios::app);

    if(!ptr) {
        cout<<"Error in opening file";
        return;
    }

    emp employee;
    deptName depName;

    cout<<"Enter Employee ID: ";
    cin>>employee.empId;
    cout<<"Enter Employee Name: ";
    cin>>employee.name;
    cout<<"Enter Department ID: ";
    cin>>employee.deptId;
    cout<<"Enter Salary: ";
    cin>>employee.salary;

    switch (employee.deptId){
    case 1011:
        employee.dept=depName.IT;
        break;
    case 1012:
        employee.dept=depName.Sales;
        break;
    case 1013:
        employee.dept=depName.HR;
        break;
    case 1014:
        employee.dept=depName.Finance;
        break;
    case 1015:
        employee.dept=depName.Marketing;
        break;
    default:
        cout<<"Enter valid Department";
        ptr.close();
        return;
    }

    ptr<<employee.empId<<","<<employee.name<<","<<employee.deptId<<","<<employee.dept<<","<<employee.salary<<endl;

    ptr.close();
}

void displayEmployee(){
    ifstream ptr("employee.csv",ios::in);

    if(!ptr) {
        cout<<"Error in opening file";
        return;
    }

    printf("=====Employee Record=====");
    cout<<"ID\tName\tDepartment ID\tDepartment\tSalary\n";
    cout<<"-----------------------------------------------------------------\n";

    emp employee;
    string line;
    string temp;

    while(getline(ptr,line)){
        stringstream ss(line);

        getline(ss,temp,',');
        employee.empId=stoi(temp);

        getline(ss,employee.name,',');

        getline(ss,temp,',');
        employee.deptId=stoi(temp);

        getline(ss,employee.dept,',');

        getline(ss,temp,',');
        employee.salary=stoi(temp);

        cout << employee.empId << "\t"
            << employee.name << "\t"
            << employee.deptId << "\t\t"
            << employee.dept << "\t\t"
            << employee.salary << "\n";
    }

    ptr.close();
}

int main(){ 
    int choice;

    while(true){
        cout<<"Enter Choice: ";
        cout<<"1.Add Employee: ";
        cout<<"2.Display All Employees: ";
        cout<<"3.Exit";

        switch (choice){
        case 1:
            addEmployee();
            break;
        case 2:
            displayEmployee();
            break;
        case 3:
            cout<<"Exiting the Program....";
            exit(0);
        default:
            cout<<"Enter a valid input";
            break;
        }
    }
    return 0;
}