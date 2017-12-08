CC = gcc # Compiler

test: test.o myMem.o mySem.o task.o
	$(CC) -o test test.o myMem.o mySem.o task.o

test.o: test.c
	$(CC) -c test.c

myMem.o: myLibrary/myMem.c
	$(CC) -c myLibrary/myMem.c

mySem.o: myLibrary/mySem.c
	$(CC) -c myLibrary/mySem.c

task.o: myLibrary/task.c
	$(CC) -c myLibrary/task.c

.Phony: clean

clean:
	rm -r test results.txt test.o myMem.o mySem.o task.o
