#include<stdio.h>

int main() {
  int n = 0;
  scanf("%d", &n);
  int arr[n][n];

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      scanf("%d", &arr[i][j]);
    }
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (arr[i][j] != arr[j][i]) {
        printf("0");
        return 0;
      }
    }
  }

  printf("1");
  return 0;
}