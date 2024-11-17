/*
Read the city and store the first char(make it to int) and the place of the city
at array sort_city
sort the sort_city by the sort_city[n][0]
*/

// https://www.ibm.com/docs/zh-tw/uax?topic=functions-strcmp
/*
strcmp
ABC	    ABC	 0 -> a == b
abc	    ABC	 1 -> a > b
ABC	    abc	-1 -> a < b
阿布克德 abc  1 -> a > b
*/

#include<stdio.h>
#include<string.h>
#include<stdbool.h>

typedef char Data[20];

int main() {
  Data cities[50];
  int count_city = 0;

  // Read city into Data
  char city[50];
  scanf("%s", city);
  while (strcmp(city, "-1") != 0) {
    strcpy(cities[count_city], city);
    count_city++;
    scanf("%s", city);
  }

  // Sort the cities
  char temp[50];
  for (int i = 0; i < count_city - 1; i++) {
    for (int j = i + 1; j < count_city; j++) {
      if (strcmp(cities[i], cities[j]) > 0) {
        strcpy(temp, cities[i]);
        strcpy(cities[i], cities[j]);
        strcpy(cities[j], temp);
      }
    }
  }

  // Print the cities by the sort_city

  if (count_city == 0) {
    return 0;
  }

  for (int i = 0; i < count_city; i++) {
    printf("%s\n", cities[i]);
  }
  return 0;
}