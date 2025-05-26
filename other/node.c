#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct node {
  int id;
  int count;
  struct node * next;
};

typedef struct node Node;
typedef Node* NodePtr;
NodePtr OrderInsert(NodePtr head, int id);

/**
 * Print out the list
 * @param head points to the start of this list
 */
void Print(NodePtr head);
int main() {

  NodePtr head = NULL;
  int id = 0;

  scanf("%d", &id);
  while ( id != -1 ) {
    head = OrderInsert(head, id);
    scanf("%d", &id);
  }

  Print(head);

  return 0;

}

/**
 * Try to insert 'id' in the list that is pointed at by 'head' ;
 * If there is already a node in the list with its 'id' being the same
 * as the given 'id', then increment its 'count'
 * @param head points to the start of this list
 * @param id the id we want to match
 * @return a pointer that points to the first node of the list
 */
NodePtr OrderInsert(NodePtr head, int id) {
  // Empty or can't found the id
  if (head == NULL) {
    NodePtr newNode = (NodePtr)malloc(sizeof(Node));
    newNode->id = id;
    newNode->count = 1;
    newNode->next = NULL;
    return newNode;
  }
  // Found: count+1
  if (head->id == id) {
    head->count += 1;
    return head;
  }

  // if id < head->id, insert
  if (id < head->id) {
    NodePtr newNode = (NodePtr)malloc(sizeof(Node));
    newNode->id = id;
    newNode->count = 1;
    newNode->next = head;
    return newNode;
  }

  // Else: call OrderInsert(head->next, id); ???
  head->next = OrderInsert(head->next, id);
  return head; 
}