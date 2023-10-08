#include <stdint.h>
#include <stdio.h>

int main(void) {

  FILE *fp;
  uint32_t sec1_start, sec1_end, sec2_start, sec2_end;
  char input_path[100];
  uint32_t fully_contain_count = 0;

  printf_s("Input file: ");
  gets_s(input_path, 100);

  if (fopen_s(&fp, input_path, "r")) {
    printf_s("Error opening %s\n", input_path);
  }

  while (fscanf_s(fp, "%d-%d,%d-%d%[^\n]", &sec1_start, &sec1_end, &sec2_start,
                  &sec2_end) != EOF) {
    if ((sec1_start <= sec2_start && sec1_end >= sec2_end) ||
        (sec2_start <= sec1_start && sec2_end >= sec1_end)) {
      ++fully_contain_count;
    }
  }

  fclose(fp);

  printf_s("Number of fully contained ocurrances: %u", fully_contain_count);

  return 0;
}
