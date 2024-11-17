#include<stdio.h>
#include<string.h>
#include<stdbool.h>

struct Subsidy {
    char city[30];
    int money;
};

typedef struct Subsidy Subsidy;
typedef char Data[15];
int main() {
  Subsidy subsidy[20];
  int count = 0; // Count of people

  char city[30];
  int money = 0;
  scanf("%s", city);

  // Read the city and money , break when city is END
  while (city != "END") {
    scanf("%s", city);
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
        strcpy(temp, subsidy[i].city);
        strcpy(subsidy[i].city, subsidy[j].city);
        strcpy(subsidy[j].city, temp);
      }
    }
  }
  
  int count_city = 0;
  for (int i = 0; i < count; i++) {
    
  }

  
  return 0;
}