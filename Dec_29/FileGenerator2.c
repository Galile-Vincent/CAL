#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include<stdlib.h>

bool IsNumber(char name[31]) {
  if (name[0] >= '0' && name[0] <= '9') {
    return true;
  } else if (name[1] >= '0' && name[1] <= '9' && name[0] == '-') {
    return true;
  }
  return false; 
}

int Convert(char name[31]) {
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
/*
Check if it has ','
True -> remove the ','
False -> move the last to the first
*/
int main() {
  char full_name[151] = {0};
  char name[5][31] = {0};
  int count_name = 0;
  int start, end;
  bool got_start = false;
  while (true) {
    char input[31] = {0};
    scanf("%s", input);
    if (IsNumber(input) && !got_start) {
      start = Convert(input);
      got_start = true;
    } else if (IsNumber(input) && got_start) {
      end = Convert(input);
      break;
    } else {
      strcpy(name[count_name], input);
      count_name++;
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

  // Check if it has ','
  if (name[0][strlen(name[0]) - 1] == ',') {
    name[0][strlen(name[0]) - 1] = '\0';
  } else {
    char last[31] = {0};
    strcpy(last, name[count_name - 1]);
    for (int i = count_name - 1; i >= 1; i--) {
      strcpy(name[i], name[i - 1]);
    }
    strcpy(name[0], last);
  }

  for (int i = start ; i <= end; i++) {
    for (int j = 0; j < count_name; j++) {
      printf("/%s", name[j]);
    }
    printf("%d\n", i);
  }

  return 0;
}