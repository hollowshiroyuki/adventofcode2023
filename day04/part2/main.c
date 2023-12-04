#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#define W_NUM_C 10

int main(void) {
  FILE *input = fopen("input", "r");
  char *line = NULL, *nums;
  size_t total = 0, size = 0, len, id, num, winning[W_NUM_C], i,
         count[W_NUM_C] = {0}, k, worth;

  while ((len = getline(&line, &size, input)) != -1) {
    id = strtoul(line + 4, &nums, 10);
    worth = 0;
    for (i = 0; *(nums + 1) != '|'; i++) {
      winning[i] = strtoul(nums + 1, &nums, 10);
    }
    nums += 2;
    for (i = 0; *(nums + 1); i++) {
      num = strtoul(nums + 1, &nums, 10);
      for (i = 0; i < sizeof(winning) / sizeof(*winning); i++) {
        if (num == winning[i]) {
          worth++;
          break;
        }
      }
    }
    total += k = count[(id - 1) % W_NUM_C] + 1;
    count[(id - 1) % W_NUM_C] = 0;
    for (size_t j = 0; i = (id + j) % W_NUM_C, j < worth; j++) {
      count[i] += k;
    }
  }
  printf("%lu\n", total);
  free(line);
  fclose(input);
  return 0;
}
