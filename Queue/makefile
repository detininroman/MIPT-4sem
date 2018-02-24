CC         = gcc
CFLAGS     = -c -Wall
GCOV_FLAGS = -fprofile-arcs -ftest-coverage

all: queue

queue: queue.o test.o
	$(CC) $(GCOV_FLAGS) queue.o test.o -o queue

queue.o: queue.c 
	$(CC) $(CFLAGS) $(GCOV_FLAGS) queue.c 

test.o: test.c 
	$(CC) $(CFLAGS) $(GCOV_FLAGS) test.c

clean:
	rm *.o *.gcda *.gcno *.gcov queue
