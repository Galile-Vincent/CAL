#include <stdio.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int main() {
    int count, volume;
    scanf("%d", &count);
    scanf("%d", &volume);

    int weight_arr[count], value_arr[count];
    for (int i = 0; i < count; i++) {
        scanf("%d %d", &weight_arr[i], &value_arr[i]);
    }

    int all_case[count + 1][volume + 1];
    // Initialize all entries to 0
    for (int i = 0; i <= count; i++) {
        for (int j = 0; j <= volume; j++) {
            all_case[i][j] = 0;
        }
    }

    // Fill the DP table
    for (int i = 1; i <= count; i++) {  // Items
        for (int j = 1; j <= volume; j++) {  // Capacity
            // Check if current item's weight fits
            if (weight_arr[i - 1] <= j) {
                // Max of including item vs excluding item
                all_case[i][j] = max(value_arr[i - 1] + all_case[i - 1][j - weight_arr[i - 1]],
                                    all_case[i - 1][j]);
            } else {
                // If it doesn't fit, take value without current item
                all_case[i][j] = all_case[i - 1][j];
            }
        }
    }

    printf("%d", all_case[count][volume]);
    return 0;
}