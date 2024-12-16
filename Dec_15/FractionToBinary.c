#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

typedef char Str40[40];  // 長度40的字元陣列型別 

void FractionToBinary(int int_of_fraction, int num_digits, Str40 output_bin);

int main() {
  int int_of_fraction;  
  int num_digits; 
  Str40 binary = "";  // 二進位小數表示法字串，不包含小數點及之前的部分
  scanf("%d%d", &int_of_fraction, &num_digits);

  FractionToBinary(int_of_fraction, num_digits, binary);

  printf("Binary representation: %s", binary); 
  return 0;
}

/**
 * Convert the fractional part (e.g. 0.0423) of a floating-point number (e.g. 35.0423) into 
 * a binary representation string.
 * @param input_num the integer of a fraction (for 0.0423, the value is 423)
 * @param num_digits valid number of digits after the decimal point (for 0.0423, the value is 4)
 * @param output_bin the binary representation string
 */
void FractionToBinary(int int_of_fraction, int num_digits, Str40 output_bin) {
  int place = 0;
  double fraction = int_of_fraction;
  for (int i = 0; i < num_digits; i++) {
    fraction/=10;
  }
  if (int_of_fraction == 0) output_bin[0] = '0';
  while (fraction > 0) {
    fraction*=2;
    printf("%f\n", fraction);
    if (fraction >= 1.0) {
      output_bin[place++] = '1';
      fraction -= 1.0;
    } else {
      output_bin[place++] = '0';
    }
    if (fraction == 0) break;
    if (place == 10) break;
  }
}