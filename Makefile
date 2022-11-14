CC = gcc
OBJ = Main.o Test.o Case.o
CFLAGS = -ansi -pedantic -Wall
EXEC = ProgC

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

Main.o: Main.c Case.h Test.h
Test.o: Test.c Test.h Case.h
Case.o: Case.c Case.h


%.o: %.c
	$(CC) -c $< $(CFLAGS)

clean:
	rm *.o
	rm $(EXEC)