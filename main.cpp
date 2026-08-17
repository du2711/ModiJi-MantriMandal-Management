#include<iostream>
#include<vector>
#include<fstream>
#include<sstream>
#include<cstdio>

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

    ptr << employee.empId << "," << employee.name << "," << employee.deptId << "," << employee.dept << "," << employee.salary << endl;

    ptr.close();
}

void displayEmployee(){
    ifstream ptr("employee.csv",ios::in);

    if(!ptr) {
        cout<<"Error in opening file";
        return;
    }

    printf("\n\t\t=====Mantri-Mandal Record=====\n");
    cout<<"ID\tName\t\t\tDepartment ID\t\tDepartment\tSalary\n";
    cout<<"-------------------------------------------------------------------------------\n";

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

        cout <<employee.empId << "\t"
            << employee.name << "\t\t"
            << employee.deptId << "\t\t\t"
            << employee.dept << "\t\t"
            << employee.salary << "\n";
    }

    ptr.close();
}

void deleteEmployee(){
    ifstream ptr("employee.csv",ios::in);

    if(!ptr) {
        cout<<"Error in opening file";
        return;
    }

    emp employee;
    ofstream temp("temp.csv",ios::out);

    if(!temp){
        cout<<"Error in opening file";
        return; 
    }

    int del;
    cout<<"Enter Employee Id to delete: ";
    cin>>del;

    string line;
    string tempData;
    bool found = false;

    while(getline(ptr,line)){
        stringstream ss(line);

        getline(ss,tempData,',');
        employee.empId=stoi(tempData);

        getline(ss,employee.name,',');

        getline(ss,tempData,',');
        employee.deptId=stoi(tempData);

        getline(ss,employee.dept,',');

        getline(ss,tempData,',');
        employee.salary=stoi(tempData);

        if(employee.empId != del){
            temp <<employee.empId << ","
            << employee.name << ","
            << employee.deptId << ","
            << employee.dept << ","
            << employee.salary << "\n";
        }
        else found=true;
    }

    ptr.close();
    temp.close();

    if(found){
        cout<<"Employee Deleted Successfully\n";
        remove("employee.csv");
        rename("temp.csv","employee.csv");
    }
    else {
        cout<<"Employee not found\n";
        remove("temp.csv");
    }
}

void updateEmployee(){
    ifstream ptr("employee.csv");

    if(!ptr){
        cout<<"Error in opening file";
        return;
    }

    emp employee;

    int edit;
    cout<<"Enter Employee Id: ";
    cin>>edit;

    ofstream temp("temp.csv");

    if(!temp){
        cout<<"Error in opening file";
        return;
    }

    string line;
    string tempdata;
    bool found = false;

    deptName depName;

    while(getline(ptr,line)){
        stringstream ss(line);

        getline(ss,tempdata,',');
        employee.empId=stoi(tempdata);

        getline(ss,employee.name,',');

        getline(ss,tempdata,',');
        employee.deptId=stoi(tempdata);

        getline(ss,employee.dept,',');

        getline(ss,tempdata,',');
        employee.salary=stoi(tempdata);

        if(edit==employee.empId){
            found=true;
            cout<<"Enter Employee name: ";
            cin>>employee.name;

            cout<<"Enter Department ID: ";
            cin>>employee.deptId;

            switch(employee.deptId){
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
                    cout<<"Enter valid Department ID";
                    ptr.close();
                    temp.close();
                    remove("temp.csv");
                    return;
            }
            cout<<"Enter Salary: ";
            cin>>employee.salary;
        }

        temp<< employee.empId << ","
            << employee.name << ","
            << employee.deptId << ","
            << employee.dept << ","
            << employee.salary << "\n";
    }

    ptr.close();
    temp.close();

    if(found){
        remove("employee.csv");
        rename("temp.csv","employee.csv");
        cout<<"Employee Details Updated Successfully";
    }
    else{
        remove("temp.csv");
        cout<<"Employee not found";
    }
}

int main(){ 
    int choice;
    while(1){
        cout<<"\n===Modi ji MantriMandal Management System===\n";
        cout<<"1.Add Employee: \n";
        cout<<"2.Display All Employees: \n";
        cout<<"3.Delete Employee\n";
        cout<<"4.Update Employee Details\n";
        cout<<"5.Exit\n";
        cout<<"Enter Your Choice: ";
        cin>>choice;

        switch (choice){
        case 1:
            addEmployee();
            break;
        case 2:
            displayEmployee();
            break;
        case 3:
            deleteEmployee();
            break;
        case 4:
            updateEmployee();
            break;
        case 5:
            cout<<"Exiting the Program....";
            return 0;
        default:
            cout<<"Enter a valid input";
            break;
        }
    }
}