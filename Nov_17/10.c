#include<stdio.h>
#include<string.h>
#include<stdbool.h>

struct Bank {
  char bank_name[30];
  int money;
};

typedef struct Bank Bank;

int main() {
  Bank bank[100];
  int count = 0; // Count of bank

  int max_ammount = 0;
  int goal = 0;
  if (scanf("%d", &max_ammount) != 1) {
    printf("Not enough!");
    return 0;
  }
  if (scanf("%d", &goal) != 1) {
    printf("Not enough!");
    return 0;
  }

  char bank_get[30];
  int total = 0;
  int money;
  // Read the bank and money , break when EOF
  while (scanf("%s %d", bank_get, &money) == 2) {
    strcpy(bank[count].bank_name, bank_get);
    bank[count].money = money;
    total += money;
    count++;
}


  if (total < goal) {
    printf("Not enough! 1");
    return 0;
  }
  // Break if there is no input 
  if (count == 0) {
    printf("Not enough! 2");
    return 0;
  }
  if (max_ammount == 0 && goal != 0) {
    printf("Not enough! 3");
    return 0;
  }
  if (goal == 0) {
    printf("0\n");
    printf("%s 0\n", bank[0].bank_name);
    return 0;
  }

  // Sort by money
  for (int i = 0; i < count - 1; i++) {
    for (int j = i + 1; j < count; j++) {
      if (bank[i].money < bank[j].money) {
        Bank temp = bank[i];
        bank[i] = bank[j];
        bank[j] = temp;
      }
    }
  }
  if (max_ammount == 0 && goal == 0) {
    printf("0\n");
    printf("%s 0\n", bank[0].bank_name);
    return 0;
  }

  if (goal == 0) {
    printf("0\n");
    printf("%s 0\n", bank[0].bank_name);
    return 0;
  }

  int sum = 0;
  int bank_needed = 0; // Count of bank needed to meet the goal
  for (int i = 0; i < count && bank_needed < max_ammount; i++) {
    int borrow = bank[i].money;
    if (sum + borrow > goal) {
      borrow = goal - sum;
    }
    sum += borrow;
    bank[i].money = borrow;
    bank_needed++;

    if (sum >= total) break;
  }

  if (bank_needed > max_ammount) {
    printf("Not enough! 4");
    return 0;
  }

  // Situation when the goal is not met
  if (total < goal) {
    printf("Not enough! 5");
    return 0;
  }


  printf("%d\n", bank_needed);
  for (int i = 0; i < bank_needed; i++) {
    printf("%s %d\n", bank[i].bank_name, bank[i].money);
  }

  return 0;
}