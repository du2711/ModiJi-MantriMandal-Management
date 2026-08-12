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
        cout<<"Employee Deleted Successfully";
        remove("employee.csv");
        rename("temp.csv","employee.csv");
    }
    else {
        cout<<"Employee not found";
        remove("temp.csv");
    }
}