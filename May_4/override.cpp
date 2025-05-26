#include <iostream>

enum ALIEN_TYPE {
  SNAKE_ALIEN, OGRE_ALIEN, MARSHMALLOW_ALIEN
};

class Alien {
 public:
  virtual int GetDamage() {
    return 0;
  }
  virtual void AttackMessage() {
    std::cout << "Alien attack!" << std::endl;
  }
};

class SnakeAlien : public Alien {
 public:
  int GetDamage() override {
    return 4;
  }
  void AttackMessage() override {
    std::cout << "an snake attacks!" << std::endl;
  }
};

class MarshmallowAlien : public Alien {
 public:
  int GetDamage() override {
    return 1;
  }
  void AttackMessage() override {
    std::cout << "an marshmallow attacks!" << std::endl;
  }
};

class OgreAlien : public Alien {
 public:
  int GetDamage() override {
    return 6;
  }
  void AttackMessage() override {
    std::cout << "an ogre attacks!" << std::endl;
  }
};

class AlienPack {
 private:
  Alien* aliens[100];
  int count;
 public:
  void AddAlien(Alien* alien) {
    aliens[count] = alien;
    count++;
  }
  void Attack() {
    int totalDamage = 0;
    for (int i = 0; i < count; i++) {
      aliens[i]->AttackMessage();
      totalDamage += aliens[i]->GetDamage();
    }
    std::cout << "th total damage is " << totalDamage << "." << std::endl;
  }
};

int main() {
  AlienPack pack;
  int count;
  std::cin >> count;
  for (int i = 0; i < count; i++) {
    std::string type;
    std::cin >> type;
    if (type == "snake") {
      pack.AddAlien(new SnakeAlien());
    } else if (type == "ogre") {
      pack.AddAlien(new OgreAlien());
    } else if (type == "marshmallow") {
      pack.AddAlien(new MarshmallowAlien());
    }
  }
}