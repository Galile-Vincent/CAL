#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  char name[30][51];
  int total = 0;
  int position = 0;
  int full = 0;
  char answer[30][51];
  char temp[30][51];

  for (int i = 0; i < 30; i++) {
    scanf("%50s", name[i]);
    if (strcmp(name[i] , "END_OF_EVERYTHING") == 0) {
      if (i == 0)  return 0;
      break;
    }
    total++;
  }

  for (int j = 1; j < total; j++) {
    if (strcmp(name[j] , ";") != 0) {
      if (strlen(name[j + 1]) != 0) {
        strcat(name[position], " ");
        strcat(name[position], name[j]);
      }
    }

    else {
      strcpy(answer[full], name[position]);
      full++;
      position = j + 1;
      j++;
    }
  }

  for (int i = 0; i < full - 1; i++) {
    for (int j = i + 1; j < full; j++) {
      if (strcmp(answer[j], answer[i]) < 0) {
        strcpy(temp[i], answer[i]);
        strcpy(answer[i], answer[j]);
        strcpy(answer[j], temp[i]);
      }
    }
  }

  for (int c = 0; c < full; c++) {
    printf("%s\n", answer[c]);
  }
}