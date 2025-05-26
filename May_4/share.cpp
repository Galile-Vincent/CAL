#include <iostream>




int main() {
  Car car1, car2;
  car2.ShowSpeed();
  int flag;
  std::cin >> flag;
  if (flag == 1) {
    Car car3;
    car3.ShowSpeed();
    Car car4;
    car4.ShowSpeed();
  }

  for (int i = 0; i < 2; i++) {
    Car c;
    c.ShowSpeed();
  }
  
  Car * c[5];
  for (int i = 0; i < 5; i++) {
    c[i] = new Car;
    c[i]->ShowSpeed();
  }
  for (int i = 0; i < 5; i++) {
  delete c[i];   
  }
}