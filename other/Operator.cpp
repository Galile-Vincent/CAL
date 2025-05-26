#include <iostream>

using namespace std;
/**
 * operate input1 and input2 according to the operator.
 * @param way_of_use operator. Could be +,-,*,/,%
 * @param input1 the first input
 * @param input2 the second input
 * @param result the result
 */
void Operate(char op, int input1, int input2, int & result); 

int main() {
  char op;
  int input1, input2;
  int result;
  cin >> op;
  cin >> input1;
  cin >> input2;
  Operate(op, input1, input2, result);
  printf("%d", result);
  return 0;
}

void Operate(char op, int input1, int input2, int & result) {
  switch (op) {
    case '+':
      result = input1 + input2;
      break;
    case '-':
      result = input1 - input2;
      break;
    case '*':
      result = input1 * input2;
      break;
    case '/':
      if (input2 == 0) {
        return;
      }
      result = input1 / input2;
      break;
    case '%':
      if (input2 == 0) {
        return;
      }
      result = input1 % input2;
      break;
    default:
      return;
  }
}