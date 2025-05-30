/*         UNIVERSITY OF GONDAR
          COLLEGE OF INFORMATICS
	  DEPARTMENT OF COMPUTER SCIENCE
        PROGRAMMING PROJECT FOR SECOND YEAR STUDENT
     STUDENT ID              STUDENT NAME
	 GUR/01575/15            Eyerusalem Tsegaye
	 GUR/01753/15            Kalkidan Zemedkun
	 GUR/01623/15            Ketsebaot Tariku
	 GUR/02368/15            Kidest  Chombe
	  
	  
	                                             submitted to Mr. Kibret.Z  
	                                             submission date Jan 7,2025
	                                        
*/

/*INTRODUCTION
This C++ program implements an Employee Management System , allowing for the addition, display, and file storage of employee data for
those who works in college of informatics.It defines a structure to store essential employee details such as ID, name, age, salary, 
managerial status, and department.The program supports functionality to filter and display employees based on their department, 
along with options to save and load data from a binary file.Overall, it facilitates efficient management of employee records, 
enhancing usability for administrative tasks in any organization.*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Define a structure for Employee
struct Employee {
    int id;
    string name;
    int age;
    double salary;
    bool isManager;
    string department;
};

const int MAX_EMPLOYEES = 100; // Maximum number of employees
Employee employees[MAX_EMPLOYEES]; // Array to store employee data
int employeeCount = 0; // To keep track of the number of employees

// Function to input employee data
void inputEmployeeData() {
    if (employeeCount >= MAX_EMPLOYEES) {
        cout << "Maximum number of employees reached!" << endl;
        return;
    }

    Employee emp;
    cout << "Enter employee ID: ";
    cin >> emp.id;
    cin.ignore(); // To clear the newline character left in the buffer
    cout << "Enter employee name: ";
    getline(cin, emp.name);
    cout << "Enter employee age: ";
    cin >> emp.age;
    cout << "Enter employee salary: ";
    cin >> emp.salary;
    cout << "Is the employee a manager (1 for Yes, 0 for No): ";
    cin >> emp.isManager;
    cin.ignore(); // Clear the buffer again
    cout << "Enter employee department: ";
    getline(cin, emp.department);

    // Add the employee to the array
    employees[employeeCount] = emp;
    employeeCount++;
}

// Function to display employee data
void displayEmployee(const Employee& emp) {
    cout << "Employee ID: " << emp.id << "\t";
    cout << "Name: " << emp.name << "\t";
    cout << "Age: " << emp.age << "\t";
    cout << "Salary: $" << emp.salary << "\t";
    cout << "Manager: " << (emp.isManager ? "Yes" : "No") << "\t";
    cout << "Department: " << emp.department << endl;
}

// Function to display all employees
void displayAllEmployees() {
    if (employeeCount == 0) {
        cout << "No employees to display." << endl;
        return;
    }

    cout << "Employee List:\n";
    for (int i = 0; i < employeeCount; i++) {
        displayEmployee(employees[i]); 
    }
}

// Function to save employee data to a file
void saveEmployeesToFile(const string& filename) {
    ofstream file(filename, ios::binary);
    if (!file) {
        cerr << "Error opening file for writing." << endl;
        return;
    }

    for (int i = 0; i < employeeCount; i++) {
        file.write(reinterpret_cast<const char*>(&employees[i]), sizeof(Employee));
    }

    file.close();
    cout << "Employees saved to file." << endl;
}

// Function to read employee data from a file
void loadEmployeesFromFile(const string& filename) {
    ifstream file(filename, ios::binary);
    if (!file) {
        cout << "No existing file found. Starting fresh." << endl;
        return;
    }

    while (file.read(reinterpret_cast<char*>(&employees[employeeCount]), sizeof(Employee))) {
        employeeCount++;
    }

    file.close();
}

// Function to display employees in a specific department
void displayEmployeesInDepartment(const string& department) {
    bool found = false;
    cout << "Employees in " << department << " department:\n"; 
    for (int i = 0; i < employeeCount; i++) {
        if (employees[i].department == department) {
            displayEmployee(employees[i]);
            found = true;
        }
    }
    if (!found) {
        cout << "No employees found in the " << department << " department." << endl;
    }
}

// Function to display employees within a specific salary range
void displayEmployeesBySalaryRange(double lowerBound, double upperBound) {
    bool found = false;
    cout << "Employees with salary between $" << lowerBound << " and $" << upperBound << ":\n";
    for (int i = 0; i < employeeCount; i++) {
        if (employees[i].salary >= lowerBound && employees[i].salary <= upperBound) { 
            displayEmployee(employees[i]);
            found = true;
        }
    }
    if (!found) {
        cout << "No employees found in the specified salary range." << endl;
    }
}
// Function to display manager employees
void displayManagerEmployees() {
    bool found = false;
    cout << "Managerial Employees:\n";
    for (int i = 0; i < employeeCount; i++) {
        if (employees[i].isManager) {
            displayEmployee(employees[i]);
            found = true;
        }
    }
    if (!found) {
        cout << "No managers found in the company." << endl;
    }
}

int main() {
    string filename = "employees.dat";

    // Load employees from the file if it exists
    loadEmployeesFromFile(filename);

    int choice;
    do {
        cout << "\nEmployee Management System" << endl;
        cout << "1. Add Employee" << endl;
        cout << "2. Display Employees in a Department" << endl;
        cout << "3. Display All Employees" << endl;
        cout << "4. Display Employees by Salary Range" << endl; 
        cout << "5. Display Manager Employees" << endl; // Added option for displaying managers
        cout << "6. Save Employees to File" << endl;
        cout << "7. Load Employees from File" << endl;
        cout << "8. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                inputEmployeeData();
                break;
            case 2: {
                string department;
                cin.ignore(); // To clear the buffer
                cout << "Enter department name: ";
                getline(cin, department);
                displayEmployeesInDepartment(department);
                break;
            }
            case 3:
                displayAllEmployees(); 
                break;
            case 4: {
                double lowerBound, upperBound;
                cout << "Enter lower bound of salary: ";
                cin >> lowerBound;
                cout << "Enter upper bound of salary: ";
                cin >> upperBound;
                displayEmployeesBySalaryRange(lowerBound, upperBound);
                break;
            }
            case 5:
                displayManagerEmployees(); // Added case for displaying managers
                break;
            case 6:
                saveEmployeesToFile(filename);
                break;
            case 7:
                loadEmployeesFromFile(filename);
                cout << "Employees loaded from file." << endl;
                break;
            case 8:
                cout << "Exiting program." << endl;
                break;
            default:
                cout << "Invalid choice, please try again." << endl;
        }
    } while (choice != 8);

    return 0;
}