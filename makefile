all:
	gcc main.c -o main -lGL -lglut -lGLU
	./main