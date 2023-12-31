CC = gcc
CFLAGS = -Wall -Wextra -DSTANDALONE_MEMORY_ALLOCATION

# Target: build
build: mem.c
	$(CC) $(CFLAGS) -o mem.out mem.c

# Target: build-test
build-test: CFLAGS += -DAUTOMATED_TESTING_MEMORY_ALLOCATION
build-test: mem.c test/*.c
	$(CC) $(CFLAGS) -o test.out mem.c test/*.c

# Target: run-test
run-test: build-test
	./test.out

# Target: run
run:
	./mem.out

# Target: clean
clean:
	rm -f mem test

.PHONY: build build-test run-test clean

