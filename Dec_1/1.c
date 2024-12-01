#include <stdio.h>

/* The size of each array will be 21 (because ignore place 0)
If the num we read is three then array[num] will be 1,
otherwise, it will be 0 */

void Union(int a[], int b[]) {
  for (int i = 1; i < 21; i++) {
    if (a[i] == 1 || b[i] == 1) {
      printf("%d ", i);
    }
  }
}

void Intersection(int a[], int b[]) {
  for (int i = 1; i < 21; i++) {
    if (a[i] == 1 && b[i] == 1) {
      printf("%d ", i);
    }
  }
}

void Difference(int a[], int b[]) {
  for (int i = 1; i < 21; i++) {
    if (a[i] == 1 && b[i] == 0) {
      printf("%d ", i);
    }
  }
}

void SymmetricDifference(int a[], int b[]) {
  for (int i = 1; i < 21; i++) {
    if ((a[i] == 1 || b[i] == 1) && a[i] != b[i]) {
      printf("%d ", i);
    }
  }
}

int main() { 
  int a[21] = {0}, b[21] = {0}; 
  int num = 0;

  // Read a
  while (scanf("%d", &num) && num != -1) {
    a[num] = 1;
  }

  // Read b
  while (scanf("%d", &num) && num != -1) {
    b[num] = 1;
  }

  int operation = 0;
  scanf("%d", &operation);

  switch (operation) {
    case 1:
      Intersection(a, b);
      break;
    case 2:
      Union(a, b);
      break;
    case 3:
      SymmetricDifference(a, b);
      break;
    case 4:
      Difference(a, b);
      break;
    default:
      break;
  }

  return 0;
}
