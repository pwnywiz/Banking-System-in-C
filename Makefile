#Makefile
OBJS = main.o LinkedList.o HashTable.o Graph.o TransactionList.o BaseFunctions.o SearchFunctions.o InputFunctions.o
SOURCE = main.c LinkedList.c HashTable.c Graph.c TransactionList.c BaseFunctions.c SearchFunctions.c InputFunctions.c
HEADER = LinkedList.h HashTable.h Graph.h BaseFunctions.h InputFunctions.h
COMPHEADER = LinkedList.h.gch HashTable.h.gch Graph.h.gch BaseFunctions.h.gch InputFunctions.h.gch
OUT = elegxos
CC = gcc
FLAGS = -g -c

# -g option enables debugging mode
# -c flag generates object code for separate files
all: $(OBJS)
	gcc -o $(OUT) $(SOURCE)

# create / compile the individual files separately
main.o: main.c
	$(CC) $(FLAGS) main.c

LinkedList.o: LinkedList.c
	$(CC) $(FLAGS) LinkedList.c

HashTable.o: HashTable.c
	$(CC) $(FLAGS) HashTable.c

Graph.o: Graph.c
	$(CC) $(FLAGS) Graph.c

TransactionList.o: TransactionList.c
	$(CC) $(FLAGS) TransactionList.c

BaseFunctions.o: BaseFunctions.c
	$(CC) $(FLAGS) BaseFunctions.c

SearchFunctions.o: SearchFunctions.c
	$(CC) $(FLAGS) SearchFunctions.c

InputFunctions.o: InputFunctions.c
	$(CC) $(FLAGS) InputFunctions.c

# clean
clean:
	rm -f $(OBJS) $(COMPHEADER) $(OUT)

# do a bit of accounting
count:
	wc $(SOURCE) $(HEADER)
