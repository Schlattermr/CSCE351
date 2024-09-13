#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {

  char word[256];

  strncpy(word, argv[1], sizeof(word) - 1);
  word[255] = '\0';

  if(word == NULL) {
    printf("ERROR: No input given.\n");
  } else {
    printf("%s\n", word);
  }

  return 0;
}