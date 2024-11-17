#include<stdio.h>
#include<string.h>
#include<stdbool.h>

struct People {
    char name[30];
    char city[30];
};

typedef struct People People;
int main() {
  People people[20];
  int count = 0; // Count of people

  char name[30];
  char city[30];
  scanf("%s", name);

  // Read the name and city , break when name is -1
  while (name != '-1') {
    scanf("%s", city);
    strcpy(people[0].name, name);
    strcpy(people[0].city, city);
    count++;
    scanf("%s", name);
  }

  // Break if there is no input 
  if (count == 0) {
    printf("0");
    return 0;
  }

  // City to search
  char search[30];
  scanf("%s", search);
  
  char people_fit_search[20][30];
  int count_fit = 0;

  for (int i = 0; i < count; i++) {
    if (people[i].city == search) {
        strcpy(people_fit_search[count_fit], people[i].name);
        count_fit++;
    }
  }

  printf("%d", count_fit);
  for (int i = 0; i < count_fit; i++) {
    printf("%s\n", people_fit_search[i]);
  }
  return 0;
}