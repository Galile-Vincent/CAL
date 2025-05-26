#include<iostream>

class Dog {
 public:
  Dog(int a, int w) {
    age = a;
    weight = w;
  }
  
  explicit Dog(int w) {
    weight = w;
  }

  Dog() {
  }

  void Display() {
    std::cout << "The age of this dog is " << age
              << ". The weight of this dog is " << weight << ".\n";
  }
 private:
  int age = 0;
  int weight = 1;
};

int main() {
  int a, b;
  for (int i = 0; i < 3; i++) {
    std::cin >> a >> b;
    if (i == 0) {
      Dog d(a, b);
      d.Display();
    } else if (i == 1) {
      Dog d(b);
      d.Display();
    } else {
      Dog d;
      d.Display();
    }
  }
  return 0;
}