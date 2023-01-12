CC = gcc
OBJ = bin/Graphisme.o bin/Input.o bin/Object.o bin/Player.o bin/Sound.o
CFLAGS = -ansi -pedantic -Wall
LDFLAGS = -lMLV
EXEC = a.out

$(EXEC): src/Main.c $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

bin/%.o: src/%.c include/Config.h include/Object.h
	$(CC) -o $@ -c $< $(CFLAGS) $(LDFLAGS)

bin/Object.o : src/Object.c

bin/Input.o : src/Input.c include/Input.h

bin/Wall.o : src/Wall.c include/Wall.h

bin/Player.o : src/Player.c include/Player.h include/Input.h

bin/Guards.o : src/Guards.c include/Guards.h include/Wall.h

bin/Relique.o : src/Relique.c include/Relique.h include/Player.h include/Wall.h

bin/Graphisme.o : src/Graphisme.c include/Graphisme.h include/Player.h include/Relique.h include/Wall.h

bin/Sound.o : src/Sound.c include/Sound.h 

clean:
	rm bin/*.o
	rm $(EXEC)
