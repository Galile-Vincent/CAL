#include <stdio.h>
#include <string.h>

struct Bank {
  char bank_name[30];
  int money;
};

typedef struct Bank Bank;

int main() {
  Bank bank[100];
  int count = 0;  // Count of banks read

  int max_ammount, goal;
  if (scanf("%d %d", &max_ammount, &goal) != 2) {
    printf("Not enough!");
    return 0;
  }

  int total = 0;
  char bank_get[30];
  int money;

  // Read banks and loan amounts until EOF
  while (scanf("%s %d", bank_get, &money) == 2) {
    strcpy(bank[count].bank_name, bank_get);
    bank[count].money = money;
    total += money;
    count++;
  }

  // Check if total loans available are insufficient
  if (total < goal) {
    printf("Not enough!");
    return 0;
  }

  // Handle edge case where no borrowing is required
  if (goal == 0) {
    printf("0\n");
    return 0;
  }

  // Sort banks by loan amount (descending order) using nested loops
  for (int i = 0; i < count - 1; i++) {
    for (int j = i + 1; j < count; j++) {
      if (bank[i].money < bank[j].money) {
        Bank temp = bank[i];
        bank[i] = bank[j];
        bank[j] = temp;
      }
    }
  }

  int sum = 0;
  int bank_needed = 0;  // Count of banks needed to meet the goal

  // Borrow from banks in sorted order
  for (int i = 0; i < count && bank_needed < max_ammount; i++) {
    int borrow = bank[i].money;

    // Adjust the borrow amount if it exceeds the remaining goal
    if (sum + borrow > goal) {
      borrow = goal - sum;
    }

    sum += borrow;
    bank[i].money = borrow;  // Update the bank's loan amount to reflect the borrowing
    bank_needed++;

    // Break if the goal is met
    if (sum >= goal) break;
  }

  // If the total borrowed amount is still less than the goal, print "Not enough!"
  if (sum < goal) {
    printf("Not enough!");
    return 0;
  }

  // Output the result
  printf("%d\n", bank_needed);
  for (int i = 0; i < bank_needed; i++) {
    printf("%s %d\n", bank[i].bank_name, bank[i].money);
  }

  return 0;
}
