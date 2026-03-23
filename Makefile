main: main.c sphere_list.h hittable.h sphere.h
	rm -rf out.ppm
	gcc -std=c99 -lm -g -fsanitize=address -o main main.c
	./main > out.ppm
