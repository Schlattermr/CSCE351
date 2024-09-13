#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv) {

  char word[256] = argv[1];

  if(word == NULL) {
    printf("ERROR: No input given.\n");
  } else {
    printf("%s\n", word);
  }

  return 0;
}