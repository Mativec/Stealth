CC = gcc
OBJ = Graphisme.o Input.o Object.o Player.o
CFLAGS = -ansi -pedantic -Wall
LDFLAGS = -lMLV
EXEC = a.out
DOC = Engine

base : $(EXEC) clean

$(EXEC): Main.c $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

%.o: %.c $(DOC)/Config.h
	$(CC) -c $< $(CFLAGS) $(LDFLAGS)

Graphisme.o : Graphisme.c $(DOC)/Graphisme.h $(DOC)/Object.h

Input.o : Input.c $(DOC)/Input.h

Player.o : Player.c $(DOC)/Player.h $(DOC)/Object.h $(DOC)/Input.h

clean:
	rm *.o