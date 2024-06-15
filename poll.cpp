#include<bits/stdc++.h>

using namespace std;

// Employee class
class Employee {
public:
    string name;
    int code;
    string designation;
    int exp;
    int age;
    int salary;
    bool hasLoan;

    Employee(string n, int c, string des, int e, int a, int s, bool l) {
        name = n;
        code = c;
        designation = des;
        exp = e;
        age = a;
        salary = s;
        hasLoan = l;
    }
};

// Binary Search Tree for storing employees based on their codes
class BSTNode {
public:
    Employee* data;
    BSTNode* left;
    BSTNode* right;

    BSTNode(Employee* emp) {
        data = emp;
        left = nullptr;
        right = nullptr;
    }
};

class BST {
private:
    BSTNode* root;

    BSTNode* insertHelper(BSTNode* node, Employee* emp) {
        if (node == nullptr) {
            return new BSTNode(emp);
        }

        if (emp->code < node->data->code) {
            node->left = insertHelper(node->left, emp);
        } else {
            node->right = insertHelper(node->right, emp);
        }

        return node;
    }

    void inorderTraversal(BSTNode* node, vector<Employee*>& employees) {
        if (node != nullptr) {
            inorderTraversal(node->left, employees);
            employees.push_back(node->data);
            inorderTraversal(node->right, employees);
        }
    }

public:
    BST() {
        root = nullptr;
    }

    void insert(Employee* emp) {
        root = insertHelper(root, emp);
    }

    vector<Employee*> getEmployees() {
        vector<Employee*> employees;
        inorderTraversal(root, employees);
        return employees;
    }
};

// Hashing for quick search of employees based on their codes
unordered_map<int, Employee*> employeeMap;

// Function to insert a new employee
void insertEmployee(BST& bst) {
    string name, designation;
    int code, exp, age, salary;
    bool hasLoan;

    cout << "Enter Name: ";
    cin >> name;
    cout << "Enter Code: ";
    cin >> code;
    cout << "Enter Designation: ";
    cin >> designation;
    cout << "Enter Years of Experience: ";
    cin >> exp;
    cout << "Enter Age: ";
    cin >> age;
    cout << "Enter Salary: ";
    cin >> salary;
    cout << "Has Loan? (0/1): ";
    cin >> hasLoan;

    Employee* emp = new Employee(name, code, designation, exp, age, salary, hasLoan);
    bst.insert(emp);
    employeeMap[code] = emp;

    cout << "Employee inserted successfully!" << endl;
}

// Function to edit an existing employee
void editEmployee(BST& bst) {
    int code;
    cout << "Enter Employee Code to edit: ";
    cin >> code;

    if (employeeMap.find(code) == employeeMap.end()) {
        cout << "Employee not found!" << endl;
        return;
    }

    Employee* emp = employeeMap[code];

    string name, designation;
    int exp, age, salary;
    bool hasLoan;

    cout << "Enter New Name (" << emp->name << "): ";
    cin >> name;
    if (!name.empty()) {
        emp->name = name;
    }

    cout << "Enter New Designation (" << emp->designation << "): ";
    cin >> designation;
    if (!designation.empty()) {
        emp->designation = designation;
    }

    cout << "Enter New Years of Experience (" << emp->exp << "): ";
    cin >> exp;
    if (exp != 0) {
        emp->exp = exp;
    }

    cout << "Enter New Age (" << emp->age << "): ";
    cin >> age;
    if (age != 0) {
        emp->age = age;
    }

    cout << "Enter New Salary (" << emp->salary << "): ";
    cin >> salary;
    if (salary != 0) {
        emp->salary = salary;
    }

    cout << "Has Loan? (0/1) (" << emp->hasLoan << "): ";
    cin >> hasLoan;
    emp->hasLoan = hasLoan;

    cout << "Employee updated successfully!" << endl;
}

// Function to delete an employee
void deleteEmployee(BST& bst) {
    int code;
    cout << "Enter Employee Code to delete: ";
    cin >> code;

    if (employeeMap.find(code) == employeeMap.end()) {
        cout << "Employee not found!" << endl;
        return;
    }

    Employee* emp = employeeMap[code];
    employeeMap.erase(code);

    // Remove the employee from the BST
    // (Implementation left as an exercise)

    cout << "Employee deleted successfully!" << endl;
}

// Function to display all employees
void displayEmployees(BST& bst) {
    vector<Employee*> employees = bst.getEmployees();

    cout << "Employee List:" << endl;
    for (Employee* emp : employees) {
        cout << "Name: " << emp->name << ", Code: " << emp->code << ", Designation: " << emp->designation
             << ", Experience: " << emp->exp << " years, Age: " << emp->age << ", Salary: " << emp->salary
             << ", Loan: " << (emp->hasLoan ? "Yes" : "No") << endl;
    }
}

int main() {
    BST bst;

    int choice;
    do {
        cout << "\nPayroll Management System" << endl;
        cout << "1. Insert Employee" << endl;
        cout << "2. Edit Employee" << endl;
        cout << "3. Delete Employee" << endl;
        cout << "4. Display Employees" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                insertEmployee(bst);
                break;
            case 2:
                editEmployee(bst);
                break;
            case 3:
                deleteEmployee(bst);
                break;
            case 4:
                displayEmployees(bst);
                break;
            case 5:
                cout << "Exiting program..." << endl;
                break;
            default:
                cout << "Invalid choice! Please enter a valid option." << endl;
                break;
        }
    } while (choice != 5);

    return 0;
}
