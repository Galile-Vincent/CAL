#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void Process(char name[250]) {
  char family_name[51] = {0};
  int place_family = 0;
  char small_name[51] = {0};
  int place_small = 0;
  bool family = false;
  bool need_process = true;
  // Check if need process
  for (int i = 0; i < strlen(name); i++) {
    if (name[i] == ',') need_process = false;
   }
  if (need_process) {
    int place = 0;
    for (int i = strlen(name) - 1; i >= 0; i--) {
      if (name[i] == ' ') {
        place = i;
        break;
      }
    }

    for (int i = 0; i < strlen(name); i++) {
      if (i < place) {
        small_name[place_small] = name[i];
        place_small++;
      } else {
        if (name[i] != ' ') {
          family_name[place_family] = name[i];
          place_family++;
        }
      }
    }
    name[0] = '\0';
    strcat(name, family_name);
    strcat(name, ", ");
    strcat(name, small_name);
  }
}
int main() {
  char input[51] = {0};

  scanf("%50s", input);

  char names[30][250] = {0};
  int count_name = 0;
  while (true) {
    if (strcmp(input, "END_OF_EVERYTHING") == 0) {
      count_name--;
      break;
    }
    if (strcmp(input, ";") == 0) {
      Process(names[count_name]);
      count_name++;
    } else {
      if (strlen(names[count_name]) == 0) {
        strcpy(names[count_name], input);
      } else {
        strcat(names[count_name], " "); // Mark for the family name
        strcat(names[count_name], input);
      }
    }
    scanf("%50s", input);
  }
  if (count_name > 0) {
    // Order
    for (int i = 0; i < count_name; i++) {
      for (int j = i + 1; j < count_name + 1; j++) {
        if (strcmp(names[i], names[j]) > 0) {
          char temp[51] = {0};
          strcpy(temp, names[i]);
          strcpy(names[i], names[j]);
          strcpy(names[j], temp);
        }
      }
    }
    for (int i = 0; i < count_name+1; i++) {
      printf("%s\n", names[i]);
    }
  }

  return 0;
}