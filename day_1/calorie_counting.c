#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {

  clock_t start, end;
  double elapsedSecs;

  printf_s("Enter input file: ");

  char inputPath[100];
  gets_s(inputPath, 100);

  start = clock();

  FILE *fp;

  if (fopen_s(&fp, inputPath, "r")) {
    printf_s("Error opening file %s", inputPath);
    return -1;
  }

  char tmpStr[100];
  uint32_t max_calories = 0, current_calories = 0;

  while (fgets(tmpStr, 100, fp)) {
    if (tmpStr[0] == '\n') {
      max_calories =
          current_calories > max_calories ? current_calories : max_calories;
      current_calories = 0;
    } else {
      current_calories += atoi(tmpStr);
    }
  }

  fclose(fp);

  printf_s("Calories: %d\n", max_calories);

  end = clock();
  elapsedSecs = ((double)end - start) / CLOCKS_PER_SEC;
  printf_s("Elapsed time in seconds: %lf", elapsedSecs);

  getchar();

  return 0;
}
