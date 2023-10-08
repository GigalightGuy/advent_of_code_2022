#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

  char tmpStr[100];

#define TOP_LENGTH 3
  uint32_t top_calories[TOP_LENGTH] = {0, 0, 0};
  uint32_t current_calories = 0;

  while (fgets(tmpStr, 100, fp)) {
    if (tmpStr[0] == '\n') {
      if (current_calories > top_calories[TOP_LENGTH - 1]) {
        top_calories[TOP_LENGTH - 1] = current_calories;
        for (int32_t i = TOP_LENGTH - 2; i >= 0; --i) {
          if (current_calories > top_calories[i]) {
            top_calories[i + 1] = top_calories[i];
            top_calories[i] = current_calories;
          }
        }
      }

      current_calories = 0;
    } else {
      current_calories += atoi(tmpStr);
    }
  }

  fclose(fp);

  uint32_t sum_calories = top_calories[0] + top_calories[1] + top_calories[2];
  printf_s("Calories: %u\n", sum_calories);

  end = clock();
  elapsed_milisecs = ((double)end - start) / (CLOCKS_PER_SEC * 0.001f);
  printf_s("Elapsed time: %lf ms", elapsed_milisecs);

  getchar();

  return 0;
}
