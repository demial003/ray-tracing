main: main.c vec3.h color.h ray.h
	gcc -lm -g -fsanitize=address -o main main.c
