CC=gcc
LIB=common
STATLIB=lib$(LIB).a

all: statlib server client 

server: server.c clean
	$(CC) -static  server.c -o server -l$(LIB) -L. -I.

client: client.c clean
	$(CC) -static  client.c -o client -l$(LIB) -L. -I.

statlib: common.c clean
	$(CC) -fPIC -c common.c
	ar rcs $(STATLIB) common.o	

clean:
	rm -f *.o
