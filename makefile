CC = gcc
CFLAGS = -Wall -Wextra

# Target: build
build: mem.c
	$(CC) $(CFLAGS) -o mem.out mem.c

# Target: build-test
build-test: CFLAGS += -DTEST_CASES_VISUAL -DTEST_CASE_MEMORY_ALLOC -DMEMORY_ALLOCATION_LOGGING
build-test: mem.c test.c
	$(CC) $(CFLAGS) -o test.out mem.c test.c

# Target: run-test
run-test: build-test
	./test
# Target: run
run:
	./mem

# Target: clean
clean:
	rm -f mem test

.PHONY: build build-test run-test clean
