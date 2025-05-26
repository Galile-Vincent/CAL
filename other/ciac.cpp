#include<iostream>
/*
狗的體重如果超過30，就要印出 Woof!Woof!
狗的體重如果介於11~30，就要印出 Yip!Yip!
狗的體重如果小於等於10，就要印出 Meow~
*/
using namespace std;
class Dog {
 public:
  int weight;

  void Bark() {
    if (weight > 20) {
      cout << "Wooof!Woof!" << endl;
    } else if (weight > 10) {
      cout << "Yip!Yip!" << endl;
    } else {
      cout << "Meow~" << endl;
    }
  }
};

int main() {
  Dog dog1, dog2;
  cin >> dog1.weight;
  cin >> dog2.weight;
  dog1.Bark();
  dog2.Bark();
  return 0;
}