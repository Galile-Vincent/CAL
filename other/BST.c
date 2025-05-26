#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>

struct Node {
  int value;
  struct Node *left;
  struct Node *right;
};

typedef struct Node Node;
typedef Node* NodePtr;

// initialize the BST so that it is empty
void Init(NodePtr node);

// test whether the BST is empty (and print the test result)
bool IsEmpty(NodePtr node);

// add an element (an integer) onto the BST
NodePtr Add(NodePtr node, int num);

// test whether the given integer is on the tree (and print)
bool OnTree(NodePtr node, int num);

// inorder traverse the tree and print the content of the tree
void Inorder(NodePtr node);

// preorder traverse the tree and print the content of the tree
void Preorder(NodePtr node);
// postorder traverse the tree and print the content of the tree
void Postorder(NodePtr node);
// print the current height of the tree
int Height(NodePtr node);
// stop program execution

int main() {
  NodePtr root = NULL;
  char command[10];
  int value;
    
  while (1) {
    scanf("%s", command);
        
    if (strcmp(command, "quit") == 0) {
      break;
    }
    else if (strcmp(command, "init") == 0) {
      Init(root);
    }
    else if (strcmp(command, "empty") == 0) {
      printf("%s\n", IsEmpty(root) ? "true" : "false");
    }
    else if (strcmp(command, "add") == 0) {
      scanf("%d", &value);
      root = Add(root, value);
    }
    else if (strcmp(command, "ontree") == 0) {
      scanf("%d", &value);
      printf("%s\n", OnTree(root, value) ? "true" : "false");
    }
    else if (strcmp(command, "inorder") == 0) {
      Inorder(root);
    }
    else if (strcmp(command, "preorder") == 0) {
      Preorder(root);
    }
    else if (strcmp(command, "postorder") == 0) {
      Postorder(root);
    }
    else if (strcmp(command, "height") == 0) {
      printf("%d\n", Height(root));
    }
  }
    
  Init(root);  // Free memory before exit
  return 0;
}

void Init(NodePtr node) {
  if (node != NULL) {
    Init(node->left);
    Init(node->right);
    free(node);
  }
}

bool IsEmpty(NodePtr node) {
  return (node == NULL);
}

NodePtr Add(NodePtr node, int num) {
  // Empty
  if (node == NULL) {
    NodePtr newNode = (NodePtr)malloc(sizeof(Node));
    newNode->value = num;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
  }

  // num > node.value
  // Keep search until the end
  if (num > node->value) {
    node->right = Add(node->right, num);
  } else if (num < node->value) {
    node->left = Add(node->left, num);
  } 
  // if num == node.value: Do nothing

  return node;
}

bool OnTree(NodePtr node, int num) {
  if (node == NULL) {
    return false;
  }

  if (node->value == num) {
    return true;
  } else if (num > node->value) {
    return OnTree(node->right, num);
  } else {
    return OnTree(node->left, num);
  }
}

void Inorder(NodePtr node) {
  if (node != NULL) {
    Inorder(node->left);
    printf("%d\n", node->value);
    Inorder(node->right);
  }
}

void Preorder(NodePtr node) {
  if (node != NULL) {
    printf("%d\n", node->value);
    Preorder(node->left);
    Preorder(node->right);
  }
}

void Postorder(NodePtr node) {
  if (node != NULL) {
    Postorder(node->left);
    Postorder(node->right);
    printf("%d\n", node->value);
  }
}

int Height(NodePtr node) {
  if (node == NULL) {
    return -1;
  }
  int left_height = Height(node->left);
  int right_height = Height(node->right);

  return (left_height > right_height ? left_height : right_height) + 1;
}
