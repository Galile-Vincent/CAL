#include <iostream>

using namespace std;

struct Customer {
  int id;  // 客戶編號
  char name[20];  // 名字
  int balance;  // 存款
};

int main() {
  Customer customers[11];
  int input = 0;
  int count = 0;
  int max = 0;
  cin >> input;
  while (input != -1) {
    customers[count].id = input;
    cin >> customers[count].name;
    cin >> customers[count].balance;
    if (customers[count].balance > max) {
      max = customers[count].balance;
    }
    cin >> input;
  }

  for (int i = 0; i < count; i++) {
    if (customers[i].balance == max) {
      cout << customers[i].id << " " << customers[i].name << " " << customers[i].balance << endl;
    }
  }
  return 0;
}