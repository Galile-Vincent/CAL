#include <stdio.h>
#include <stdbool.h>

#define count 3

// Check vertical
int CheckVertical(int arr[count][count]) {
  // 0 no winner in vertical
  int winner = 0;
  for (int i = 0; i < count; i++) {
    if (arr[0][i] != 0 && (arr[0][i] == arr[1][i] && arr[0][i] == arr[2][i])) {
      winner = arr[0][i];
      break;
    }
  }
  return winner;
}

// Check horizotal
int CheckHorizontal(int arr[count][count]) {
  // 0 no winner in Horizontal
  int winner = 0;
  for (int i = 0; i < count; i++) {
    if (arr[i][0] != 0 && (arr[i][0] == arr[i][1] && arr[i][0] == arr[i][2])) {
      winner = arr[i][0];
      break;
    }
  }
  return winner;
}
// Check x
int CheckX(int arr[count][count]) {
  // 0 no winner in X
  int winner = 0;
  if (arr[0][0] == arr[1][1] && arr[0][0] == arr[2][2]) {
    if (arr[0][0] != 0) winner = arr[0][0];
  }
  if (arr[0][2] == arr[1][1] && arr[1][1] == arr[2][0]) {
    if (arr[0][2] != 0) winner = arr[0][2];
  }
  return winner;
}
int main() {
  int arr[count][count];
  for (int i = 0; i < count; i++) {
    for (int j = 0; j < count; j++) {
      scanf("%d", &arr[i][j]);
    }
  }
  int winner = 0;
  // If return 0 means no winner
  // Else means have winner so return instead
  winner = CheckHorizontal(arr);
  if (winner != 0) {
    printf("%d", winner);
    return 0;
  }
  winner = CheckVertical(arr);
  if (winner != 0) {
    printf("%d", winner);
    return 0;
  }
  winner = CheckX(arr);
  if (winner != 0) {
    printf("%d", winner);
    return 0;
  }
  printf("3"); // No winner
  return 0;
}