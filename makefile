CC = gcc
CFLAGS = -Wall -Wextra -DSTANDALONE_MEMORY_ALLOCATION -DMEMORY_ALLOCATION_VERBOSE_OUTPUT

# Target: build
build: lowlevel/mem.c
	$(CC) $(CFLAGS) -o mem.out lowlevel/*.c

# Target: build-test
build-test: CFLAGS += -DAUTOMATED_TESTING_MEMORY_ALLOCATION
build-test: CFLAGS := $(filter-out -DMEMORY_ALLOCATION_VERBOSE_OUTPUT,$(CFLAGS))
build-test: lowlevel/*.c test/*.c
	$(CC) $(CFLAGS) -o test.out lowlevel/*.c test/*.c

# Target: run-test
run-test: build-test
	./test.out

# Target: run
run:
	./mem.out

# Target: clean
clean:
	rm -f mem.out test.out

.PHONY: build build-test run-test clean

