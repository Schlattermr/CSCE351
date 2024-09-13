#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {

  char words[256] = "";

  for (int i = 1; i < argc; i++) {
    strncat(words, argv[i], sizeof(words) - strlen(words) - 1);
    if (i < argc - 1) {
      strncat(words, " ", sizeof(words) - strlen(words) - 1);
    }
  }

  if(words == NULL) {
    printf("ERROR: No input given.\n");
  } else {
    printf("%s\n", words);
  }

  return 0;
}