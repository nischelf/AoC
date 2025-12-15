#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  FILE *pfile;
  char buffer[4096];

  int **numbers = NULL;
  int *row_lengths = NULL;

  int rows = 0;
  int row_capacity = 0;

  char *operations = NULL;
  int op_count = 0;
  int op_capacity = 0;

  long code = 0; // sum of col opertations

  printf("AoC 2025 - Day6 #part1\n");

  pfile = fopen("input.txt", "r");
  if (!pfile) {
    printf("Error opening file!\n");
    return 1;
  }

  while (fgets(buffer, sizeof(buffer), pfile)) {

    // get operations + *
    if (buffer[0] == '+' || buffer[0] == '*') {
      char *p = buffer;

      while (*p) {
        if (*p == '+' || *p == '*') {
          if (op_count == op_capacity) {
            op_capacity = op_capacity ? op_capacity * 2 : 4;
            operations = realloc(operations, op_capacity * sizeof(char));
          }
          operations[op_count++] = *p;
        }
        p++;
      }
      continue;
    }

    // get numbers
    if (rows == row_capacity) {
      row_capacity = row_capacity ? row_capacity * 2 : 4;
      numbers = realloc(numbers, row_capacity * sizeof(int *));
      row_lengths = realloc(row_lengths, row_capacity * sizeof(int));
    }

    numbers[rows] = NULL;

    int col_count = 0;
    int col_capacity = 0;

    char *p = buffer;
    while (*p) {
      if (isdigit(*p) || ((*p == '-' || *p == '+') && isdigit(*(p + 1)))) {
        int num = strtol(p, &p, 10);

        if (col_count == col_capacity) {
          col_capacity = col_capacity ? col_capacity * 2 : 4;
          numbers[rows] = realloc(numbers[rows], col_capacity * sizeof(int));
        }

        numbers[rows][col_count++] = num;
      } else {
        p++;
      }
    }

    row_lengths[rows] = col_count;
    rows++;
  }

  fclose(pfile);

  // output
  // printf("Operations:\n");
  // for (int i = 0; i < op_count; i++) {
  //   printf("%c ", operations[i]);
  // }
  // printf("\n\nNumbers:\n");
  //
  // for (int i = 0; i < rows; i++) {
  //   for (int j = 0; j < row_lengths[i]; j++) {
  //     printf("%d ", numbers[i][j]);
  //   }
  //   printf("\n");
  // }

  // calc code
  for (int c = 0; c < op_count; c++) {
    if (operations[c] == '+') {
      for (int r = 0; r < rows; r++) {
        code += numbers[r][c];
      }
    } else if (operations[c] == '*') {
      long prod = 1;
      for (int r = 0; r < rows; r++) {
        prod *= numbers[r][c];
      }
      code += prod;
    }
  }

  // free memory
  for (int i = 0; i < rows; i++) {
    free(numbers[i]);
  }
  free(numbers);
  free(row_lengths);
  free(operations);

  printf("\nCode: %ld\n", code);

  return 0;
}
