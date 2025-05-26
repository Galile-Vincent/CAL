#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

char * Concatenate(const char * str1, const char * str2);

int main() {
  char * s1;
  char * s2;
  char * s3;
  int op;
  s1 = malloc(sizeof(char)*100);
  s2 = malloc(sizeof(char)*100);
  scanf("%99s", s1);
  scanf("%99s", s2);
  s3 = Concatenate(s1, s2);
  if (s3 != NULL) {
    if (s3 == s1 || s3 == s2) {
      printf("Invalid operation!");
    } else {
      printf("%s", s3);
    }
  } 
  return 0;
}

char * Concatenate(const char * str1, const char * str2) {
  
}