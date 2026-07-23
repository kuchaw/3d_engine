build:
	gcc -Wall -std=c99 src/*.c -lSDL2-o renderer $(shell pkg-config --cflags --libs sdl2)
run: 
	./renderer
clean:
	rm -f renderer