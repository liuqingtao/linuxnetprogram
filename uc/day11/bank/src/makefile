CC=gcc
RM=rm
CFLAGS= -c -Wall
all:server open
server:server.o
	$(CC) $^ -o ../bin/$@
server.o:server.c
	$(CC) $(CFLAGS) $^
open:open.o dao.o
	$(CC) $^ -o ../bin/$@
open.o:open.c
	$(CC) $(CFLAGS) $^
dao.o:dao.c
	$(CC) $(CFLAGS) $^
clean:
	$(RM) *.o \
	../bin/server \
	../bin/open