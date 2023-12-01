#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  if (argc < 2) {
    puts("Input file not provided");
    return -1;
  }

  FILE *fInput;

  fInput = fopen(argv[1], "r");

  if (fInput == NULL) {
    printf("Error loading file");
    return -1;
  }
  
  char line[256];
  unsigned char digits[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
  unsigned short digitsLength =  sizeof(digits) / sizeof(digits[0]); // Could've also just hard coded this but eh 🤷
  unsigned int total = 0;

  while(fgets(line, sizeof(line), fInput) != NULL) {
    unsigned char firstDigit, lastDigit;
    char numStr[2];
    unsigned int i = 0;
    int foundIndex;

    while (line[i] != NULL) { // Check for first digit linearly forwards
      foundIndex = -1; // The code below code probably be a function to make it more readable
      for (int j = 0; j < digitsLength; ++j) {
        if (line[i] == digits[j]) {
          firstDigit = line[i];
          foundIndex = i;
        }
      }
      if (foundIndex != -1) {
        break;
      }
      ++i;
    }

    for (int l = strlen(line); l > foundIndex; --l) { // Check for second digit linearly backwards
      foundIndex = -1;
      for(int j = 0; j < digitsLength; ++j) {
        if (line[l] == digits[j]) {
          lastDigit = line[l];
          foundIndex = l;
        }
        if (foundIndex != -1) {
          break;
        }
      }
    }

    char str[2]; 
    str[0] = firstDigit; // Some C fuckery necessary to convert a char to a string
    strcpy(numStr, str);
    str[0] = lastDigit;
    strcat(numStr, str);

    unsigned int num = atoi(numStr); // Convert num string to integer
    total += num;
  }

  printf("%d", total);
  fclose(fInput);
  return 0;
}
