main: main.c vec3.c ray.c
	gcc -lm -g -fsanitize=address -o main main.c
