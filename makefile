CC = gcc
CFLAGS = -Wall -Wextra -DSTANDALONE_MEMORY_ALLOCATION -DMEMORY_ALLOCATION_VERBOSE_OUTPUT
LIBNAME = libmem.a
OUT_DIR = out
BUILD_DIR = build

# Source files
SRCDIR = lowlevel
SRCFILES = $(wildcard $(SRCDIR)/*.c)
OBJFILES = $(patsubst $(SRCDIR)/%.c, $(BUILD_DIR)/%.o, $(SRCFILES))

# Target: build
build: lowlevel/mem.c
	$(CC) $(CFLAGS) -o $(OUT_DIR)/mem.out lowlevel/*.c

# Target: build-test
build-test: CFLAGS += -DAUTOMATED_TESTING_MEMORY_ALLOCATION
build-test: CFLAGS := $(filter-out -DMEMORY_ALLOCATION_VERBOSE_OUTPUT,$(CFLAGS))
build-test: $(OBJFILES) test/*.c
	$(CC) $(CFLAGS) -o $(OUT_DIR)/test.out $(OBJFILES) test/*.c

# Target: run-test
run-test: build-test
	./$(OUT_DIR)/test.out

# Target: run
run: $(LIBNAME) main.c
	$(CC) $(CFLAGS) -o $(OUT_DIR)/mem.out main.c -L. -lmem

# Target: lib
lib: CFLAGS += -DAUTOMATED_TESTING_MEMORY_ALLOCATION -DEXAMPLE_BUILD -DLIB_BUILD
lib: $(LIBNAME)  

# Target: clean
clean:
	rm -f $(OUT_DIR)/mem.out $(OUT_DIR)/test.out $(OBJFILES) $(LIBNAME)
	rm -rf $(BUILD_DIR)

# Rule to build library
$(LIBNAME): $(OBJFILES)
	ar rcs $@ $(OBJFILES)
	

# Rule to build object files
$(BUILD_DIR)/%.o: $(SRCDIR)/%.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: build build-test run-test run lib clean
