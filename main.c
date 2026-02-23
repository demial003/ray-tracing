#include "color.h"
#include "vec3.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
  FILE *file;
  // hello
  file = fopen("log.txt", "w+");
  if (file == NULL) {
    exit(EXIT_FAILURE);
  }

  double aspect_ratio = 16.0 / 9.0;
  int image_width = 400;
  int image_height = (int)(image_width / aspect_ratio);
  image_height = (image_height < 1) ? 1 : image_height;

  double focal_length = 1.0;
  double viewport_height = 2.0;
  double viewport_width =
      viewport_height * ((double)image_width) / image_height;

  vec3 *v = init_vec3(1.0, 2.7, 3.5);
  print_vec3(v);
  free(v);

  fprintf(file, "\rDone.						"
                "		\n");
  fclose(file);
  exit(EXIT_SUCCESS);
}
