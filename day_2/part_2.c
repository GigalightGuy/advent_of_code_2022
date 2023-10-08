#include <stdint.h>
#include <stdio.h>
#include <time.h>

static uint32_t scores_lut[11] = {1, 5, 9, 2, 6, 7, 0, 0, 3, 4, 8};

uint16_t hash_round_layout(char a, char b) {
  return ((uint16_t)a << 8 | b) % 11;
}

int main(void) {

  clock_t start, end;
  double elapsed_milisecs;

  printf_s("Enter input file: ");

  char input_path[100];
  gets_s(input_path, 100);

  start = clock();

  FILE *fp;

  if (fopen_s(&fp, input_path, "r")) {
    printf_s("Error opening file %s", input_path);
    return -1;
  }

  char tmp_str[100];

  uint32_t score = 0;
  while (fgets(tmp_str, 100, fp)) {
    score += scores_lut[hash_round_layout(tmp_str[0], tmp_str[2])];
  }

  fclose(fp);

  printf_s("Total score: %u\n", score);

  end = clock();
  elapsed_milisecs = ((double)end - start) / (CLOCKS_PER_SEC * 0.001f);
  printf_s("Elapsed time: %lf\n", elapsed_milisecs);

  return 0;
}
