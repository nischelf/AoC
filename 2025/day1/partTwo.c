#include <stdio.h>
#include <stdlib.h>

int main() {

  int curDial = 50;
  int lastDial = 50;
  FILE *fptr;
  char line[6];
  int code = 0;
  int rotations = 0;

  fptr = fopen("input.txt", "r");
  // fptr = fopen("smallInput.txt", "r");

  while (fgets(line, sizeof(line), fptr)) {
    // printf("%s", line);

    char direction = line[0];
    int num = atoi(&line[1]);

    rotations = num / 100;
    code += rotations;
    if (direction == 'L') {

      if (lastDial - num < 0) {
        code++;
      }

      curDial = (curDial - num + 100) % 100;
      lastDial = curDial;

    } else if (direction == 'R') {

      if (lastDial + num >= 100) {
        code++;
      }

      curDial = (curDial + num + 100) % 100;
      lastDial = curDial;
    }

    if (curDial == 0 && lastDial != 0) {
      code++;
    }

    // printf("curDial: %d\n", curDial);
    // printf("Code: %d\n", code);
  }

  fclose(fptr);
  printf("Code: %d\n", code);

  return 0;
}
