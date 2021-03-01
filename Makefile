GameOfLife: main.o
	$(CC) -o GameOfLife main.o

.PHONY: clean clean_all

clean: 
	-rm *.o

clean_all: clean
	-rm GameOfLife
