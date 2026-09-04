#include "httplib.h"
#include "EmployeeManager.h"

#include <iostream>
#include <sstream>

using namespace std;

int main() {
    EmployeeManager manager;
    httplib::Server server;

    server.Get("/employees", [&](const httplib::Request& req,
                                 httplib::Response& res) {

        vector<Employee> employees = manager.getAllEmployees();

        stringstream json;
        json << "[";

        for (size_t i = 0; i < employees.size(); i++) {
            const Employee& employee = employees[i];

            json << "{"
                 << "\"empId\":" << employee.getEmpId() << ","
                 << "\"name\":\"" << employee.getName() << "\","
                 << "\"deptId\":" << employee.getDeptId() << ","
                 << "\"dept\":\"" << employee.getDept() << "\","
                 << "\"salary\":" << employee.getSalary()
                 << "}";

            if (i < employees.size() - 1)
                json << ",";
        }

        json << "]";

        res.set_content(json.str(), "application/json");
    });

    cout << "Employee Management API running...\n";
    cout << "Server: http://localhost:8080\n";

    server.listen("localhost", 8080);

    return 0;
}