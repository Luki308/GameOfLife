GameOfLife: main.o data.o const_char_arrays.o gif_maker.o gifenc.o
	$(CC) -o GameOfLife main.o data.o const_char_arrays.o gif_maker.o gifenc.o

.PHONY: clean clean_all

clean: 
	-rm *.o

clean_all: clean
	-rm GameOfLife
