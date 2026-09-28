CC      ?= cc
CFLAGS  ?= -std=c11 -Wall -Wextra -Wpedantic -Werror -O2
CLANG_FORMAT ?= clang-format
SANITIZE = -fsanitize=address,undefined -fno-omit-frame-pointer -g

BIN      = employee-records
SOURCES  = src/employee_table.c
HEADERS  = src/employee_table.h

.PHONY: all test format format-check clean

all: $(BIN)

$(BIN): src/main.c $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) -o $@ src/main.c $(SOURCES)

# Tests always run under AddressSanitizer and UBSan: memory bugs fail the build.
test: tests/test_employee_table.c $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) $(SANITIZE) -o tests/run_tests tests/test_employee_table.c $(SOURCES)
	./tests/run_tests

format:
	$(CLANG_FORMAT) -i src/*.c src/*.h tests/*.c

format-check:
	$(CLANG_FORMAT) --dry-run --Werror src/*.c src/*.h tests/*.c

clean:
	rm -f $(BIN) tests/run_tests
