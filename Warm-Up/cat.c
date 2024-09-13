#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
  char filePath[] = "data/test.txt";
  char tempBuffer[100];
  char text[100];

  FILE *instream = fopen(filePath, "r");

  if (instream == NULL) {
    fprintf(stderr, "Unable to open file: %s\n", "data/test.txt");
    exit(1);
  }

  while (fgets(tempBuffer[], 100, instream) != NULL) {
    strcat(tempBuffer);
  }
  fclose(instream);

  return 0;
}