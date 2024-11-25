
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "employee.c"
#include "hashtable.h"

// Function to display the main menu
void displayMenu() {
    printf("\n===== Employee Management System =====\n");
    printf("1. Add Employee\n");
    printf("2. View All Employees\n");
    printf("3. Search Employee by Name\n");
    printf("4. Search Employee by Position\n");
    printf("5. Exit\n");
    printf("======================================\n");
    printf("Please select an option: ");
}

// Function to handle adding an employee
void addEmployee(hashtable *ht) {
    employee newEmp;
    printf("\nEnter employee name: ");
    scanf("%s", newEmp.name);
    printf("Enter employee position (B/M/W): ");
    scanf(" %c", &newEmp.position); // Note the space before %c to consume any lingering newline
    printf("Enter employee ID: ");
    scanf("%d", &newEmp.id);
    printf("Enter employee experience (years): ");
    scanf("%d", &newEmp.exp);
    printf("Enter employee age: ");
    scanf("%d", &newEmp.age);

    // Insert employee into hash table
    if (ht->insertNode(ht, &newEmp)) {
        printf("\nEmployee added successfully!\n");
    } else {
        printf("\nError adding employee.\n");
    }
}

// Function to display all employees in the hash table
void viewAllEmployees(hashtable *ht) {
    printf("\n===== Employee Records =====\n");
    ht->printTable(ht);
}

// Function to search for an employee by name
void searchEmployeeByName(hashtable *ht) {
    char name[100];
    printf("\nEnter employee name to search: ");
    scanf("%s", name);

    bool found = false;
    for (int i = 0; i < TABLESIZE; ++i) {
        node *curr = ht->heads[i];
        while (curr != NULL) {
            if (strcmp(curr->e->name, name) == 0) {
                printf("\nEmployee Found:\n");
                printf("Name: %s, Position: %c, ID: %d, Experience: %d years, Age: %d\n",
                       curr->e->name, curr->e->position, curr->e->id, curr->e->exp, curr->e->age);
                found = true;
                break;
            }
            curr = curr->next;
        }
        if (found) break;
    }
    if (!found) {
        printf("\nEmployee not found.\n");
    }
}

// Function to search for employees by position
void searchEmployeeByPosition(hashtable *ht) {
    char position;
    printf("\nEnter employee position to search (B/M/W): ");
    scanf(" %c", &position);

    bool found = false;
    for (int i = 0; i < TABLESIZE; ++i) {
        node *curr = ht->heads[i];
        while (curr != NULL) {
            if (curr->e->position == position) {
                printf("\nEmployee Found:\n");
                printf("Name: %s, Position: %c, ID: %d, Experience: %d years, Age: %d\n",
                       curr->e->name, curr->e->position, curr->e->id, curr->e->exp, curr->e->age);
                found = true;
            }
            curr = curr->next;
        }
    }
    if (!found) {
        printf("\nNo employees found for position %c.\n", position);
    }
}

int main() {
    hashtable ht;
    initTable(&ht);

    bool running = true;
    while (running) {
        displayMenu();

        int option;
        scanf("%d", &option);

        switch (option) {
            case 1:
                addEmployee(&ht);
                break;
            case 2:
                viewAllEmployees(&ht);
                break;
            case 3:
                searchEmployeeByName(&ht);
                break;
            case 4:
                searchEmployeeByPosition(&ht);
                break;
            case 5:
                printf("\nExiting program...\n");
                running = false;
                break;
            default:
                printf("\nInvalid option. Please try again.\n");
                break;
        }
    }

    freeTable(&ht);
    return 0;
}


