#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int semicolon_chunk_reader(FILE *f, char *buf, int size) {
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

char *convertNumberIntoArray(unsigned int number) {
  unsigned int length = (int)(log10((float)number)) + 1;
  char *arr = (char *)malloc(length * sizeof(char)), *curr = arr;
  do {
    *curr++ = number % 10;
    number /= 10;
  } while (number != 0);
  return arr;
}

int check_pattern(int num) {
  unsigned int length = (int)(log10((float)num)) + 1;
  char *arr = convertNumberIntoArray(num);

  int second_half = atoi(&arr[length / 2]);
  arr[length / 2] = '\0';
  int first_half = atoi(arr);

  printf("Number Array: ");
  printf("1st: %d", first_half);
  printf("2nd: %d", second_half);

  return 0; // if not match
  return 1; // if pattern matches
}

int main() {
  printf("AoC 2025 -  Day 2 #Part 1\n");

  FILE *pfile;
  char buf[200];
  char seen[50];
  int a, b;
  int code = 0;

  pfile = fopen("smallInput.txt", "r");
  while (semicolon_chunk_reader(pfile, buf, sizeof(buf))) {
    printf("Got: %s\n", buf);

    // initialize a, b
    for (int i = 0; buf[i] != '\0'; i++) {
      if (buf[i] == '-') {

        buf[i] = '\0';

        a = atoi(buf);
        b = atoi(&buf[i + 1]);

        // printf("a: %d\n", a);
        // printf("b: %d\n", b);

        break;
      }
    }

    // check for seen in the buf, probably need array for this but also need to
    // increase +1 every loop
    for (a; a <= b; a++) {

      if ((((int)floor(log10(a)) + 1) % 2) == 0) {
        if (check_pattern(a)) {
          code += a;
        }
      } else {
        continue;
      }
    }
  }

  fclose(pfile);

  printf("Code: %d\n", code);

  return 0;
}
