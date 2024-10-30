#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 100

int main(int argc, char **argv) {
  char filePath[] = argv[1];
  char tempBuffer[BUFFER_SIZE] = "";
  char text[BUFFER_SIZE] = "";

  FILE *instream = fopen(filePath, "r");

  if (instream == NULL) {
    fprintf(stderr, "Unable to open file: %s\n", filePath);
    exit(1);
  }

  while (fgets(tempBuffer, BUFFER_SIZE, instream) != NULL) {
    strcat(text, tempBuffer);
  }
  fclose(instream);

  printf("%s\n", text);

  return 0;
}