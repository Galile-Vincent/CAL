#include<iostream>
#include<string>

enum Type {
  A, B, Other
}

class Student {
 private:
  std::string id;
  Type class_type
 public:
  void ReadId(std::string id) {
    this->id = id;
  }
  void CheckId() {
    int stu_id = id - '0';
    if (stu_id >= 11227101 && stu_id <= 11227170) {
      this->Type = Type.A;
    } else if (stu_id >= 11227201 && stu_id <= 11227270) {
      this->Type = TYpe.B;
    } else {
      this->Type = Type.Other;
    }
    PrintInfo();
  }
  void PrintInfo() {
    if (class_type == Type.A) {
      std::cout << id << "就讀的班級是甲班" << std::endl;
    } else if (class_type == Type.B) {
      std::cout << id << "就讀的班級是乙班" << std::endl;
    } else {
      std::cout << id << "就讀的班級是外星人的班級" << std::endl;
    }
  }
};


int main() {
  Student stu;
  std::string id;
  std::cin >> id;
  while(id.compare("-1")) {
    stu.ReadId(id);  // 讀進使用者輸入的學號
    stu.CheckId();  // 判斷此學號是屬於哪一個班級並印出結果
    std::cin >> id;
  }
  return 0;
}