#include <iostream>
#include <string>

/**
 * Create a simple calculator. The user input an option
 * and then input two numbers. 
 * possibilities of option: 
 * 0: quit
 * 1: add two integers  2: subtract two integers
 * 3: multiply two integers 4: divide two integers
 * 5: add two doubles  6: subtract two doubles
 * 7: multiply two doubles 8: divide two doubles
 */

int Add(int a, int b) {
  return a + b;
}
int Subtract(int a, int b) {
  return a - b;
}
int Multiply(int a, int b) {
  return a * b;
}
int Divide(int a, int b) {
  if (b == 0) {
    std::cout << "Error: Division by zero" << std::endl;
    return 0;
  }
  return a / b;
}

double Add(double a, double b) {
  return a + b;
}
double Subtract(double a, double b) {
  return a - b;
}
double Multiply(double a, double b) {
  return a * b;
}
double Divide(double a, double b) {
  if (b == 0) {
    std::cout << "Error: Division by zero" << std::endl;
    return 0;
  }
  return a / b;
}

void Operate(int option) {
  if (option == 0) {
    return;
  }
  if (option < 1 || option > 8) {
    std::cout << "Invalid option" << std::endl;
    return;
  }
  double a, b;
  int x, y;
  if (option < 5) {
    std::cin >> x >> y;
  } else {
    std::cin >> a >> b;
  }

  switch (option) {
    case 1:
      std::cout << Add(x, y) << std::endl;
      break;
    case 2:
      std::cout << Subtract(x, y) << std::endl;
      break;
    case 3:
      std::cout << Multiply(x, y) << std::endl;
      break;
    case 4:
      std::cout << Divide(x, y) << std::endl;
      break;
    case 5:
      std::cout << Add(a, b) << std::endl;
      break;
    case 6:
      std::cout << Subtract(a, b) << std::endl;
      break;
    case 7:
      std::cout << Multiply(a, b) << std::endl;
      break;
    case 8:
      std::cout << Divide(a, b) << std::endl;
      break;
    default:
      break; // This should never happen
  }
}

int main() {
  int option = -1;
  std::cin >> option;

  while ( option != 0 ) {
    Operate(option);
    std::cin >> option;
  }
  return 0;
}
