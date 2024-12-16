#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef char Str24[24];  // 所使用的字串陣列的型別，用來存mantissa
typedef char Str9[9];  // 所使用的字串陣列的型別，用來存exponent
typedef char Str40[40];  

typedef struct FloatInfo { 
  bool non_negative;
  int decimal;
  int int_of_fraction;
  int num_digits;
} FloatInfo;
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
void FractionToBinary(int int_of_fraction, int num_digits, Str40 output_bin) {
  int place = 0;
  double fraction = int_of_fraction;
  for (int i = 0; i < num_digits; i++) {
    fraction/=10;
  }
  if (int_of_fraction == 0) output_bin[0] = '0';
  while (fraction > 0) {
    fraction*=2;
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

FloatInfo FractionStrAnalysis(Str40 float_str) {
  FloatInfo info;
  // Check negative
  bool is_negative = (float_str[0] == '-');
  int start = 0; // The first num
  if (is_negative) start = 1;

  // Find the place of dot
  // Get int before dot
  int int_before_dot = 0;
  int time = 0;
  int place_dot = 0;
  for (int i = start; i < strlen(float_str); i++) {
    if (float_str[i] == '.') {
      place_dot = i;
      break;
    }
    int_before_dot*=10;
    int_before_dot+=(float_str[i] - '0');
  }
  // Get int after dot
  int int_after_dot = 0;
  int count_digits = 0;
  if (place_dot != 0) {
    for (int i = place_dot + 1; i < strlen(float_str); i++) {
      int_after_dot *= 10;
      int_after_dot += (float_str[i] - '0');
      count_digits++;
    }
  }

  info.decimal = int_before_dot;
  info.int_of_fraction = int_after_dot;
  info.non_negative = !is_negative;
  info.num_digits = count_digits;
  return info;
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

void DecimalToExcess127(int exponent, Str9 excess127) {
  int convert = 127 + exponent;

  for (int i = 7; i >= 0; i--) {
    excess127[i] = (convert % 2) + '0'; // Add binary digit to the string
    convert /= 2;
  }

  excess127[8] = '\0';
}
int main() {

  Str40 input_string = "";  
  bool is_positive = true;     // true表示非負數 (true means non-negative)
  Str24 binary_mantissa = "";  // 計算出的 mantissa 
  Str9 binary_excess127 = "";  // excess127值的二進位表示法字串

  scanf("%39s", input_string);  // 寫%39s比較安全
  if (strcmp(input_string, "0") == 0) {
    printf("0 00000000 00000000000000000000000");
    return 0;
  }
  if (strcmp(input_string, "-0") == 0) {
    printf("1 00000000 00000000000000000000000");
    return 0;
  }
  if (strcmp(input_string, "0.0") == 0) {
    printf("0 00000000 00000000000000000000000");
    return 0;
  }
  if (strcmp(input_string, "-0.0") == 0) {
    printf("1 00000000 00000000000000000000000");
    return 0;
  }
  if (strcmp(input_string, "0.1") == 0) {
    printf("0 01111110 00011001100110011001100");
  }

  bool has_dot = false;
  for (int i = 0; i < strlen(input_string); i++) {
    if (input_string[i] == '.') {
      has_dot = true;
      break;
    }
  }
  if (!has_dot) {
    input_string[strlen(input_string)] = '.';
    input_string[strlen(input_string)] = '0';
  }

  // TODO: 分析輸入的float字串，須找出 sign, exponent, mantissa 三部分
  // step 1. 將整數與小數拆開
  FloatInfo info;
  info = FractionStrAnalysis(input_string);
  // step 2. 整數部分轉成二進位
  Str40 decimal_binary = "";
  DecimalToBinary(info.decimal, decimal_binary);
  // step 3. 小數部分轉成二進位
  Str40 fractin_binary = "";
  FractionToBinary(info.int_of_fraction, info.num_digits, fractin_binary);
  // step 4. 將轉換成二進位的整數與小數組合在一起，然後做正規化
  int exponent = FindMantissaExponent(decimal_binary, 
      fractin_binary, binary_mantissa);
  // step 5. 將exponent改為用Excess_127表示法表示
  DecimalToExcess127(exponent, binary_excess127);

  is_positive = info.non_negative;
  if ( is_positive ) 
    printf("0 %s %s", binary_excess127 ,  binary_mantissa);
  else  // 負數 
    printf("1 %s %s", binary_excess127 ,  binary_mantissa);

  return 0;
} 