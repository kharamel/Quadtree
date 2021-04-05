exe:	main.cpp
	g++ *.cpp src/*.cpp src/*.c `sdl-config --cflags --libs` -lSDL_image -lSDL_mixer -lSDL_ttf -Iincludes 

run:
	./a.out

r:
	./a.out

clean:
	rm a.out

c:
	rm a.out

graph:
	dot -Tpng graph.dot -o graph.png; xdg-open graph.png;
