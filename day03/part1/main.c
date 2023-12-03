
#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WIDTH 140
#define HEIGTH 140
#define SIZE ((WIDTH + 2) * (HEIGTH + 2))

typedef struct number {
  uint32_t value;
  const char *start, *end;
  struct number *next;
} number_t;

void read_file(char *map) {
  FILE *input = fopen("input", "r");
  size_t size = 0, len;
  char *line = NULL;
  for (int i = 1; (len = getline(&line, &size, input)) != -1; i++) {
    memcpy(map + (i * (WIDTH + 2)) + 1, line, len - 1);
  }
  free(line);
  fclose(input);
}

number_t *read_numbers(char const *map) {
  number_t *list = NULL;

  for (char const *cur = map; cur != map + SIZE; cur++) {
    if (isdigit(*cur)) {
      number_t *neo = malloc(sizeof(*neo));
      neo->start = cur;
      neo->value = strtoul(cur, (char **)&cur, 10);
      cur = cur - 1;
      neo->end = cur;
      neo->next = list;
      list = neo;
    }
  }
  return list;
}

int main(void) {
  char *area = malloc(SIZE);
  memset(area, '.', SIZE);
  read_file(area);
  number_t *numbers = read_numbers(area), *last = NULL;
  size_t total = 0;

  for (int y = 0; y < HEIGTH; y++) {                    // traverse map y
    for (int x = 0; x < WIDTH; x++) {                   // traverse map x
      char pos = *(area + ((WIDTH + 2) * y) + (x + 1)); // get current char
      if (pos != '.' && !isdigit(pos)) {     // check that pos is a "part"
        for (int dy = -1; dy <= 1; dy++) {   // traverse c adjacent y
          for (int dx = -1; dx <= 1; dx++) { // traverse c adjacent x
            char *c = area + ((WIDTH + 2) * (y + dy)) +
                      (x + 1 + dx); // get adjacent location
            if (isdigit(*c)) {      // if adjacent is a number
              for (number_t *cur = numbers; cur;
                   cur = cur->next) { // search for the parsed number
                if (cur->start <= c &&
                    c <= cur->end) { // if adjacent location matches this number
                  if (last ==
                      cur)    // if the last number is the same we already added
                    break;    // continue
                  last = cur; // update the last added number
                  total += cur->value; // add the number to the total
                }
              }
            }
          }
        }
      }
    }
  }
  printf("%lu\n", total);
  for (number_t *cur = numbers; cur; cur = numbers) {
    numbers = cur->next;
    free(cur);
  }
  free(area);
  return 0;
}
