#include<stdio.h>

/*
case +:
case *:
*/

void Sum(int x, int y, int arr1[x][y], int arr2[x][y]) {
  for (int i = 0; i < x; i++) {
    for (int j = 0; j < y; j++) {
      printf("%d", arr1[i][j] + arr2[i][j]);
      if (j != y - 1) {
        printf(" ");
      }
    }
    printf("\n");
  }
}

void Product(int x, int y, int arr1[x][y], int arr2[x][y]) {
  int arr3[x][x];

  int inverse[y][x];
  for (int i = 0; i < x; i++) {
    for (int j = 0; j < y; j++) {
        inverse[j][i] = arr2[i][j];
    }
  }
  for (int i = 0; i < x; i++) {
    for (int j = 0; j < x; j++) {
      arr3[i][j] = 0; 
      for (int k = 0; k < y; k++) {
          arr3[i][j]+=arr1[i][k]*inverse[k][j];
      }
    }
  }
  for (int i = 0; i < x; i++) {
    for (int j = 0; j < x; j++) {
      printf("%d", arr3[i][j]);
      if (j != x - 1) {
        printf(" ");
      }
    }
    printf("\n");
  }
}

int main() {
  int x = 0;
  int y = 0;
  scanf("%d %d", &x, &y);
  int arr1[x][y];
  int arr2[x][y];
  for (int i = 0; i < x; i++) {
    for (int j = 0; j < y; j++) {
      scanf("%d", &arr1[i][j]);
    }
  }

  for (int i = 0; i < x; i++) {
    for (int j = 0; j < y; j++) {
      scanf("%d", &arr2[i][j]);
    }
  }

  char operator = ' ';
  scanf("%c", &operator);
  while (operator == '\n') {
    scanf("%c", &operator);
  }

  switch (operator) {
    case '+':
      Sum(x, y, arr1, arr2);
      break; 
    case '*':
      Product(x, y, arr1, arr2);
      break;
    default:
      break;
  }

  return 0;
}