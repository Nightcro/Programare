CC = gcc
CFLAG = -Wall -Wextra
EXE =  image_processing
OBJ =  queue.o image.o tasks.o image_processing.o
DEPS = bmp_header.h queue.h image.h tasks.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAG)

build: $(OBJ)
	$(CC) $^ $(CFLAG) -o $(EXE)

run:
	./$(EXE)

.PHONY : clean

clean:
	rm -f *.o $(EXE)
