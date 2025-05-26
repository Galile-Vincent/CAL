#include <iostream>

class Dog {
 private:
  int weight;

 public:
  void SetWeight(int w) {
    weight = w;
  }

  int GetWeight() {
    return weight;
  }

  void Bark();
};

int main() {
  Dog d;
  int desired_weight;
  std::cin >> desired_weight;
  d.SetWeight(desired_weight);
  d.Bark();
}

void Dog::Bark() {
  if (weight > 30) {
    std::cout << "Woof!Woof!" << std::endl;
  } else if (weight > 10) {
    std::cout << "Yip!Yip!" << std::endl;
  } else {
    std::cout << "Meow~" << std::endl;
  }
}