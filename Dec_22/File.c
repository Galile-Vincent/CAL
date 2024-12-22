#include<stdio.h>
#include<string.h>
#include<stdbool.h>
int main() {
  char name[41] = {0};

  scanf("%s", name);

  int start, end;

  scanf(" %d", &start);
  scanf(" %d", &end);

  // Check valid
  if (start < 0) {
    printf("Input format error : %d\n", start);
    return 0;
  } else if (end < 0) {
    printf("Input format error : %d\n", end);
    return 0;
  } else if (end - start < 0) {
    printf("Input format error : %d\n", end);
    return 0;
  }

  for (int i = start ; i <= end; i++) {
    printf("%s%d\n", name, i);
  }

  return 0;
}