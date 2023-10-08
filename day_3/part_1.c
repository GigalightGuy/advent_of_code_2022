#include <stdint.h>
#include <stdio.h>
#include <string.h>

int main(void) {

  char tmp_str[100];
  FILE *fp;
  uint32_t total_prio = 0;

  printf_s("Enter input file: ");
  gets_s(tmp_str, 100);

  if (fopen_s(&fp, tmp_str, "r")) {

    printf_s("Error opening %s\n", tmp_str);
    return -1;
  }

  while (fgets(tmp_str, 100, fp)) {

    size_t str_len = strlen(tmp_str) - 1;
    size_t half_len = str_len / 2;
    uint32_t prio = 0;

    for (size_t i = 0; i < half_len; ++i) {
      for (size_t j = half_len; j < str_len; ++j) {
        if (tmp_str[i] == tmp_str[j]) {
          if (tmp_str[i] >= 96 && tmp_str[i] <= 122) {
            prio = (uint32_t)tmp_str[i] - 96;
          } else {
            prio = (uint32_t)tmp_str[i] - 38;
          }
          goto out_of_loops;
        }
      }
    }
  out_of_loops:
    total_prio += prio;
  }

  fclose(fp);

  printf_s("Total priority: %u\n", total_prio);

  return 0;
}
