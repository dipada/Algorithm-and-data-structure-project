CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -Wconversion
COMMON_DEPS = src/*.h Makefile

# C Project
BLDDIR = build
BINDIR = bin
SRCDIR = src

all: edit_distance_test edit_distance_main dyn_edit_distance_test dyn_edit_distance_main

#For naive version
edit_distance_main: $(BINDIR)/edit_distance_main

edit_distance_test: $(BINDIR)/edit_distance_test

run_edit_distance_test:
	./bin/edit_distance_test

#For dynamic programming version

dyn_edit_distance_main: $(BINDIR)/dyn_edit_distance_main

dyn_edit_distance_test: $(BINDIR)/dyn_edit_distance_test

run_dyn_edit_distance_main:
	./bin/dyn_edit_distance_main src/data/correctme.txt src/data/dictionary.txt

run_dyn_edit_distance_test:
	./bin/dyn_edit_distance_test

$(BLDDIR)/%.o: $(SRCDIR)/%.c $(COMMON_DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

$(BLDDIR)/unity.o: $(SRCDIR)/unity/unity.c $(COMMON_DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

$(BINDIR)/edit_distance_test: $(BLDDIR)/edit_distance_test.o $(BLDDIR)/edit_distance.o $(BLDDIR)/unity.o $(COMMON_DEPS)
	$(CC) -o $(BINDIR)/edit_distance_test $(BLDDIR)/edit_distance_test.o $(BLDDIR)/edit_distance.o $(BLDDIR)/unity.o

$(BINDIR)/edit_distance_main: $(BLDDIR)/edit_distance_main.o $(BLDDIR)/edit_distance.o $(COMMON_DEPS)
	$(CC) -o $(BINDIR)/edit_distance_main $(BLDDIR)/edit_distance_main.o $(BLDDIR)/edit_distance.o

$(BINDIR)/dyn_edit_distance_test: $(BLDDIR)/edit_distance_dyn_test.o $(BLDDIR)/edit_distance_dyn.o $(BLDDIR)/unity.o $(COMMON_DEPS)
	$(CC) -o $(BINDIR)/dyn_edit_distance_test $(BLDDIR)/edit_distance_dyn_test.o $(BLDDIR)/edit_distance_dyn.o $(BLDDIR)/unity.o

$(BINDIR)/dyn_edit_distance_main: $(BLDDIR)/edit_distance_dyn_main.o $(BLDDIR)/edit_distance_dyn.o $(COMMON_DEPS)
	$(CC) -o $(BINDIR)/dyn_edit_distance_main $(BLDDIR)/edit_distance_dyn_main.o $(BLDDIR)/edit_distance_dyn.o

clean: 
	rm -f $(BINDIR)/* $(BLDDIR)/*

