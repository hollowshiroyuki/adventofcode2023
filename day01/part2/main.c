#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

const char * const digits[] = {
  "one",
  "two",
  "three",
  "four",
  "five",
  "six",
  "seven",
  "eight",
  "nine",
  NULL
};

int get_digit(const char *str) {
  if (isdigit(*str))
    return (*str) - '0';
  for (int i = 0; digits[i]; i++)
    if (!strncmp(str, digits[i], strlen(digits[i])))
      return i + 1;
  return 0;
}

int main(void) {
  FILE *input = fopen("input", "r");
  char *line = NULL;
  size_t total, size, len, digit = 0;

  while ((len = getline(&line, &size, input)) != -1) {
    for (int i = 0; line[i]; i++) {
      if ((digit = get_digit(line + i))) {
        total += digit * 10;
        break;
      }
    }
    for (int i = len; i >= 0; i--) {
      if ((digit = get_digit(line + i))) {
        total += digit;
        break;
      }
    }
  }
  printf("%lu\n", total);
  free(line);
  fclose(input);
  return 0;
}
