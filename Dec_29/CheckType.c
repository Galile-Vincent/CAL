#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool IsNumber(char ch) {
  return (ch >= '0' && ch <= '9');
}

bool IsAlphabet(char ch) {
  return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

int main() {
  char input[21] = {0};
  scanf("%20s", input);
  int length = strlen(input);
  if (length == 0) {
    return 0;
  }
  if (IsAlphabet(input[0]) || input[0] == '_') {
    bool is_identifier = true;
    for (int i = 1; i < length; i++) {
      if (!(IsNumber(input[i]) || IsAlphabet(input[i]))) {
        is_identifier = false;
        break;
      }
    }
    if (is_identifier) {
      printf("%s is an identifier.", input);
      return 0;
    }
  }
  int start = 0;
  bool has_sign = false;
  bool has_dot = false;
  bool is_floating = false;
  if (input[0] == '-' || input[0] == '+') {
    has_sign = true;
    start++;
    if (length == 1) {
      printf("%s is a string.", input);
      return 0;
    }
  }
  bool is_number = true;
  for (int i = start; i < length; i++) {
    if (input[i] == '.') {
      if (has_dot) {
        is_number = false;
        break;
      }
      has_dot = true;
      if (i == start || i == length - 1) {
        is_number = false;
        break;
      }
      is_floating = true;
    } else if (!IsNumber(input[i])) {
      is_number = false;
      break;
    }
  }
  if (is_number) {
    if (is_floating) {
      printf("%s is a floating number.", input);
    } else {
      printf("%s is an integer.", input);
    }
    return 0;
  }
  printf("%s is a string.", input);
  return 0;
}
