GameOfLife: main.o data.o
	$(CC) -o GameOfLife main.o data.o

.PHONY: clean clean_all

clean: 
	-rm *.o

clean_all: clean
	-rm GameOfLife
