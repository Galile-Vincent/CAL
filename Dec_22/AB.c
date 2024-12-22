#include<stdio.h>

int main() {
  int arr1[10] = {0};
  int arr2[10] = {0};

  int num1, num2;
  scanf("%d", &num1);
  scanf("%d", &num2);
  int b = 0;
  int a = 0;

  for (int i = 0; i < 4; i++) {
    int num_of_num1 = num1%10;
    num1 /= 10;

    int num_of_num2 = num2%10;
    num2 /= 10;

    if (num_of_num1 == num_of_num2) {
      a++;
    } else {
      arr1[num_of_num1] = 1;
      arr2[num_of_num2] = 1;
    }
  }
  for (int i = 0; i < 10; i++) {
    if (arr1[i] && arr2[i]) b++;
  }

  printf("%dA%dB", a, b);

  return 0;
}