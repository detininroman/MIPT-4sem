CC         = gcc
CFLAGS     = -c -Wall
GCOV_FLAGS = -fprofile-arcs -ftest-coverage

all: queue

queue: queue.o test.o
	$(CC) $(GCOV_FLAGS) queue.o test.o -o queue

%.o: %.c queue.h
	$(CC) $(CFLAGS) $(GCOV_FLAGS) $<

clean:
	rm *.o *.gcda *.gcno *.gcov queue
