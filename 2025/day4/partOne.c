#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  printf("AoC 2025 - Day 4 #part 1\n");

  FILE *pfile;
  char **grid = NULL;
  int rows = 0;
  int capacity = 0;
  char buffer[256];

  // Open input
  // pfile = fopen("smallInput.txt", "r");
  pfile = fopen("input.txt", "r");
  if (!pfile) {
    printf("Error - no file!\n");
    return 1;
  }

  // --- Load dynamic grid ---
  while (fgets(buffer, sizeof(buffer), pfile)) {
    buffer[strcspn(buffer, "\n")] = '\0'; // remove newline

    if (rows == capacity) {
      capacity = (capacity == 0) ? 16 : capacity * 2;
      grid = realloc(grid, capacity * sizeof(char *));
    }

    grid[rows] = malloc(strlen(buffer) + 1);
    strcpy(grid[rows], buffer);
    rows++;
  }
  fclose(pfile);

  int code = 0;

  // --- Count accessible rolls ---
  for (int i = 0; i < rows; i++) {
    int rowLen = strlen(grid[i]);

    for (int j = 0; j < rowLen; j++) {

      if (grid[i][j] != '@')
        continue;

      int neighbourCount = 0;

      // Check 8 neighbors
      for (int di = -1; di <= 1; di++) {
        for (int dj = -1; dj <= 1; dj++) {

          if (di == 0 && dj == 0)
            continue;

          int ni = i + di;
          int nj = j + dj;

          // bounds
          if (ni < 0 || ni >= rows)
            continue;

          int nLen = strlen(grid[ni]);
          if (nj < 0 || nj >= nLen)
            continue;

          if (grid[ni][nj] == '@')
            neighbourCount++;
        }
      }

      if (neighbourCount < 4)
        code++;
    }
  }

  printf("Code: %d\n", code); // should print 13

  // free memory
  for (int i = 0; i < rows; i++)
    free(grid[i]);
  free(grid);

  return 0;
}
