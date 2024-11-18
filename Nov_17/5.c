#include<stdio.h>
#include<string.h>
#include<stdbool.h>

int Calculator (int num1, int num2, char type) {
    int ans = 0;
    switch (type) {
        case '+':
          return num1 + num2;
          break;
        case '-':
          return num1 - num2;
          break;
        case '*':
          return num1 * num2;
          break;
        case '/':
          return num1 / num2;
          break;
        default:
          break;
    }
}
int main() {
  int num1 = 0;
  int num2 = 0;
  scanf("%d", &num1);
  scanf("%d", &num2);

  char type = ' ';

  // It might have \n
  scanf(" %c", &type);


  int integer_after = Calculator(num1, num2, type);

  // Fix the condition when sum is zero, 0 is the hidden case
  if (integer_after == 0) {
    printf("0");
    return 0;
  }
  // Make the integer to string to inverse
  // 0 1 2 3 4 5 6 7
  // 8 7
  char s[12];
  int place = 0; // Place to add the int to s

  bool is_negative = (integer_after < 0); // Check if the sum is negative

  // Make it back to positive to reverse without negative symbol
  if (is_negative) {
    integer_after *= -1;
  }

  while (integer_after != 0) {
    int num = integer_after % 10;
    s[place] = '0' + num;
    integer_after /= 10;
    place++;
  }

  // Add the negative symbol
  if (is_negative) {
    s[place] = '-';
    place++;
  }
  s[place] = '\0';

  for (int i = 0; i < strlen(s); i++) {
    char ch = s[i];
    printf("%c", s[i]);
  }
  return 0;
}