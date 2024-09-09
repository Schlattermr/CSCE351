#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
  char filePath[] = "data/test.txt";
  int maxSize = 50;
  char tempBuffer[100];

  FILE *instream = fopen(filePath, "r");

  if (instream == NULL) {
    fprintf(stderr, "Unable to open file: %s\n", "data/test.txt");
    exit(1);
  }

  i = 0;
  while (fgets(tempBuffer, maxSize, instream) != NULL) {
    tempBuffer[strlen(tempBuffer) - 1] = '\0';
    char *fileText = strtok(tempBuffer, ".");
    i++;
  }
  fclose(instream);

  return 0;
}