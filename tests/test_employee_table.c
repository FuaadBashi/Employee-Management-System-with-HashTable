#include "../src/employee_table.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int failures = 0;

#define CHECK(condition)                                                                           \
    do {                                                                                           \
        if (!(condition)) {                                                                        \
            fprintf(stderr, "%s:%d: CHECK failed: %s\n", __FILE__, __LINE__, #condition);          \
            failures++;                                                                            \
        }                                                                                          \
    } while (0)

static Employee make(const char *name, char position, int id) {
    Employee e = {0};
    snprintf(e.name, sizeof e.name, "%s", name);
    e.position = position;
    e.id = id;
    e.years_experience = 3;
    e.age = 30;
    return e;
}

static void an_inserted_employee_can_be_found_by_name(void) {
    EmployeeTable *t = table_create();
    Employee alice = make("Alice", 'M', 1);

    CHECK(table_insert(t, &alice) == INSERT_OK);

    const Employee *found = table_find(t, "Alice");
    CHECK(found != NULL && found->id == 1 && found->position == 'M');
    CHECK(table_find(t, "Bob") == NULL);
    table_destroy(t);
}

static void the_table_keeps_its_own_copy_of_each_record(void) {
    EmployeeTable *t = table_create();
    Employee temp = make("Alice", 'M', 1);
    table_insert(t, &temp);

    /* Reusing the caller's buffer must not change the stored record. */
    temp = make("Mallory", 'W', 99);

    const Employee *found = table_find(t, "Alice");
    CHECK(found != NULL && found->id == 1);
    table_destroy(t);
}

static void a_duplicate_name_is_rejected_even_from_a_different_buffer(void) {
    EmployeeTable *t = table_create();
    Employee first = make("Alice", 'M', 1);
    char other_buffer[EMPLOYEE_NAME_MAX];
    strcpy(other_buffer, "Alice");
    Employee second = make(other_buffer, 'W', 2);

    table_insert(t, &first);

    CHECK(table_insert(t, &second) == INSERT_DUPLICATE);
    CHECK(table_size(t) == 1);
    table_destroy(t);
}

static void the_table_grows_and_keeps_every_record(void) {
    EmployeeTable *t = table_create();
    size_t initial_buckets = table_bucket_count(t);

    for (int i = 0; i < 1000; ++i) {
        char name[32];
        snprintf(name, sizeof name, "employee-%d", i);
        Employee e = make(name, "BMW"[i % 3], i);
        CHECK(table_insert(t, &e) == INSERT_OK);
    }

    CHECK(table_size(t) == 1000);
    CHECK(table_bucket_count(t) > initial_buckets);
    CHECK(table_size(t) * 4 <= table_bucket_count(t) * 3);
    for (int i = 0; i < 1000; ++i) {
        char name[32];
        snprintf(name, sizeof name, "employee-%d", i);
        const Employee *found = table_find(t, name);
        CHECK(found != NULL && found->id == i);
    }
    table_destroy(t);
}

static void a_removed_employee_is_gone_and_others_remain(void) {
    EmployeeTable *t = table_create();
    Employee a = make("Alice", 'M', 1), b = make("Bob", 'W', 2);
    table_insert(t, &a);
    table_insert(t, &b);

    CHECK(table_remove(t, "Alice"));
    CHECK(!table_remove(t, "Alice"));

    CHECK(table_find(t, "Alice") == NULL);
    CHECK(table_find(t, "Bob") != NULL);
    CHECK(table_size(t) == 1);
    table_destroy(t);
}

static void count_position(const Employee *e, void *context) {
    if (e->position == 'W') {
        ++*(int *)context;
    }
}

static void every_record_is_visited_exactly_once(void) {
    EmployeeTable *t = table_create();
    Employee a = make("Alice", 'M', 1), b = make("Bob", 'W', 2), c = make("Cara", 'W', 3);
    table_insert(t, &a);
    table_insert(t, &b);
    table_insert(t, &c);

    int workers = 0;
    table_for_each(t, count_position, &workers);

    CHECK(workers == 2);
    table_destroy(t);
}

static void only_b_m_and_w_are_positions(void) {
    CHECK(position_is_valid('B') && position_is_valid('M') && position_is_valid('W'));
    CHECK(!position_is_valid('X') && !position_is_valid('b'));
}

int main(void) {
    an_inserted_employee_can_be_found_by_name();
    the_table_keeps_its_own_copy_of_each_record();
    a_duplicate_name_is_rejected_even_from_a_different_buffer();
    the_table_grows_and_keeps_every_record();
    a_removed_employee_is_gone_and_others_remain();
    every_record_is_visited_exactly_once();
    only_b_m_and_w_are_positions();

    if (failures > 0) {
        fprintf(stderr, "%d check(s) failed\n", failures);
        return EXIT_FAILURE;
    }
    printf("All tests passed\n");
    return EXIT_SUCCESS;
}
