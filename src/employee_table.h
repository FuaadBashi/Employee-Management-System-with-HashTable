#ifndef EMPLOYEE_TABLE_H
#define EMPLOYEE_TABLE_H

#include <stdbool.h>
#include <stddef.h>

#define EMPLOYEE_NAME_MAX 64

typedef struct {
    char name[EMPLOYEE_NAME_MAX];
    char position; /* 'B', 'M' or 'W' */
    int id;
    int years_experience;
    int age;
} Employee;

/*
 * A hash table of employees keyed by name, using separate chaining.
 *
 * The table stores its own copy of every record, so callers may pass pointers to temporaries.
 * Storing the caller's pointer was the original bug: records pointed at stack memory that was
 * gone by the time they were read.
 */
typedef struct EmployeeTable EmployeeTable;

EmployeeTable *table_create(void);
void table_destroy(EmployeeTable *table);

typedef enum { INSERT_OK, INSERT_DUPLICATE, INSERT_NO_MEMORY } InsertResult;

InsertResult table_insert(EmployeeTable *table, const Employee *employee);
const Employee *table_find(const EmployeeTable *table, const char *name);
bool table_remove(EmployeeTable *table, const char *name);
size_t table_size(const EmployeeTable *table);
size_t table_bucket_count(const EmployeeTable *table);

/* Calls visit for every employee, in no particular order. */
void table_for_each(const EmployeeTable *table, void (*visit)(const Employee *, void *),
                    void *context);

bool position_is_valid(char position);

#endif /* EMPLOYEE_TABLE_H */
