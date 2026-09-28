#include "employee_table.h"

#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_MAX_LEN 128

/*
 * Reads one line into buffer without the newline. Returns false at end of input.
 * Line-based input replaces scanf, which looped forever on a non-numeric menu choice and
 * overflowed on long names.
 */
static bool read_line(const char *prompt, char *buffer, size_t size) {
    printf("%s", prompt);
    fflush(stdout);
    if (fgets(buffer, (int)size, stdin) == NULL) {
        return false;
    }
    size_t len = strcspn(buffer, "\n");
    if (buffer[len] != '\n' && !feof(stdin)) {
        /* Discard the rest of an over-long line so it doesn't answer the next prompt. */
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {
        }
    }
    buffer[len] = '\0';
    return true;
}

static bool read_int(const char *prompt, int min, int max, int *out) {
    char line[LINE_MAX_LEN];
    for (;;) {
        if (!read_line(prompt, line, sizeof line)) {
            return false;
        }
        char *end;
        errno = 0;
        long value = strtol(line, &end, 10);
        if (end != line && *end == '\0' && errno == 0 && value >= min && value <= max) {
            *out = (int)value;
            return true;
        }
        printf("Please enter a whole number from %d to %d.\n", min, max);
    }
}

static bool read_position(const char *prompt, char *out) {
    char line[LINE_MAX_LEN];
    for (;;) {
        if (!read_line(prompt, line, sizeof line)) {
            return false;
        }
        char position = (char)toupper((unsigned char)line[0]);
        if (strlen(line) == 1 && position_is_valid(position)) {
            *out = position;
            return true;
        }
        printf("Please enter B, M or W.\n");
    }
}

static void print_employee(const Employee *e, void *context) {
    (void)context;
    printf("  %-20s  %c  ID %-6d  %2d years' experience  age %d\n", e->name, e->position, e->id,
           e->years_experience, e->age);
}

typedef struct {
    char position;
    int matches;
} PositionFilter;

static void print_if_position(const Employee *e, void *context) {
    PositionFilter *filter = context;
    if (e->position == filter->position) {
        print_employee(e, NULL);
        filter->matches++;
    }
}

static bool add_employee(EmployeeTable *table) {
    Employee e = {0};
    if (!read_line("Name: ", e.name, sizeof e.name)) {
        return false;
    }
    if (e.name[0] == '\0') {
        printf("A name is required.\n");
        return true;
    }
    if (!read_position("Position (B/M/W): ", &e.position) || !read_int("ID: ", 0, INT_MAX, &e.id) ||
        !read_int("Years of experience: ", 0, 80, &e.years_experience) ||
        !read_int("Age: ", 16, 120, &e.age)) {
        return false;
    }

    switch (table_insert(table, &e)) {
    case INSERT_OK:
        printf("Added %s.\n", e.name);
        break;
    case INSERT_DUPLICATE:
        printf("%s is already on record.\n", e.name);
        break;
    case INSERT_NO_MEMORY:
        printf("Out of memory.\n");
        break;
    }
    return true;
}

int main(void) {
    EmployeeTable *table = table_create();
    if (table == NULL) {
        fprintf(stderr, "Out of memory.\n");
        return EXIT_FAILURE;
    }

    bool running = true;
    while (running) {
        printf("\n===== Employee Management System =====\n"
               "1. Add employee\n"
               "2. View all employees\n"
               "3. Find employee by name\n"
               "4. List employees by position\n"
               "5. Remove employee\n"
               "6. Exit\n");

        int option;
        if (!read_int("Select an option: ", 1, 6, &option)) {
            break;
        }

        char name[EMPLOYEE_NAME_MAX];
        switch (option) {
        case 1:
            running = add_employee(table);
            break;
        case 2:
            printf("%zu employee(s):\n", table_size(table));
            table_for_each(table, print_employee, NULL);
            break;
        case 3: {
            if (!read_line("Name: ", name, sizeof name)) {
                running = false;
                break;
            }
            const Employee *found = table_find(table, name);
            if (found != NULL) {
                print_employee(found, NULL);
            } else {
                printf("No employee named %s.\n", name);
            }
            break;
        }
        case 4: {
            PositionFilter filter = {0};
            if (!read_position("Position (B/M/W): ", &filter.position)) {
                running = false;
                break;
            }
            table_for_each(table, print_if_position, &filter);
            if (filter.matches == 0) {
                printf("No employees in position %c.\n", filter.position);
            }
            break;
        }
        case 5:
            if (!read_line("Name: ", name, sizeof name)) {
                running = false;
                break;
            }
            printf(table_remove(table, name) ? "Removed %s.\n" : "No employee named %s.\n", name);
            break;
        case 6:
            running = false;
            break;
        }
    }

    table_destroy(table);
    return EXIT_SUCCESS;
}
