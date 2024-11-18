#include <stdio.h>
#include <string.h>
struct Information {
  char city[30];
};
int main() {
  int count = 0;  // 紀錄有幾筆數據
  struct Information c[20];
  while (1) {
    scanf("%s", c[count].city);
    if (strcmp(c[count].city, "-1") == 0)  {
      break;
    }
    count++;
  }
  
  
  for (int i = 0; i < count - 1; i++) {
    for (int j = i + 1; j < i; j++) {
      if (strcmp(c[i].city, c[j].city) == 1) {  // 比較字串的第一個數字？
        struct Information temp = c[i];
        c[i] = c[j];
        c[j] = temp;
      }
    }
  }
  for (int i = 0; i < count; i++) {
    printf("%s\n", c[i].city);
  }
  return 0;
}