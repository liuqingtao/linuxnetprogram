CC=gcc
RM=rm
CFLAGS= -c -Wall -lpthread
all:main
main:main.o condition.o threadpool.o
	$(CC) $^ -o$@ -lpthread -lrt
main.o:main.c
	$(CC) $(CFLAGS) $^
condition.o:condition.c
	$(CC) $(CFLAGS) $^
threadpool.o:threadpool.c
	$(CC) $(CFLAGS) $^
clean:
	$(RM) *.o 