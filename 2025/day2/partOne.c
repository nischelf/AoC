#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int chunk_reader(FILE *f, char *buf, int size) {
  int i = 0;
  int c;

  while ((c = fgetc(f)) != EOF) {
    // stop
    if (c == ',' || c == '\n') {
      break;
    }

    // write to buf
    if (i < size - 1) {
      buf[i++] = c;
    }
  }
  // null terminate
  buf[i] = '\0';

  if (c == EOF && i == 0)
    return 0; // no data

  return 1; // got chunk
}

int main() {
  printf("AoC 2025 -  Day 2 #Part 1\n");

  FILE *pfile;
  char buf[200];
  long a, b;
  long code = 0;

  pfile = fopen("input.txt", "r");
  while (chunk_reader(pfile, buf, sizeof(buf))) {
    // printf("Got: %s\n", buf);

    // initialize a, b
    for (int i = 0; buf[i] != '\0'; i++) {
      if (buf[i] == '-') {

        buf[i] = '\0';

        a = atol(buf);
        b = atol(&buf[i + 1]);

        // printf("a: %ld\n", a);
        // printf("b: %ld\n", b);

        break;
      }
    }

    int Base = 10;
    for (; a <= b; a++) {

      // skip odd length numbers
      int length = log10(a) + 1;
      if (length % 2 != 0) {
        continue;
      }

      int divisor = 10;
      // split number in half 1243 -> 12 | 43
      while (a / divisor > divisor) {
        divisor *= Base;
      }
      // printf("split: %d\t%d\n", a / divisor, a % divisor);
      if ((a / divisor) == (a % divisor)) {
        // printf("MATCH: %d\n", a);
        code += a;
      }
    }
  }

  fclose(pfile);

  printf("Code: %ld\n", code);

  return 0;
}
