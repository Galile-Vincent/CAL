#include <stdio.h>

void Foo(int a[], int n);

int main() { 

  int b[] = {1, 2, 3, 4, 5};

  Foo(b, 5);

  for ( int i = 0; i < 5; i++ ) {
    printf("%d ", b[i]);
  }
  printf("\n");

  Foo(b, 3);

  for ( int i = 0; i < 5; i++ ) {
    printf("%d ", b[i]);
  }
}

void Foo(int a[], int n) {
  for ( int i = 0; i < n; i++ ) {
    a[i] = a[i] + n;
  }
}
