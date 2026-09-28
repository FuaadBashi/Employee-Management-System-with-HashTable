#include "employee_table.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_BUCKETS 8
/* Grow when the average chain would exceed 3/4 of an entry, keeping lookups O(1) on average. */
#define MAX_LOAD_NUMERATOR 3
#define MAX_LOAD_DENOMINATOR 4

typedef struct Node {
    Employee employee;
    struct Node *next;
} Node;

struct EmployeeTable {
    Node **buckets;
    size_t bucket_count;
    size_t size;
};

/* 32-bit FNV-1a: simple, fast, and spreads similar names well. */
static uint32_t hash_name(const char *name) {
    uint32_t hash = 2166136261u;
    for (const unsigned char *p = (const unsigned char *)name; *p != '\0'; ++p) {
        hash ^= *p;
        hash *= 16777619u;
    }
    return hash;
}

static size_t bucket_for(const char *name, size_t bucket_count) {
    return hash_name(name) % bucket_count;
}

EmployeeTable *table_create(void) {
    EmployeeTable *table = malloc(sizeof *table);
    if (table == NULL) {
        return NULL;
    }
    table->buckets = calloc(INITIAL_BUCKETS, sizeof *table->buckets);
    if (table->buckets == NULL) {
        free(table);
        return NULL;
    }
    table->bucket_count = INITIAL_BUCKETS;
    table->size = 0;
    return table;
}

void table_destroy(EmployeeTable *table) {
    if (table == NULL) {
        return;
    }
    for (size_t i = 0; i < table->bucket_count; ++i) {
        Node *node = table->buckets[i];
        while (node != NULL) {
            Node *next = node->next;
            free(node);
            node = next;
        }
    }
    free(table->buckets);
    free(table);
}

static bool grow(EmployeeTable *table) {
    size_t new_count = table->bucket_count * 2;
    Node **new_buckets = calloc(new_count, sizeof *new_buckets);
    if (new_buckets == NULL) {
        return false;
    }
    for (size_t i = 0; i < table->bucket_count; ++i) {
        Node *node = table->buckets[i];
        while (node != NULL) {
            Node *next = node->next;
            size_t b = bucket_for(node->employee.name, new_count);
            node->next = new_buckets[b];
            new_buckets[b] = node;
            node = next;
        }
    }
    free(table->buckets);
    table->buckets = new_buckets;
    table->bucket_count = new_count;
    return true;
}

InsertResult table_insert(EmployeeTable *table, const Employee *employee) {
    if (table_find(table, employee->name) != NULL) {
        return INSERT_DUPLICATE;
    }
    if ((table->size + 1) * MAX_LOAD_DENOMINATOR > table->bucket_count * MAX_LOAD_NUMERATOR) {
        /* A failed resize is not fatal: the table still works, just with longer chains. */
        (void)grow(table);
    }

    Node *node = malloc(sizeof *node);
    if (node == NULL) {
        return INSERT_NO_MEMORY;
    }
    node->employee = *employee;
    node->employee.name[EMPLOYEE_NAME_MAX - 1] = '\0';

    size_t b = bucket_for(node->employee.name, table->bucket_count);
    node->next = table->buckets[b];
    table->buckets[b] = node;
    table->size++;
    return INSERT_OK;
}

const Employee *table_find(const EmployeeTable *table, const char *name) {
    /* Compare contents with strcmp: comparing the pointers never matched a different buffer. */
    for (const Node *node = table->buckets[bucket_for(name, table->bucket_count)]; node != NULL;
         node = node->next) {
        if (strcmp(node->employee.name, name) == 0) {
            return &node->employee;
        }
    }
    return NULL;
}

bool table_remove(EmployeeTable *table, const char *name) {
    Node **link = &table->buckets[bucket_for(name, table->bucket_count)];
    while (*link != NULL) {
        if (strcmp((*link)->employee.name, name) == 0) {
            Node *doomed = *link;
            *link = doomed->next;
            free(doomed);
            table->size--;
            return true;
        }
        link = &(*link)->next;
    }
    return false;
}

size_t table_size(const EmployeeTable *table) {
    return table->size;
}

size_t table_bucket_count(const EmployeeTable *table) {
    return table->bucket_count;
}

void table_for_each(const EmployeeTable *table, void (*visit)(const Employee *, void *),
                    void *context) {
    for (size_t i = 0; i < table->bucket_count; ++i) {
        for (const Node *node = table->buckets[i]; node != NULL; node = node->next) {
            visit(&node->employee, context);
        }
    }
}

bool position_is_valid(char position) {
    return position == 'B' || position == 'M' || position == 'W';
}
