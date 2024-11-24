#include <stdio.h>
#include <stdbool.h>

bool BiggerUp(int i, int j, int x, int y, int arr[x][y]) {
  if (i == 0) { // if is the first row
    return true;
  } else {
    return (arr[i][j] > arr[i - 1][j]);
  }
}

bool BiggerDown(int i, int j, int x, int y, int arr[x][y]) {
  if (i == x - 1) { // if is the last row
    return true;
  } else {
    return (arr[i][j] > arr[i + 1][j]);
  }
}

bool BiggerRight(int i, int j, int x, int y, int arr[x][y]) {
  if (j == y - 1) {
    return true;
  } else {
    return (arr[i][j] > arr[i][j + 1]);
  }
}

bool BiggerLeft(int i, int j, int x, int y, int arr[x][y]) {
  if (j == 0) {
    return true;
  } else {
    return (arr[i][j] > arr[i][j - 1]);
  }
}
int main() {
  int x, y;
  scanf("%d %d", &x, &y);
  int arr[x][y];

  // Get the arr elements
  for (int i = 0; i < x; i++) {
    for (int j = 0; j < y; j++) {
      scanf("%d", &arr[i][j]);
    }
  }

  for (int i = 0; i < x; i++) {
    for (int j = 0; j < y; j++) {
      bool down = BiggerDown(i, j, x, y, arr);
      bool up = BiggerUp(i, j, x, y, arr);
      bool left = BiggerLeft(i, j, x, y, arr);
      bool right = BiggerRight(i, j, x, y, arr);
      if (down && up && left && right) {
        printf("%d\n", arr[i][j]);
      }
    }
  }

  return 0;
}