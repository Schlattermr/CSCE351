#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define BUFFER_SIZE 100

int main(int argc, char **argv) {
  char filePath[] = "data/test.txt";
  char tempBuffer[BUFFER_SIZE];
  char text[BUFFER_SIZE];

  FILE *instream = fopen(filePath, "r");

  if (instream == NULL) {
    fprintf(stderr, "Unable to open file: %s\n", "data/test.txt");
    exit(1);
  }

  while (fgets(tempBuffer, BUFFER_SIZE, instream) != NULL) {
    strcat(text, tempBuffer);
  }
  fclose(instream);

  printf("%s\n", text);

  return 0;
}