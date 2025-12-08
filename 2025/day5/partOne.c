#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

  FILE *pfile;
  char buffer[256];
  int fresh_count = 0;
  char **fresh_range = NULL;
  int capacity = 0;
  int range_entries = 0;
  long start, end, id;

  printf("AoC day5 #part 1\n");

  pfile = fopen("input.txt", "r");
  // pfile = fopen("smallInput.txt", "r");

  if (!pfile) {
    printf("Error opening file\n");
    return 1;
  }

  // fresh ranges
  while (fgets(buffer, sizeof(buffer), pfile)) {
    if (buffer[0] == '\n') {
      break;
    }

    //   // allocate more space if needed
    if (range_entries == capacity) {
      capacity = (capacity == 0) ? 16 : capacity * 2;
      fresh_range = realloc(fresh_range, capacity * sizeof(long));
    }

    buffer[strcspn(buffer, "\n")] = '\0'; // remove newline
    fresh_range[range_entries] = malloc(strlen(buffer) + 1);
    strcpy(fresh_range[range_entries], buffer);
    range_entries++;

    // sscanf(buffer, "%ld-%ld", &start, &end);
    // printf("Range: %ld - %ld\n", start, end);
  }

  start = -1;
  // ingredient ids
  while (fgets(buffer, sizeof(buffer), pfile)) {
    sscanf(buffer, "%ld", &id);

    for (int i = 0; i < range_entries; i++) {
      sscanf(fresh_range[i], "%ld-%ld", &start, &end);
      // printf("Range: %ld - %ld\n", start, end);
      if (id >= start && id <= end) {
        fresh_count += 1;
        break;
      }
    }
  }

  printf("Fresh Count: %d\n", fresh_count);

  return 0;
}
