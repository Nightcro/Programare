CC = gcc
CFLAG = -Wall -Wextra -Werror
EXE = paint_simulator
OBJ =  Pixel.o Operations.o Errors.o paint_simulator.o
DEPS = Pixel.h Operations.h Errors.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAG)

build: $(OBJ)
	$(CC) $^ $(CFLAG) -o $(EXE)

run:
	./$(EXE)

.PHONY : clean

clean:
	rm -f *.o $(EXE)
