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

/*
Search for the palce if id
process_code
1 -> balance += money
2 -> balance -= money
*/
void Process(CustomerArray cus_arr, int num_of_data, 
    int id, int process_code, int money) {
  int place = 0;
  for (int i = 0; i < num_of_data; i++) {
    if (cus_arr[i].id == id) {
      place = i;
      break;
    }
  }

  if (process_code == 1) {
    cus_arr[place].balance += money;
  } else if (process_code == 2) {
    cus_arr[place].balance -= money;
  }
}

void Print(CustomerArray cus_arr, int num_of_data, char name[]) {
  bool have_person = false;
  int money = 0;
  for (int i = 0; i < num_of_data; i++) {
    if (strcmp(cus_arr[i].name, name) == 0) {
      money+=cus_arr[i].balance;
      have_person = true;
    }
  }
  
  if (!have_person) {
    printf("No such person!");
  } else {
    printf("%d", money);
  }
}
int main() {
  CustomerArray customer;  // Data of the customer
  int num_of_data; // How many data
  char name[50]; // Name to search

  // step 1: Read all the data until -1
  num_of_data = Read(customer);

  int count = 0;
  int id = 0;
  char process[50];
  int money = 0;
  char break_condition[5] = "-1";
  while (1) {
    scanf("%49s", process);
    scanf("%d", &id);
    scanf("%d", &money);

    if (strcmp(process, break_condition) == 0) break;

    if (strcmp(process, "deposit") == 0) {
      Process(customer, num_of_data, id, 1, money);
    } else if (strcmp(process, "withdraw") == 0) {
      Process(customer, num_of_data, id, 2, money);
    }
  }
  scanf("%49s", name);

  Print(customer, num_of_data, name);
  return 0;
}