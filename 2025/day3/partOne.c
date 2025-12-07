#include <stdio.h>

int main() {

  FILE *pfile;
  char buffer[1024];

  int code = 0;

  pfile = fopen("input.txt", "r");
  // pfile = fopen("smallInput.txt", "r");

  // int line = 1;
  while (fgets(buffer, sizeof(buffer), pfile)) {
    int a = 0;
    int a_last = 0;
    int a_pos = 0;
    int b = 0;
    // printf("#######\n");
    // printf("Line: %d\n", line);
    // printf("%s", buffer);
    // printf("#######\n");
    // line++;

    // search for greatest A
    for (int i = 0; buffer[i] != '\0'; i++) {
      // printf("%c", buffer[i]);
      int digit = buffer[i] - '0';

      if (digit > a) {
        a_last = a;
        a = digit;
        a_pos = i;
        // printf("a: %d, at pos %d\n", a, i);
      } else {
        continue;
      }
    }

    // search for greatest -  B after A
    if (buffer[a_pos + 1] != '\n') {
      for (int i = a_pos + 1; buffer[i] != '\0'; i++) {
        // printf("%c", buffer[i]);
        int digit = buffer[i] - '0';

        if (digit > b) {
          b = digit;
          // printf("b: %d, \n", b);
        } else {
          continue;
        }
      }
    } else {
      b = a;
      a = a_last;
    }

    printf("a: %d, al: %d \n", a, a_last);
    printf("b: %d, \n", b);
    code += a * 10 + b;
  }

  fclose(pfile);
  printf("Code: %d\n", code);

  return 0;
}
