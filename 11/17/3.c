#include<stdio.h>
#include<string.h>
int main() {
  int num1 = 0;
  int num2 = 0;
  scanf("%d", &num1);
  scanf("%d", &num2);

  int sum = num1 + num2;
  // Make the integer to string to inverse
  // 0 1 2 3 4 5 6 7
  // 8 7
  char s[12];
  int place = 0; // Place to add the int to s

  if (sum == 0) {
    printf("0");
    return 0;
  }
  while (sum != 0) {
    int num = sum % 10;
    s[place] = '0' + num;
    sum /= 10;
    place++;
  }
  s[place] = '\0';

  int can_print = 0; // If it should print 0
  for (int i = 0; i < strlen(s); i++) {
    char ch = s[i];
    if (ch != '0') {
        can_print = 1;
    }

    if (can_print) {
        printf("%c", s[i]);
    }
  }
  return 0;
}