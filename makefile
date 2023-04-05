all:
	gcc main.c -o main -lGL -lglut -lGLU
	./main
	rm main
	
clean: 
	rm main