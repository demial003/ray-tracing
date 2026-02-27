main: main.c vec3.h color.h ray.h
	rm -rf out.ppm
	gcc -Wall -Werror -std=c99 -lm -g -fsanitize=address -o main main.c
	./main > out.ppm
