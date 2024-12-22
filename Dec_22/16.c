#include<stdio.h>
#include<string.h>
#include<stdbool.h>
int main() {
  char num1[41] = {0};
  char num2[41] = {0};
  scanf("%s", num1);
  scanf("%s", num2);

  int arr1[17] = {0};
  int place1 = 16;
  int place2 = 16;
  int arr2[17] = {0};
  int ans[17] = {0};
  for (int i = strlen(num1) - 1; i >= 0; i--) {
    if (num1[i] <= '9' && num1[i] >= '0') {
      arr1[place1] = num1[i] - '0';
    } else {
      arr1[place1] = num1[i] - 'A' + 10;
    }
    place1--;
  }

  for (int i = strlen(num2) - 1; i >= 0; i--) {
    if (num2[i] <= '9' && num2[i] >= '0') {
      arr2[place2] = num2[i] - '0';
    } else {
      arr2[place2] = num2[i] - 'A' + 10;
    }
    place2--;
  }

  char final_ans[17] = {0};
  int place = 16;
  bool exceed = false;
  while (place >= 0)  {
    int num = arr1[place] + arr2[place];
    if (exceed) {
      num++;
      exceed = false;
    }
    if (num >= 16) {
      num -= 16;
      exceed = true;
    }

    if (num <= 9) {
      final_ans[place] = num + '0';
    } else {
      final_ans[place] = num - 10 + 'A';
    }

    place--;
  }

  bool met_non_zero = false;
  for (int i = 0; i < 17; i++) {
    if (!met_non_zero && final_ans[i] != '0') {
      met_non_zero = true;
    }
    if (met_non_zero) {
      printf("%c", final_ans[i]);
    }
  }
  return 0;
}