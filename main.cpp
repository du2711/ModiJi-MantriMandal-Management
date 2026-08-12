#include<iostream>
#include<vector>

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
    FILE *ptr=fopen("employee.csv","a");

    if(ptr==NULL) {
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
        fclose(ptr);
        return;
    }

    fprintf(ptr, "%d,%s,%d,%s,%d\n",employee.empId,employee.name.c_str(),employee.deptId,employee.dept.c_str(),employee.salary);

    fclose(ptr);
}

void displayEmployee(){
    FILE* ptr=fopen("employee.csv","r");

    if(ptr==NULL) {
        cout<<"Error in opening file";
        return;
    }

    emp employee;

    printf("=====Employee Record=====");
    cout<<"ID       Name        Department ID       Department      Salary\n";
    cout<<"-----------------------------------------------------------------\n";

    // while(fscanf("%d,%[^,],%d,%[^,],%d",&employee.empId,employee.name,&employee.deptId,employee.dept,&employee.salary)){
    //     cout<<("%d       %s      %d      %s      %d\n",employee.empId,employee.name.c_str(),employee.deptId,employee.dept.c_str(),employee.salary);
    // }

    fclose(ptr);
}

int main(){ 
    addEmployee();
    cout<<"Employee Added Successfully";
    return 0;
}