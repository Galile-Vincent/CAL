#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef char Str40[40];
typedef char Str24[24];

int FindMantissaExponent(Str40 input_decimal, Str40 input_fraction, 
    Str24 mantissa);

int main() {

  Str40 binary_fraction = "";  // 輸入的二進位小數部字串，不包含小數點
  Str40 binary_decimal = "";   // 輸入的二進位整數部
  Str40 mantissa = "";
  int exponent = 0;

  scanf("%s", binary_decimal);
  scanf("%s", binary_fraction);

  exponent = FindMantissaExponent(binary_decimal, binary_fraction , mantissa); 

  printf("mantissa: %s; exponent: %d", mantissa, exponent);  
  return 0;  
}

/**
 * normalize the binary representation of a floating point number and 
 * compute the mantissa and exponent.
 * @param input_decimal the binary representation of the whole number part 
 *                    (e.g. for 35.0423, the value is 100011)
 * @param mantissa the binary representation of the fractional part 
 *                    (e.g, for 35.0423, the value is 0000101011
 * @return the exponent value. This value is the exponent term 
 *        after normalization
 */
int FindMantissaExponent(Str40 input_decimal, Str40 input_fraction, 
    Str24 mantissa) {
  // Special case no 1 at left
  bool special_case = (strlen(input_decimal) == 1 && input_decimal[0] == '0');

  // Find the first one & Find exponent
  int first_one = 0;
  int exponent = 0;
  if (special_case) {
    // Find right. Special case
    for (int i = 0; i < strlen(input_fraction); i++) {
      if (input_fraction[i] == '1') {
        first_one = i;
        break;
      }
    }
    exponent = (first_one * -1) - 1;
  } else {
    // Find left. Normal case
    for (int i = 0; i < strlen(input_decimal); i++) {
      if (input_decimal[i] == '1') {
        first_one = i;
        break;
      }
    }
    exponent = strlen(input_decimal) - first_one - 1;
  }

  
  // Initial mantissa with 0
  for (int i = 0 ; i < 23; i++) {
    mantissa[i] = '0';
  }
  mantissa[23] = '\0';


  int place_mantissa = 0;
  if (!special_case) {
    for (int i = first_one + 1; i < strlen(input_decimal); i++) {
      mantissa[place_mantissa] = input_decimal[i];
      place_mantissa++;
    }
  }
  int start_of_fraction = 0;
  if (special_case) start_of_fraction = first_one + 1;
  for (int i = start_of_fraction; i < strlen(input_fraction); i++) {
    mantissa[place_mantissa] = input_fraction[i];
    place_mantissa++;
  }

  return exponent;
} 