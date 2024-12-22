#include<stdio.h>
#include<string.h>
#include<stdbool.h>
int main() {
  char full_numbers[51] = {0};

  scanf("%s", full_numbers);

  char area_code[11] = {0};
  char numbers[41] = {0};

  bool add_area_code = false;
  int area_code_len = 0;

  bool add_numbers = false;
  int numbers_len = 0;
  for (int i = 0; i < strlen(full_numbers); i++) {
    if (add_area_code && full_numbers[i] != ')') {
      area_code[area_code_len] = full_numbers[i];
      area_code_len++;
    }
    if (add_numbers && full_numbers[i] != '-') {
      numbers[numbers_len] = full_numbers[i];
      numbers_len++;
    }
    if (full_numbers[i] == '(') {
      add_area_code = true;
    }
    if (full_numbers[i] == ')') {
      add_numbers = true;
      add_area_code = false;
    }
  }

  printf("area code : %s, tel. : %s", area_code, numbers);
  return 0;
}