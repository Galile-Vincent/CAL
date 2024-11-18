#include<stdio.h>
#include<string.h>
#include<stdbool.h>

/*
1. get old and new
2. read string
3. split string by space

read till EOF
char old[40]
char new[40]

Data[50]
Data str[40]
*/
typedef char Data[50];

int main() {
  Data str[40];
  
  char old[40];
  char new[40];

  scanf("%s", old);
  scanf("%s", new);

  char get[40];

  int place = 0; // The place of the Data
  int changed = 0; // Time that the Data has been changed

  while (scanf("%s", get) != EOF) {
    bool isOld = strcmp(get, old) == 0;

    if (isOld) {
        strcpy(str[place], new);
        changed++;
    } else {
        strcpy(str[place], get);
    }
    place++;
  }

  printf("%d\n", changed);
  for (int i = 0; i < place; i++) {
    printf("%s\n", str[i]);
  }
}