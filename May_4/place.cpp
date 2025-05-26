#include<iostream>

class Person {
 private:
  std::string name;
  std::string place;
 public:
  void SetName(std::string name) {
    this->name = name;
  }
  void SetPlace(std::string place) {
    this->place = place;
  }
};

class DB {
 private:
  Person person[21];
  int count;
 public:
  void AddPerson(std::string name, std::string place) {
    person[count].SetName(name);
    person[count].SetPlace(place);
    count++;
  }
  void FindPerson(std::string place) {
    int found[21];
    int count_found = 0;
    for (int i = 0; i < count; i++) {
      if (person[i].place == place) {
        found[count_found] = i;
        count_found++;
      }
    }
    std::cout << count_found << std::endl;
    for (int i = 0; i < count_found; i++) {
      std::cout << person[found[i]].name << std::endl;
    }
  }
};

int main() {
  DB db;
  std::string name, place;
  std::cin >> name;
  while (name != "-1") {
    std::cin >> place;
    db.AddPerson(name, place);
    std::cin >> name;
  }
  std::cin >> place;
  db.FindPerson(place);
  return 0;
}