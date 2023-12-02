#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef union cubes {
  struct {
    uint32_t r;
    uint32_t g;
    uint32_t b;
  };
  uint32_t colors[3];
} cubes_t;

int main(void) {
  FILE *input = fopen("input", "r");
  char *line = NULL, *draws, *draw_ctx, *color_ctx;
  size_t total = 0, size = 0, len;

  while ((len = getline(&line, &size, input)) != -1) {
    uint32_t id = strtoul(line + 5, &draws, 10);
    cubes_t count = {0};
    for (char *draw = strtok_r(draws + 1, ";", &draw_ctx); draw;
         draw = strtok_r(NULL, ";", &draw_ctx)) {
      for (char *color = strtok_r(draw, ",", &color_ctx); color;
           color = strtok_r(NULL, ",", &color_ctx)) {
        int v = strtoul(color, &color, 10), c = *(color + 1);
        switch (c) {
        case 'r':
          if (count.r < v)
            count.r = v;
          break;
        case 'g':
          if (count.g < v)
            count.g = v;
          break;
        case 'b':
          if (count.b < v)
            count.b = v;
          break;
        }
      }
    }
    total += count.r * count.g * count.b;
  }
  printf("%lu\n", total);
  fclose(input);
  free(line);
  return 0;
}
