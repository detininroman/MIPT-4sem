CC = gcc
CFLAGS = -Wall
GCOV_FLAGS = -fprofile-arcs -ftest-coverage

all: queue.c test.c queue.h
	$(CC) $(CFLAGS) queue.c test.c -o queue

clean:
	rm queue

queue_gcov: queue.c test.c queue.h
	$(CC) $(CFLAGS) $(GCOV_FLAGS) queue.c test.c -o queue_gcov

rmgcov:
	rm queue.c.gcov queue.gcda queue.gcno queue_gcov
