#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
typedef char Str40[40];

struct account {
  Str40 name;
  int id;
  struct account * next;
};

typedef struct account Account;
typedef Account* AccountPtr;
AccountPtr Find(AccountPtr head, int id);
bool Update(AccountPtr head, int id, Str40 new_name);
AccountPtr Delete(AccountPtr head, int id);

int main() {

  AccountPtr accounts = NULL;
  int id;

  accounts = Read(accounts);

  scanf("%d", &id);  // id we want to find

  AccountPtr calFind = NULL, learnerFind = NULL;
  learnerFind = Find(accounts, id);
  calFind = CalFind(accounts, id);

  if ( calFind == learnerFind )
    if ( learnerFind != NULL )
      printf("%s", learnerFind->name);
    else printf("No such person!");

  else printf("Find() works incorrectly!");
  return 0;

}

/**
 * Try to find 'id' in the list.
 * else return NULL ;
 * Note : if there are more than one node in the list with
 *           their 'id' being the same as the given 'id',
 *           then Find() returns a pointer to THE FIRST NODE
 *           in the list that has the given 'id'
 * @param head points to the start of this list
 * @param id   the id we want to match
 * @return     if matched, returns a pointer that points to that matched node. else return NULL
 * then return
 */
AccountPtr Find(AccountPtr head, int id) {
  if (head == NULL) {
    return NULL;
  }

  if (head == id) {
    return head;
  } else {
    Find(head->next, id);
  }
}

/**
 * Try to find 'id' in the list that is pointed at by 'head'
 * If there is a node in the list with its 'id' being the same
 * as the given 'id', then change its 'name' to 'newName'
 * Note : if there are more than one node in the list with
 *           their 'id' being the same as the given 'id',
 *          then Update() will update ALL such nodes
 * @param head points to the start of this list
 * @param id the id we want to match
 * @param newName the string we want to update
 * @return true if the update was successful; else false
 */
bool Update(AccountPtr head, int id, Str40 new_name) {
  // Check if the last -> NULL
  // If so it means no user found
  if (head == NULL) {
    return false;
  }
  // If found
  // Replace the name with new_name
  if (head->id == id) {
    strcpy(head->name, new_name);
    Update(head->next, id, new_name);
    return true;
  } else {
    // If not found
    // head change to next
    Update(head->next, id, new_name);
  }
}

/**
 * Try to remove nodes in the list with the given 'id'.
 * Note : if there are more than one node in the list with
 *           their 'id' being the same as the given 'id',
 *           then Delete() will DELETE ALL NODES with that 'id'
 * @param head points to the start of this list
 * @param id the id we want to match
 * @return returns a pointer that points to the first node of the list
 */
AccountPtr Delete(AccountPtr head, int id) {
  // Check if the last -> NULL
  // If so it means no id found
  if (head == NULL) {
    return head;
  }
  // If found
  // Delete the id
  if (head->id == id) {
    AccountPtr temp = head;
    head = head->next;
    free(temp);
    return Delete(head, id);
  }

  head->next = Delete(head->next, id);
  return head;
}