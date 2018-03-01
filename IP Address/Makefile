CC = gcc
CFLAGS = -Wall -Wextra
SRC = ip.c
EXE = ip

build:
	$(CC) $(SRC) $(CFLAGS) -o $(EXE)

run:
	./$(EXE)

.PHONY : clean

clean:
	rm -f *.o $(EXE)