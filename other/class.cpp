#include <iostream>

class Student {
 public:
  float height;
  float weight;
  char name[20];
  int age;

  void ShowStatistics() {
    std::cout << name << "'s age is " << age << ", height is " << height
              << std::endl;
  }
};

int main() {
  Student student1, student2;
  std::cin >> student1.height >> student1.age >> student1.name;
  std::cin >> student2.height >> student2.age >> student2.name;

  std::cout << student1.name << "'s age is " << student1.age
            << ", height is " << student1.height << std::endl;
  std::cout << student2.name << "'s age is " << student2.age
            << ", height is " << student2.height << std::endl;
  return 0;
}