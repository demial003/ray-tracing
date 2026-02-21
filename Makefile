main: main.c
	gcc -g -fsanitize=address -o main main.c
