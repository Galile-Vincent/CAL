#include<stdio.h>
#include<string.h>
#include<stdbool.h>

// https://www.ibm.com/docs/zh-tw/uax?topic=functions-strcmp
/*
strcmp
ABC	    ABC	 0
abc	    ABC	 1
ABC	    abc	-1
阿布克德 abc  1
*/

typedef char Data[30];

int main() {
  Data cities[30];
  int count_city = 0;

  char city[30];
  scanf("%s", city);

  while (strcmp(city, '-1') != 0) {
    strcpy(cities[count_city], city);
    count_city++;
    scanf("%s", city);
  }

  if (count_city == 0) {
    return 0;
  }

  for (int i = count_city - 1; i >= 0; i--) {
      printf("%s\n", cities[i]);
  }
      return 0;
}