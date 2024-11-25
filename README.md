# Employee-Management-System-with-HashTable
A simple Employee Management System built in C, utilizing a Hash Table to efficiently store and manage employee data. The system allows adding employees, viewing all records, and searching by name or position. It demonstrates dynamic memory management and hash table implementation in C for organisational purposes.

```markdown
# Employee Management System with Hash Table

## Overview

This project implements a simple Employee Management System using a Hash Table to store and manage employee data. It allows users to add, view, and search for employees based on various criteria such as name and position.

## Features

- **Add Employee**: Allows users to add new employee details such as name, position, ID, experience, and age.
- **View All Employees**: Displays a list of all employees stored in the system.
- **Search by Name**: Allows users to search for employees by their name.
- **Search by Position**: Allows users to search for employees by their position (e.g., 'B', 'M', 'W').

## Technologies Used

- **C Programming Language**
- **Hash Table Data Structure** for efficient storage and retrieval of employee data
- **Dynamic Memory Allocation** to handle employee data

## File Structure

```bash
.
├── employee.c            # Contains the implementation of the employee structure and functions
├── hashtable.c           # Contains the implementation of the hash table structure and functions
├── hashtable.h           # Header file defining the hash table and employee structures
└── main.c                # Main program with terminal UI
```

## Setup and Installation

### Prerequisites

To run this project, you will need:

- A C compiler such as GCC.
- Basic understanding of C and hash table data structures.

### Steps to Run the Project

1. Clone the repository to your local machine:
    ```bash
    git clone https://github.com/yourusername/employee-management-system.git
    cd employee-management-system
    ```

2. Compile the project:
    ```bash
    gcc -o employee_management main.c hashtable.c employee.c
    ```

3. Run the program:
    ```bash
    ./employee_management
    ```

### Example Usage

Once the program is running, the user will be prompted with a menu to interact with the system.

- **Add Employee**: Enter the details of a new employee.
- **View All Employees**: View a list of all employees in the system.
- **Search Employee by Name**: Search for an employee by their name.
- **Search Employee by Position**: Search for employees based on their position (e.g., 'B', 'M', 'W').

## Example Output

```bash
===== Employee Management System =====
1. Add Employee
2. View All Employees
3. Search Employee by Name
4. Search Employee by Position
5. Exit
======================================
Please select an option: 1

Enter employee name: Fuaad
Enter employee position (B/M/W): B
Enter employee ID: 1
Enter employee experience (years): 5
Enter employee age: 30

Employee added successfully!

===== Employee Management System =====
1. Add Employee
2. View All Employees
3. Search Employee by Name
4. Search Employee by Position
5. Exit
======================================
Please select an option: 2

===== Employee Records =====
0: Fuaad -> 
1: Felix -> 
2: Feysal -> 
3: Yonis -> 
```


## Contact

For any inquiries, please contact me at: fbshurie@hotmail.com
```
