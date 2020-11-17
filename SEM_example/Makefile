CC=gcc
FLAG_1=-W -Wall
FLAG_2=-W -Wall -c

server:ipcs.o client server_info.h server.c
	$(CC) $(FLAG_1) ipcs.o server.c -o server

client:ipcs.o server_info.h client.c
	$(CC) $(FLAG_1) ipcs.o client.c -o client

ipcs.o:../IPCS/ipcs.h ../IPCS/ipcs.c
	$(CC) $(FLAG_2) ../IPCS/ipcs.c -o ipcs.o

clean:
	rm -rf *.o file.serv server client
