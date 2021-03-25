GameOfLife: src/main.o src/data.o src/arrays.o src/gif_maker.o src/gifenc.o src/game_of_life.o
	$(CC) -o GameOfLife src/main.o src/data.o src/arrays.o src/gif_maker.o src/gifenc.o src/game_of_life.o








.PHONY: clean clean_all

clean: 
	-rm src/*.o

clean_all: clean
	-rm GameOfLife *.gif *.txt
