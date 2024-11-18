#include<stdio.h>
/*
a b -> c, d
3 4 -> 7, -1
8 0 -> 8 12
*/
#define END_STR "CYCUICE"
#define PLUS(a, b) a + b
#define MINUS(a, b) (a - b)


int main() {
  int a = 0, b = 0;
  scanf("%d%d", &a, &b);
  int c = PLUS(a, b);
  int d = 3 * MINUS(a, b) / 2;
  printf("%d, %d\n", c, d);
  printf("%s", END_STR);
  return 0;
}