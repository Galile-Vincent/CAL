#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

typedef char Str40[40];  // 長度40的字元陣列型別 

typedef struct {
  bool non_negative;
  int decimal;
  int int_of_fraction;
  int num_digits;
} FloatInfo;

FloatInfo FractionStrAnalysis(Str40 float_str);

int main() {

  Str40 input_string = "";
  scanf("%s", input_string);

  FloatInfo info = FractionStrAnalysis(input_string);

  printf("%d %d %d %d", info.non_negative, info.decimal,
      info.int_of_fraction, info.num_digits);
  return 0;
}

FloatInfo FractionStrAnalysis(Str40 float_str) {
  FloatInfo Info;
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

  Info.decimal = int_before_dot;
  Info.int_of_fraction = int_after_dot;
  Info.non_negative = !is_negative;
  Info.num_digits = count_digits;
  return Info;
}