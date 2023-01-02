CC = gcc
OBJ = bin/Graphisme.o bin/Input.o bin/Object.o bin/Player.o bin/Guards.o bin/Wall.o
CFLAGS = -ansi -pedantic -Wall
LDFLAGS = -lMLV
EXEC = a.out

$(EXEC): src/Main.c $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

bin/%.o: src/%.c include/Config.h
	$(CC) -o $@ -c $< $(CFLAGS) $(LDFLAGS)

bin/Graphisme.o : src/Graphisme.c include/Graphisme.h include/Object.h

bin/Input.o : src/Input.c include/Input.h

bin/Wall.o : src/Wall.c include/Wall.h include/Object.h

bin/Player.o : src/Player.c include/Player.h include/Object.h include/Input.h

bin/Guards.o : src/Guards.c include/Guards.h include/Object.h

clean:
	rm bin/*.o
	rm $(EXEC)
