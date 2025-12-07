#include <stdio.h>
#include <stdlib.h>

int main() {

  int curDial = 50;
  FILE *fptr;
  char line[6];
  int code = 0;

  fptr = fopen("input.txt", "r");
  // fptr = fopen("smallInput.txt", "r");

  while (fgets(line, sizeof(line), fptr)) {
    // printf("%s", line);

    char direction = line[0];
    int num = atoi(&line[1]);

    printf("curDial: %d\n", curDial);
    if (direction == 'L') {
      curDial = (curDial - num + 100) % 100;
    } else if (direction == 'R') {
      curDial = (curDial + num + 100) % 100;
    }

    if (curDial == 0) {
      code++;
    }
  }

  fclose(fptr);
  printf("Code: %d\n", code);

  return 0;
}
