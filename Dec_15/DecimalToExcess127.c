#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef char Str9[9];

void DecimalToExcess127(int exponent, Str9 excess127);

int main() {
    
  int exponent;  
  Str9 excess127 = "";

  scanf("%d", &exponent);

  DecimalToExcess127(exponent, excess127); 
  
  printf("Excess127 representation: %s", excess127);

  return 0;
}
void ArrayForward(char arr[], int n) {
  for (int i = n; i > 0; i--) {
    arr[i] = arr[i - 1];
  } 
}

/**
 * convert the exponent to binary representation using excess 127 notation. 
 * i.e., the value is 127 greater than the actual exponent
 * @param
 * @param excess127 store the converted binary string
 */
void DecimalToExcess127(int exponent, Str9 excess127) {
  int convert = 127 + exponent;

  for (int i = 7; i >= 0; i--) {
    excess127[i] = (convert % 2) + '0'; // Add binary digit to the string
    convert /= 2;
  }

  excess127[8] = '\0';
}