#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

int main(void) {
  FILE *input = fopen("input", "r");
  char *line = NULL, *nums;
  size_t total = 0, size = 0, len, id, num, winning[10], i;

  while ((len = getline(&line, &size, input)) != -1) {
    id = strtoul(line + 4, &nums, 10);
    float worth = .5;
    for (i = 0; *(nums + 1) != '|'; i++) {
      winning[i] = strtoul(nums + 1, &nums, 10);
    }
    nums += 2;
    while (*(nums + 1)) {
      num = strtoul(nums + 1, &nums, 10);
      for (i = 0; i < sizeof(winning) / sizeof(*winning); i++) {
        if (num == winning[i]) {
          worth *= 2;
        }
      }
    }
    if (worth) {
      total += worth;
    }
  }
  printf("%lu\n", total);
  free(line);
  fclose(input);
  return 0;
}
