#include <stdint.h>
#include <stdio.h>
#include <string.h>

int main(void) {

  char tmp_str[100], tmp_str2[100], common_types[100];
  FILE *fp;
  uint32_t total_prio = 0;

  printf_s("Enter input file: ");
  gets_s(tmp_str, 100);

  if (fopen_s(&fp, tmp_str, "r")) {

    printf_s("Error opening %s\n", tmp_str);
    return -1;
  }

  while (fgets(tmp_str, 100, fp)) {

    size_t str_len, str_len2;
    uint32_t prio = 0;
    size_t n = 0;

    fgets(tmp_str2, 100, fp);

    str_len = strlen(tmp_str) - 1;
    str_len2 = strlen(tmp_str2) - 1;

    for (size_t i = 0; i < str_len; ++i) {
      for (size_t j = 0; j < str_len2; ++j) {
        if (tmp_str[i] == tmp_str2[j]) {
          common_types[n] = tmp_str[i];
          ++n;
        }
      }
    }

    fgets(tmp_str, 100, fp);
    str_len = strlen(tmp_str) - 1;

    for (size_t i = 0; i < n; ++i) {
      for (size_t j = 0; j < str_len; ++j) {
        if (common_types[i] == tmp_str[j]) {
          if (tmp_str[j] >= 96 && tmp_str[j] <= 122) {
            prio = (uint32_t)tmp_str[j] - 96;
          } else {
            prio = (uint32_t)tmp_str[j] - 38;
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
