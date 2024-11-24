#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef char Str50[50];  // 新型別；一個可存放50字元的陣列

struct Customer {
  int id;  // 客戶編號
  Str50 name;  // 名字
  int balance;  // 存款
};

typedef struct Customer CustomerArray[200];

int Read(CustomerArray cus_arr) {
  int count = 0;
  int id = 0;
  char name[50];
  int balance = 0;
  char break_condition[5] = "-1";
  while (1) {
    if (count >= 200) break;
    scanf("%49s", name);
    scanf("%d", &id);
    scanf("%d", &balance);
    if (strcmp(name, break_condition) == 0)
      break;

    cus_arr[count].id = id;
    strcpy(cus_arr[count].name, name);
    cus_arr[count].balance = balance;
    count++;
  }
  return count;
}

void Print(CustomerArray cus_arr, int num_of_data, char name[]) {
  bool have_person = false;
  for (int i = 0; i < num_of_data; i++) {
    if (strcmp(cus_arr[i].name, name) == 0) {
      printf("%d", cus_arr[i].balance);
      have_person = true;
      break;
    }
  }
  if (!have_person) {
    printf("No such person!");
  }
}
int main() {
  CustomerArray customer;  // Data of the customer
  int num_of_data; // How many data
  char name[50]; // Name to search

  // step 1: Read all the data until -1
  num_of_data = Read(customer);

  scanf("%49s", name);

  Print(customer, num_of_data, name);
  return 0;
}