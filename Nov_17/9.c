#include<stdio.h>
#include<string.h>
#include<stdbool.h>

struct Subsidy {
  char city[30];
  int money;
};

typedef struct Subsidy Subsidy;
typedef char City[15];
int main() {
  Subsidy subsidy[20];
  int count = 0; // Count of people

  char city[30];
  scanf("%s", city);

  // Read the city and money , break when city is END
  while (strcmp(city, "END") != 0) {
    int money = 0;
    scanf("%d", &money);
    strcpy(subsidy[count].city, city);
    subsidy[count].money = money;
    count++;
    scanf("%s", city);
  }

  // Break if there is no input 
  if (count == 0) {
    return 0;
  }

  // Sort the cities
  char temp[50];
  for (int i = 0; i < count - 1; i++) {
    for (int j = i + 1; j < count; j++) {
      if (strcmp(subsidy[i].city, subsidy[j].city) > 0) {
        Subsidy temp = subsidy[i];
        subsidy[i] = subsidy[j];
        subsidy[j] = temp;
      }
    }
  }

  char city_name[20][30];
  int money_amount[20] = {0};
  int count_city = 0;

  strcpy(city_name[0], subsidy[0].city);
  money_amount[0] = subsidy[0].money;

  for (int i = 1; i < count; i++) {
    if (strcmp(subsidy[i].city, subsidy[i - 1].city) == 0) {
      money_amount[count_city] += subsidy[i].money;
    } else {
      count_city++;
      strcpy(city_name[count_city], subsidy[i].city);
      money_amount[count_city] = subsidy[i].money;
    }
  }
  count_city++;

  for (int i = 0; i < count_city; i++) {
    printf("%s %d\n", city_name[i], money_amount[i]);
  }
  return 0;
}

/*
        City_name[diff] Money_mon[diff] diff
A 100 ->   A                 100      0
A 200 ->   A                 300      0
B 200 ->   B                          1   
*/