#include <iostream>

// TODO: put your classes here

class Vehicle {
 public:
  void Move() {
    std::cout << "moving." << std::endl;
  }
  void Brake() {
    std::cout << "stop." << std::endl;
  }
  void Open() {
    std::cout << "open the door." << std::endl;
  }
};

class Truck : public Vehicle {
 public:
  Truck();
};
class Bus : public Vehicle {
 public:
  Bus();
};
class Car : public Vehicle {
 public:
  Car();
};
class Motor : public Vehicle {
 public:
  Motor();
};

int main() {
  Truck t;
  Bus b;
  Car c;
  Motor m;
  t.Move();
  b.Move();
  c.Move();
  m.Move();
  t.Brake();
  b.Brake();
  c.Brake();
  m.Brake();
  b.Open();
  c.Open();
  return 0;
}