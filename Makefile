CC = gcc
OBJ = Test.o Graphisme.o Input.o
CFLAGS = -ansi -pedantic -Wall
LDFLAGS = -lMLV
EXEC = a.out

base : $(EXEC) clean

$(EXEC): Main.c $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

%.o: %.c config.h
	$(CC) -c $< $(CFLAGS) $(LDFLAGS)

clean:
	rm *.o