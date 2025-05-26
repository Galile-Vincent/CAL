/*
a <name> <id>      // add to the underlying list IN ORDER (smaller-id precedes larger-id)
d <id>             // delete from the underlying list the node with this id
u <id> <name>      // update the name of the node (with its id being <id>) to be <name>
p                  // print the underlying list
q                  // quit
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef char Str40[40];

struct Account {
  Str40 name;
  int id;
  struct Account * next;
};
typedef struct Account Account;
typedef Account* AccountPtr;

/*
AccountPtr OrderInsert(AccountPtr head, int id, Str40 name) {
  AccountPtr next = NULL; // Previous -> (new) INSERT -> Next
  AccountPtr previous = NULL;
  if (head == NULL) {
    AccountPtr newptr = (AccountPtr)malloc(sizeof(Account));
    newptr->id = id;
    strcpy(newptr->name, name);
    newptr->next = NULL;
    return newptr;
  }
  AccountPtr current = head;
  while (current != NULL) {
    if (current->id == id) {
      current->count += 1;
      return head;
    }
    if (current->id > id) {
      next = current;
      break;
    }
    previous = current;
    current = current->next;
  }
  AccountPtr *newptr;
  newptr = (AccountPtr)malloc(sizeof(Account));
  newptr->id = id;
  newptr->count = 1;
  newptr->next = next;
  if (previous == NULL) {
    return newptr;
  } else {
    previous->next = newptr;
    return head;
  }
}
*/
AccountPtr Delete(AccountPtr head, int id) {
  AccountPtr previous = NULL; // Previous -> (current) DELETE -> Next
  if (head == NULL) {
    return head;
  }
  AccountPtr current = head;
  while (current != NULL) {
    if (current->id == id) {
      if (current == head) {
        head = current->next;
        free(current);
        current = head;
      } else {
        previous->next = current->next;
        free(current);
        current = previous->next;
      }
    } else {
      previous = current;
      current = current->next;
    }
  }
  return head;
}
int main() {
  char operation = "";
  scanf("%c", &operation);
  while (operation)
}