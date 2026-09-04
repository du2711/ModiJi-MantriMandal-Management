const API_URL = "http://localhost:8080";

let employees = [];

const tableBody = document.getElementById("employeeTableBody");
const searchInput = document.getElementById("searchInput");
const departmentFilter = document.getElementById("departmentFilter");
const addEmployeeBtn = document.getElementById("addEmployeeBtn");

const totalEmployees = document.getElementById("totalEmployees");
const totalDepartments = document.getElementById("totalDepartments");
const averageSalary = document.getElementById("averageSalary");
const highestSalary = document.getElementById("highestSalary");

const loadingMessage = document.getElementById("loadingMessage");
const errorMessage = document.getElementById("errorMessage");


// ==========================================
// LOAD EMPLOYEES FROM C++ BACKEND
// ==========================================

async function loadEmployees() {

    try {

        showLoading(true);
        showError("");

        const response = await fetch(`${API_URL}/employees`);

        if (!response.ok) {
            throw new Error("Failed to fetch employees");
        }

        employees = await response.json();

        renderEmployees();
        updateStats();

    } catch (error) {

        console.error(error);

        showError(
            "Unable to connect to the backend. Make sure the C++ server is running."
        );

    } finally {

        showLoading(false);
    }
}


// ==========================================
// DISPLAY EMPLOYEES
// ==========================================

function renderEmployees() {

    const searchText =
        searchInput.value.toLowerCase().trim();

    const selectedDepartment =
        departmentFilter.value;


    const filteredEmployees = employees.filter(employee => {

        const matchesSearch =
            employee.name.toLowerCase().includes(searchText) ||
            employee.empId.toString().includes(searchText);


        const matchesDepartment =
            selectedDepartment === "all" ||
            employee.dept === selectedDepartment;


        return matchesSearch && matchesDepartment;
    });


    tableBody.innerHTML = "";


    if (filteredEmployees.length === 0) {

        tableBody.innerHTML = `
            <tr>
                <td colspan="6" class="empty">
                    No employees found
                </td>
            </tr>
        `;

        return;
    }


    filteredEmployees.forEach(employee => {

        const row = document.createElement("tr");


        row.innerHTML = `

            <td>
                #${employee.empId}
            </td>


            <td>

                <div class="employee">

                    <div class="employee-avatar">
                        ${getInitials(employee.name)}
                    </div>

                    <div>

                        <strong>
                            ${escapeHTML(employee.name)}
                        </strong>

                        <span>
                            Employee ID: ${employee.empId}
                        </span>

                    </div>

                </div>

            </td>


            <td>
                ${employee.deptId}
            </td>


            <td>

                <span class="department ${getDepartmentClass(employee.dept)}">
                    ${escapeHTML(employee.dept)}
                </span>

            </td>


            <td>
                ₹${Number(employee.salary).toLocaleString("en-IN")}
            </td>


            <td class="actions">

                <button
                    class="edit"
                    onclick="editEmployee(${employee.empId})">
                    Edit
                </button>


                <button
                    class="delete"
                    onclick="deleteEmployee(${employee.empId})">
                    Delete
                </button>

            </td>

        `;


        tableBody.appendChild(row);
    });
}


// ==========================================
// DASHBOARD STATISTICS
// ==========================================

function updateStats() {

    totalEmployees.textContent =
        employees.length;


    const departments = new Set(
        employees.map(employee => employee.dept)
    );

    totalDepartments.textContent =
        departments.size;


    if (employees.length === 0) {

        averageSalary.textContent = "₹0";
        highestSalary.textContent = "₹0";

        return;
    }


    const salaries = employees.map(
        employee => Number(employee.salary)
    );


    const totalSalary =
        salaries.reduce(
            (sum, salary) => sum + salary,
            0
        );


    const average =
        Math.round(totalSalary / salaries.length);


    const highest =
        Math.max(...salaries);


    averageSalary.textContent =
        `₹${average.toLocaleString("en-IN")}`;


    highestSalary.textContent =
        `₹${highest.toLocaleString("en-IN")}`;
}


// ==========================================
// ADD EMPLOYEE
// ==========================================

async function addEmployee() {

    const empId =
        Number(prompt("Enter Employee ID:"));


    if (!empId) {
        return;
    }


    const existingEmployee =
        employees.some(
            employee => employee.empId === empId
        );


    if (existingEmployee) {

        alert("Employee with this ID already exists.");

        return;
    }


    const name =
        prompt("Enter Employee Name:");


    if (!name || name.trim() === "") {
        return;
    }


    const deptId =
        Number(
            prompt(
                "Enter Department ID:\n\n" +
                "1011 - IT\n" +
                "1012 - Sales\n" +
                "1013 - HR\n" +
                "1014 - Finance\n" +
                "1015 - Marketing"
            )
        );


    if (!isValidDepartment(deptId)) {

        alert("Invalid Department ID.");

        return;
    }


    const salary =
        Number(prompt("Enter Salary:"));


    if (!salary || salary < 0) {

        alert("Invalid salary.");

        return;
    }


    const newEmployee = {

        empId: empId,

        name: name.trim(),

        deptId: deptId,

        salary: salary
    };


    try {

        const response = await fetch(
            `${API_URL}/employees`,
            {
                method: "POST",

                headers: {
                    "Content-Type": "application/json"
                },

                body: JSON.stringify(newEmployee)
            }
        );


        if (!response.ok) {

            throw new Error(
                "Failed to add employee"
            );
        }


        alert("Employee added successfully.");

        await loadEmployees();


    } catch (error) {

        console.error(error);

        alert(
            "Unable to add employee. Check the backend."
        );
    }
}


// ==========================================
// EDIT EMPLOYEE
// ==========================================

async function editEmployee(id) {

    const employee =
        employees.find(
            employee => employee.empId === id
        );


    if (!employee) {
        return;
    }


    const name =
        prompt(
            "Enter Employee Name:",
            employee.name
        );


    if (!name || name.trim() === "") {
        return;
    }


    const deptId =
        Number(
            prompt(
                "Enter Department ID:\n\n" +
                "1011 - IT\n" +
                "1012 - Sales\n" +
                "1013 - HR\n" +
                "1014 - Finance\n" +
                "1015 - Marketing",

                employee.deptId
            )
        );


    if (!isValidDepartment(deptId)) {

        alert("Invalid Department ID.");

        return;
    }


    const salary =
        Number(
            prompt(
                "Enter Salary:",
                employee.salary
            )
        );


    if (!salary || salary < 0) {

        alert("Invalid salary.");

        return;
    }


    const updatedEmployee = {

        empId: id,

        name: name.trim(),

        deptId: deptId,

        salary: salary
    };


    try {

        const response = await fetch(
            `${API_URL}/employees/${id}`,
            {
                method: "PUT",

                headers: {
                    "Content-Type": "application/json"
                },

                body: JSON.stringify(updatedEmployee)
            }
        );


        if (!response.ok) {

            throw new Error(
                "Failed to update employee"
            );
        }


        alert(
            "Employee details updated successfully."
        );


        await loadEmployees();


    } catch (error) {

        console.error(error);

        alert(
            "Unable to update employee. Check the backend."
        );
    }
}


// ==========================================
// DELETE EMPLOYEE
// ==========================================

async function deleteEmployee(id) {

    const employee =
        employees.find(
            employee => employee.empId === id
        );


    if (!employee) {
        return;
    }


    const confirmation =
        confirm(
            `Are you sure you want to delete ${employee.name}?`
        );


    if (!confirmation) {
        return;
    }


    try {

        const response = await fetch(
            `${API_URL}/employees/${id}`,
            {
                method: "DELETE"
            }
        );


        if (!response.ok) {

            throw new Error(
                "Failed to delete employee"
            );
        }


        alert(
            "Employee deleted successfully."
        );


        await loadEmployees();


    } catch (error) {

        console.error(error);

        alert(
            "Unable to delete employee. Check the backend."
        );
    }
}


// ==========================================
// SEARCH
// ==========================================

searchInput.addEventListener(
    "input",
    renderEmployees
);


// ==========================================
// DEPARTMENT FILTER
// ==========================================

departmentFilter.addEventListener(
    "change",
    renderEmployees
);


// ==========================================
// ADD BUTTON
// ==========================================

addEmployeeBtn.addEventListener(
    "click",
    addEmployee
);


// ==========================================
// HELPER FUNCTIONS
// ==========================================

function getInitials(name) {

    const words =
        name.trim().split(" ");


    if (words.length === 1) {

        return words[0][0]
            .toUpperCase();
    }


    return (
        words[0][0] +
        words[words.length - 1][0]
    ).toUpperCase();
}


function getDepartmentClass(department) {

    return department
        .toLowerCase();
}


function isValidDepartment(deptId) {

    const validDepartments = [
        1011,
        1012,
        1013,
        1014,
        1015
    ];

    return validDepartments.includes(deptId);
}


function showLoading(show) {

    if (!loadingMessage) {
        return;
    }

    loadingMessage.style.display =
        show ? "block" : "none";
}


function showError(message) {

    if (!errorMessage) {
        return;
    }

    errorMessage.textContent =
        message;

    errorMessage.style.display =
        message ? "block" : "none";
}


// Prevent HTML injection when displaying names/data

function escapeHTML(value) {

    return String(value)
        .replace(/&/g, "&amp;")
        .replace(/</g, "&lt;")
        .replace(/>/g, "&gt;")
        .replace(/"/g, "&quot;")
        .replace(/'/g, "&#039;");
}


// ==========================================
// START APPLICATION
// ==========================================

loadEmployees();