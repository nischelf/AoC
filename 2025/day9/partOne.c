#include <stdio.h>
#include <stdlib.h>

int abs_diff(int a, int b) { return (a > b) ? (a - b) : (b - a); }

int main() {
  typedef struct {
    int x;
    int y;
  } Position;

  FILE *pfile;
  char buffer[64];

  Position *red_tiles = NULL;
  int red_tiles_len = 0;
  int capacity = 0;

  Position cur_pos;
  long area = 0;
  long max = 0;

  pfile = fopen("input.txt", "r");
  if (!pfile) {
    perror("fopen");
    return 1;
  }

  while (fgets(buffer, sizeof(buffer), pfile)) {

    if (red_tiles_len == capacity) {
      capacity = (capacity == 0) ? 8 : capacity * 2;
      red_tiles = realloc(red_tiles, capacity * sizeof(Position));
      if (!red_tiles) {
        perror("realloc");
        exit(1);
      }
    }

    sscanf(buffer, "%d,%d", &cur_pos.x, &cur_pos.y);
    red_tiles[red_tiles_len++] = cur_pos;
  }

  fclose(pfile);

  for (int i = 0; i < red_tiles_len; i++) {
    for (int j = i + 1; j < red_tiles_len; j++) {
      long width = abs_diff(red_tiles[i].x, red_tiles[j].x) + 1;
      long height = abs_diff(red_tiles[i].y, red_tiles[j].y) + 1;
      area = width * height;

      if (area > max) {
        max = area;
      }
    }
  }

  free(red_tiles);

  printf("Max: %ld\n", max);
  return 0;
}
