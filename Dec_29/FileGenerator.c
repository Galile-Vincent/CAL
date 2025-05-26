#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include<stdlib.h>

bool IsNumber(char name[21]) {
  if (name[0] >= '0' && name[0] <= '9') {
    return true;
  } else if (name[1] >= '0' && name[1] <= '9' && name[0] == '-') {
    return true;
  }
  return false; 
}

int Convert(char name[21]) {
  int num = 0;
  int start = 0;
  if (name[0] == '-') {
    start = 1;
  }
  for (int i = start; i < strlen(name); i++) {
    num*=10;
    num+=(name[i] - '0');
  }
  if (start == 1) num*=-1;
  return num;
}
int main() {
  char full_name[101] = {0};
  char name[21] = {0};
  int start, end;
  bool got_start = false;
  while (true) {
    scanf("%s", name);
    if (IsNumber(name) && !got_start) {
      start = Convert(name);
      got_start = true;
    } else if (IsNumber(name) && got_start) {
      end = Convert(name);
      break;
    } else {
      strcat(full_name, name);
    }
  }

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
    printf("%s%d\n", full_name, i);
  }

  return 0;
}