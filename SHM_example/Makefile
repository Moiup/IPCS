CC=gcc
FLAG=-W -Wall
FLAG_2=-W -Wall -c

server:ipcs.o server_info.h client server.c
	$(CC) $(FLAG) ipcs.o server.c -o server

client:ipcs.o server_info.h client.c
	$(CC) $(FLAG) ipcs.o client.c -o client

ipcs.o:../IPCS/ipcs.h ../IPCS/ipcs.c
	$(CC) $(FLAG_2) ../IPCS/ipcs.c -o ipcs.o

clean:
	rm -rf *.o server.file

