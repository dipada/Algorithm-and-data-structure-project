CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -Wconversion
COMMON_DEPS = src/*.h Makefile

# C Project
BLDDIR = build
BINDIR = bin
SRCDIR = src

all: $(BINDIR)/ordered_records_main

test: CFLAGS += -DTEST=1
test: $(BINDIR)/msort_test

$(BLDDIR)/%.o: $(SRCDIR)/%.c $(COMMON_DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

$(BINDIR)/msort_test: $(BLDDIR)/msort_test.o $(BLDDIR)/msort.o $(BLDDIR)/unity.o $(COMMON_DEPS)
	$(CC) -o $(BINDIR)/test $(BLDDIR)/msort_test.o $(BLDDIR)/msort.o $(BLDDIR)/unity.o

$(BINDIR)/ordered_records_main: $(BLDDIR)/ordered_records_main.o $(BLDDIR)/msort.o $(COMMON_DEPS)
	$(CC) -o $(BINDIR)/final $(BLDDIR)/ordered_records_main.o $(BLDDIR)/msort.o

clean: 
	rm -f $(BINDIR)/* $(BLDDIR)/*


run:
	./bin/final ./src/records.csv