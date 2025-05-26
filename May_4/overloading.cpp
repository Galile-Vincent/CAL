#include <iostream>

int Add(int a, int b) {
  return a + b;
}
int Add(int a, int b, int c) {
  return a + b + c;
}
double Add(double a, double b) {
  return a + b;
}

int main() {
  int a, b, c;
  double d, e;
  std::cin >> a >> b >> c;
  std::cin >> d >> e;
  std::cout << Add(a, b) << std::endl;
  std::cout << Add(a, b, c) << std::endl;
  std::cout << Add(d, e) << std::endl;
  return 0;
}