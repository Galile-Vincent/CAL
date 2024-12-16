#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef char Str40[40]; 

void DecimalToBinary(int input_num, Str40 output_num);

int main() {

  int decimal;
  Str40 binary_decimal = "";  // 二進位表示法字串

  scanf("%d", &decimal);  // 輸入要轉換的整數

  DecimalToBinary(decimal, binary_decimal); 
  
  printf("%s", binary_decimal);

  return 0;
}

void ArrayForward(char arr[], int n) {
  for (int i = n; i > 0; i--) {
    arr[i] = arr[i - 1];
  } 
}

void DecimalToBinary(int input_num, Str40 output_num) {
  int place = 0;
  if (input_num == 0) output_num[0] = '0';
  while (input_num > 0) {
    int remain = input_num % 2;
    input_num/=2;
    ArrayForward(output_num, place + 1);
    output_num[0] = '0' + remain;
    place++;
  }
}