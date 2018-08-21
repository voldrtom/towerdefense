CC=g++
CFLAGS=-Wall -pedantic -g -std=c++11 -Wno-long-long -O0 -ggdb
CURSES=-lncurses
EXEC=voldrtom
SRC=./src/main.cpp ./src/map.cpp ./src/menu.cpp ./src/game.cpp ./src/tower.cpp ./src/archer_tower.cpp ./src/ballista_tower.cpp ./src/figure.cpp ./src/medium_figure.cpp ./src/light_figure.cpp
OBJ=./src/main.o ./src/map.o ./src/menu.o ./src/game.o ./src/tower.o ./src/archer_tower.o ./src/ballista_tower.o ./src/figure.o ./src/medium_figure.o ./src/light_figure.o


.PHONY: all
all: compile doc

.PHONY: compile
compile: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $(EXEC) $(CURSES)

$(OBJ): ./src/%.o: ./src/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@ $(CURSES)

.PHONY: clean
clean:
	rm -rf ./src/*.o $(EXEC)
	rm -rf doc

.PHONY: doc
doc:
	mkdir doc
	doxygen ./src/doc

.PHONY: run
run: compile
	./$(EXEC)