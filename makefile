CC = gcc
CFLAGS = -Wall -Wextra -DSTANDALONE_MEMORY_ALLOCATION -DMEMORY_ALLOCATION_VERBOSE_OUTPUT
LIBNAME = libmem.a

# Source files
SRCDIR = lowlevel
SRCFILES = $(wildcard $(SRCDIR)/*.c)
OBJFILES = $(patsubst $(SRCDIR)/%.c, %.o, $(SRCFILES))

# Target: build
build: lowlevel/mem.c
	$(CC) $(CFLAGS) -o mem.out lowlevel/*.c

# Target: build-test
build-test: CFLAGS += -DAUTOMATED_TESTING_MEMORY_ALLOCATION
build-test: CFLAGS := $(filter-out -DMEMORY_ALLOCATION_VERBOSE_OUTPUT,$(CFLAGS))
build-test: $(OBJFILES) test/*.c
	$(CC) $(CFLAGS) -o test.out $(OBJFILES) test/*.c

# Target: run-test
run-test: build-test
	./test.out

# Target: run
run: $(LIBNAME) main.c
	$(CC) $(CFLAGS) -o mem.out main.c -L. -lmem

# Target: lib
lib: CFLAGS += -DAUTOMATED_TESTING_MEMORY_ALLOCATION -DEXAMPLE_BUILD
lib: $(LIBNAME)  

# Target: clean
clean:
	rm -f mem.out test.out $(OBJFILES) $(LIBNAME)

# Rule to build library
$(LIBNAME): $(OBJFILES)
	ar rcs $@ $(OBJFILES)
	cp $(LIBNAME) lib/
# Rule to build object files
%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: build build-test run-test run lib clean
