#include <stdio.h>
#include <string.h>
#include <stdbool.h>

struct Bank {
    char bank_name[30];
    int money;
};
typedef struct Bank Bank;

int main() {
    Bank bank[20];
    int count = 0;
    int max_amount = 0;
    int goal = 0;

    // Read max number of banks and goal amount
    if (scanf("%d", &max_amount) != 1) {
        printf("Not enough!");
        return 0;
    }
    if (scanf("%d", &goal) != 1) {
        printf("Not enough!");
        return 0;
    }

    // Handle special cases early
    if (max_amount == 0 && goal != 0) {
        printf("Not enough!");
        return 0;
    }
    if (goal == 0) {
        printf("0\n");
        printf("%s 0", bank[0].bank_name);  // No line return for last line
        return 0;
    }

    char bank_name[30];
    int money;
    int total = 0;

    // Read bank data
    while (1) {
        int result = scanf("%s", bank_name);
        if (result == EOF || result != 1) break;

        result = scanf("%d", &money);
        if (result == EOF || result != 1) break;

        strcpy(bank[count].bank_name, bank_name);
        bank[count].money = money;
        total += money;
        count++;
    }

    // Check if we have enough total money
    if (count == 0 || total < goal) {
        printf("Not enough!");
        return 0;
    }

    // Sort banks by money (descending)
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (bank[i].money < bank[j].money) {
                Bank temp = bank[i];
                bank[i] = bank[j];
                bank[j] = temp;
            }
        }
    }

    // Calculate required loans
    int sum = 0;
    int bank_needed = 0;
    for (int i = 0; i < count && bank_needed < max_amount; i++) {
        int borrow = bank[i].money;
        if (sum + borrow > goal) {
            borrow = goal - sum;
        }
        sum += borrow;
        bank[i].money = borrow;
        bank_needed++;
        if (sum >= goal) break;
    }

    if (sum < goal) {
        printf("Not enough!");
        return 0;
    }

    // Print results
    printf("%d\n", bank_needed);
    for (int i = 0; i < bank_needed; i++) {
        printf("%s %d", bank[i].bank_name, bank[i].money);
        if (i < bank_needed - 1) {
            printf("\n");
        }
    }

    return 0;
}