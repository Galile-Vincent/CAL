#include <iostream>

void Help(int a, int b, int c, int &min, int &max);

int main() {
  int a, b, c, min, max;
  std::cin >> a >> b >> c;
  Help(a, b, c, min, max);
  std::cout << min << "," <<max;
  return 0;
}

void Help(int a, int b, int c, int &min, int &max) {
  if (a < b) {
    min = a;
    max = b;
  } else {
    min = b;
    max = a;
  }
  if (c < min) {
    min = c;
  } else if (c > max) {
    max = c;
  }
}
