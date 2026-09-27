# Employee Records with a Hash Table

A C data-structures project that stores employee records in a hash table and provides a console menu to add records, list employees, and search by name or position.

## Run locally

Requires a C compiler.

```bash
git clone https://github.com/FuaadBashi/Employee-Management-System-with-HashTable.git
cd Employee-Management-System-with-HashTable
cd EmployeesManagmentSysten
cc main.c -o employee-records
./employee-records
```

`main.c` includes `employee.c` directly, so compile the entry point alone. The directory spelling above matches the repository.

## Code to explore

- [hashtable.h](EmployeesManagmentSysten/hashtable.h): buckets and hash-table operations.
- [employee.c](EmployeesManagmentSysten/employee.c): employee representation.
- [main.c](EmployeesManagmentSysten/main.c): menu, insertion, traversal, and cleanup.

Name and position searches in the menu traverse the buckets; they should not be presented as constant-time lookups. This is an educational implementation with console input handling that needs hardening before use with untrusted data.
