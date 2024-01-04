CC = gcc
CFLAGS = -Wall -Wextra -DSTANDALONE_MEMORY_ALLOCATION -DMEMORY_ALLOCATION_VERBOSE_OUTPUT
BUILDDIR = ../../build
LIBDIR = ../../lib
LIBNAME = $(LIBDIR)/libmem.a

# Example source files
EXAMPLESDIR = .
EXAMPLEFILES = $(wildcard $(EXAMPLESDIR)/*.c)
EXAMPLEOBJ = $(patsubst $(EXAMPLESDIR)/%.c, $(BUILDDIR)/%.o, $(EXAMPLEFILES))

# Target: build
build: $(BUILDDIR)/example1.out

# Rule to build the executable
$(BUILDDIR)/example1.out: $(EXAMPLEOBJ) $(LIBNAME)
	$(CC) $(CFLAGS) -o $@ $(EXAMPLEOBJ) -L$(LIBDIR) -lmem

# Rule to build example object files
$(BUILDDIR)/%.o: $(EXAMPLESDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Target: clean
clean:
	rm -rf $(BUILDDIR)/*.o $(BUILDDIR)/example1.out

.PHONY: build clean
