CC = gcc
CFLAG = -Wall -o2 -g
ALL = client server
OBJ = client.o server.o

all:server client
server:server.o
	$(CC) $(CFLAG) $< -o $@ -lpthread -lsqlite3

client:client.o
	$(CC) $(CFLAG) $< -o $@

%*.o:%*.c
	$(CC) $(CFLAG) $< -c $@ 

.PHONY:clean
clean:
	rm -rf $(ALL)
	rm -rf $(OBJ)
