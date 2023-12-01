#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <ctype.h>

int main(void) {
  FILE *input = fopen("input", "r");
  char *line = NULL;
  size_t total, size, len = 0;

  while ((len = getline(&line, &size, input)) != -1) {
    for (int i = 0; line[i]; i++) {
      if (isdigit(line[i])) {
        total += (line[i] - '0') * 10;
        break;
      }
    }
    for (int i = len; i >= 0; i--) {
      if (isdigit(line[i])) {
        total += line[i] - '0';
        break;
      }
    }
  }
  printf("%lu\n", total);
  free(line);
  fclose(input);
  return 0;
}
