CC = gcc
CFLAGS = -Wall
GCOV_FLAGS = -fprofile-arcs -ftest-coverage

all: main.c header.h
	$(CC) $(CFLAGS) main.c -o queue

clean:
	rm queue

queue_gcov: main.c header.h
	$(CC) $(CFLAGS) $(GCOV_FLAGS) main.c -o queue_gcov

rmgcov:
	rm main.c.gcov main.gcda main.gcno queue_gcov
