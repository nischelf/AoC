#include <stdio.h>
#include <stdlib.h>

int main() {

  FILE *pfile;
  char buffer[256];
  int fresh_count = 0;
  long *fresh_range = NULL;
  int capacity = 0;
  int range_entries = 0;
  long start, end;

  printf("AoC day5 #part 1\n");

  // pfile = fopen("input.txt", "r");
  pfile = fopen("smallInput.txt", "r");

  if (!pfile) {
    printf("Error opening file\n");
    return 1;
  }

  // fresh ranges
  while (fgets(buffer, sizeof(buffer), pfile)) {
    if (buffer[0] == '\n') {
      break;
    }
    sscanf(buffer, "%ld-%ld", &start, &end);
    // printf("Range: %ld - %ld\n", start, end);

    for (int i = start; i <= end; i++) {

      // allocate more space if needed
      if (range_entries == capacity) {
        capacity = (capacity == 0) ? 16 : capacity * 2;
        fresh_range = realloc(fresh_range, capacity * sizeof(long));
      }

      fresh_range[range_entries] = i;
      // printf("Fresh ID: %ld\n", fresh_range[i]);
      range_entries++;
    }
  }

  start = -1;
  // ingredient ids
  while (fgets(buffer, sizeof(buffer), pfile)) {
    sscanf(buffer, "%ld", &start);
    // printf("ID: %ld\n", start);

    for (int i = 0; i < range_entries; i++) {
      if (fresh_range[i] == start) {
        fresh_count += 1;
        break;
      }
    }
  }

  printf("Fresh Count: %d\n", fresh_count);

  return 0;
}
