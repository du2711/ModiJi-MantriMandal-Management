#include "httplib.h"
#include "EmployeeManager.h"

#include <iostream>
#include <sstream>

using namespace std;

int main() {
    EmployeeManager manager;
    httplib::Server server;

    // CORS
    server.set_pre_routing_handler(
        [](const httplib::Request& req, httplib::Response& res) {

            res.set_header("Access-Control-Allow-Origin", "*");
            res.set_header(
                "Access-Control-Allow-Methods",
                "GET, POST, PUT, DELETE, OPTIONS"
            );
            res.set_header(
                "Access-Control-Allow-Headers",
                "Content-Type"
            );

            if (req.method == "OPTIONS")
                return httplib::Server::HandlerResponse::Handled;

            return httplib::Server::HandlerResponse::Unhandled;
        }
    );

    // GET all employees
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

        res.set_content(
            json.str(),
            "application/json"
        );
    });

    // POST - Add employee
    server.Post("/employees", [&](const httplib::Request& req,
                                httplib::Response& res) {

        try {
            string body = req.body;

            auto getValue = [&](string key) {
                string search = "\"" + key + "\":";
                size_t start = body.find(search);

                if (start == string::npos)
                    return string("");

                start += search.length();

                while (start < body.length() && body[start] == ' ')
                    start++;

                if (body[start] == '"') {
                    start++;

                    size_t end = body.find('"', start);

                    return body.substr(start, end - start);
                }

                size_t end = body.find_first_of(",}", start);

                return body.substr(start, end - start);
            };

            int empId = stoi(getValue("empId"));
            string name = getValue("name");
            int deptId = stoi(getValue("deptId"));
            int salary = stoi(getValue("salary"));

            Employee employee(
                empId,
                name,
                deptId,
                "",
                salary
            );

            if (!manager.addEmployee(employee)) {

                res.status = 400;

                res.set_content(
                    "{\"success\":false,\"message\":\"Unable to add employee\"}",
                    "application/json"
                );

                return;
            }

            res.status = 201;

            res.set_content(
                "{\"success\":true,\"message\":\"Employee added successfully\"}",
                "application/json"
            );

        } catch (...) {

            res.status = 400;

            res.set_content(
                "{\"success\":false,\"message\":\"Invalid employee data\"}",
                "application/json"
            );
        }
    });

    // PUT - Update employee
server.Put(R"(/employees/(\d+))",
    [&](const httplib::Request& req, httplib::Response& res) {

        try {
            int empId = stoi(req.matches[1]);

            string body = req.body;

            auto getValue = [&](string key) {
                string search = "\"" + key + "\":";
                size_t start = body.find(search);

                if (start == string::npos)
                    return string("");

                start += search.length();

                while (start < body.length() && body[start] == ' ')
                    start++;

                if (body[start] == '"') {
                    start++;

                    size_t end = body.find('"', start);

                    return body.substr(start, end - start);
                }

                size_t end = body.find_first_of(",}", start);

                return body.substr(start, end - start);
            };

            string name = getValue("name");
            int deptId = stoi(getValue("deptId"));
            int salary = stoi(getValue("salary"));

            Employee employee(
                empId,
                name,
                deptId,
                "",
                salary
            );

            if (!manager.updateEmployee(employee)) {

                res.status = 404;

                res.set_content(
                    "{\"success\":false,\"message\":\"Employee not found or update failed\"}",
                    "application/json"
                );

                return;
            }

            res.status = 200;

            res.set_content(
                "{\"success\":true,\"message\":\"Employee updated successfully\"}",
                "application/json"
            );

        } catch (...) {

            res.status = 400;

            res.set_content(
                "{\"success\":false,\"message\":\"Invalid employee data\"}",
                "application/json"
            );
        }
    }
);

// DELETE - Delete employee
server.Delete(R"(/employees/(\d+))",
    [&](const httplib::Request& req, httplib::Response& res) {

        try {
            int empId = stoi(req.matches[1]);

            if (!manager.deleteEmployee(empId)) {
                res.status = 404;

                res.set_content(
                    "{\"success\":false,\"message\":\"Employee not found\"}",
                    "application/json"
                );

                return;
            }

            res.status = 200;

            res.set_content(
                "{\"success\":true,\"message\":\"Employee deleted successfully\"}",
                "application/json"
            );

        } catch (...) {

            res.status = 400;

            res.set_content(
                "{\"success\":false,\"message\":\"Invalid employee ID\"}",
                "application/json"
            );
        }
    }
);

    cout << "Employee Management API running...\n";
    cout << "Server: http://localhost:8080\n";

    server.listen("localhost", 8080);

    return 0;
}