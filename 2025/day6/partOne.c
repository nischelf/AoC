#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  FILE *pfile;
  char buffer[4096];

  int **numbers = NULL;
  int rows = 0;
  int cols = 0;
  int row_capacity = 0;
  int col_capacity = 0;

  char *operations = NULL;

  long code = 0; // sum of col operation

  printf("AoC 2025 - Day6 #part1\n");

  // File handling
  //  pfile = fopen("input.txt", "r");
  pfile = fopen("smallInput.txt", "r");
  if (!pfile) {
    printf("Error opening file!\n");
    return 1;
  }

  // read numbers + operations
  while (fgets(buffer, sizeof(buffer), pfile)) {
    // printf("%s", buffer);

    if (rows == row_capacity) {
      row_capacity = row_capacity ? row_capacity * 2 : 4;
      numbers = realloc(numbers, row_capacity * sizeof(int *));
    }

    numbers[rows] = NULL;

    char *p = buffer;
    // put numbers in numbers 2d array
    while (*p) {
      if (isdigit(*p) || ((*p == '-' || *p == '+') && isdigit(*(p + 1)))) {
        // Found a number
        long num = strtol(p, &p, 10); // Read number
        printf("%ld\n", num);         // and print it.

        if (cols == col_capacity) {
          col_capacity = col_capacity ? col_capacity * 2 : 4;
          numbers[rows] = realloc(numbers[rows], col_capacity * sizeof(int));
        }

        numbers[rows][cols] = num;
        cols++;
      } else {
        // Otherwise, move on to the next character.
        p++;
      }
    }

    cols = 0;
    col_capacity = 0;
    rows++;
  }

  fclose(pfile);

  // output
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      printf("%ld\t", numbers[i][j]);
    }
  }

  // free memory
  for (int i = 0; i < row_capacity; i++) {
    free(numbers[i]);
  }
  free(numbers);

  return 0;
}
