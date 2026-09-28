# Employee Records — Hash Table in C

[![CI](https://github.com/FuaadBashi/Employee-Management-System-with-HashTable/actions/workflows/ci.yml/badge.svg)](https://github.com/FuaadBashi/Employee-Management-System-with-HashTable/actions/workflows/ci.yml)

A console employee-records system in C, built on a hash table written from scratch. Add, find,
list, filter and remove employees; lookups by name take constant time on average however many
records there are.

## Highlights

- **Hash table from scratch.** FNV-1a string hashing, separate chaining, and automatic resizing:
  the bucket array doubles whenever the load factor would pass 0.75, so chains stay short.
- **Clear ownership.** The table stores its own copy of each record, and `table_destroy` frees
  everything it allocated. The API is an opaque `EmployeeTable *` with create, insert, find,
  remove, and a callback-based `for_each`.
- **Defensive input.** Every prompt reads a whole line with `fgets` and validates it with `strtol`,
  re-asking on bad input. Names may contain spaces and cannot overflow their buffer.
- **Memory-safe by construction and by test.** The test suite runs under AddressSanitizer and
  UndefinedBehaviorSanitizer in CI, and the build treats every warning as an error.

## Getting started

Requires a C11 compiler and `make`.

```bash
git clone https://github.com/FuaadBashi/Employee-Management-System-with-HashTable.git
cd Employee-Management-System-with-HashTable
make
./employee-records
```

Each employee has a name, a position code (`B`, `M` or `W`), an ID, years of experience and an
age. Names are unique.

## How it works

```
 name ──FNV-1a──▶ hash % bucket_count
                        │
 buckets: [0] ─▶ Alice ─▶ Omar ─▶ NULL
          [1] ─▶ NULL
          [2] ─▶ Bob ─▶ NULL
          ...
```

Inserting checks the chain for the name first, so duplicates are rejected. When
`size / bucket_count` would exceed 0.75, every node is rehashed into a table twice the size.
Finding by name walks one short chain. Listing by position visits every record, so it is O(n).

## Project structure

```
src/employee_table.h   public API
src/employee_table.c   hashing, chaining, resizing
src/main.c             menu and input validation
tests/                 unit tests
Makefile               build, test, format
```

## Tests

```bash
make test           # unit tests under ASan + UBSan
make format-check   # clang-format
```
