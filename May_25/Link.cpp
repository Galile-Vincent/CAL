#include <iostream>

class Node {
 private:
  int id;
  std::string name;
  Node* next;
 public:
  explicit Node(int id, std::string name) {
    this->id = id;
    this->name = name;
    this->next = nullptr;
  }
  Node() {
    id = -1;
    name = "";
    next = nullptr;
  }
  int GetId() const {
    return id;
  }
  std::string GetName() const {
    return name;
  }
  Node* GetNext() const {
    return next;
  }
  void Insert(int id, std::string name);
  void Delete(int id);
  void Update(int id, std::string name);
  bool FindDuplicate(int id);
};

void Print(Node &head) {
  Node* current = head.GetNext();
  if (current == nullptr) {
    std::cout << "List is empty!" << std::endl;
    return;
  }
  while (current != nullptr) {
    std::cout << current->GetName() << " " << current->GetId() << std::endl;
    current = current->GetNext();
  }
}
void Find(std::string name, Node &head) {
  Node* current = head.GetNext();
  if (current == nullptr) {
    std::cout << "List is empty!" << std::endl;
    return;
  }
  while (current != nullptr) {
    if (current->GetName() == name) {
      std::cout << "The id of " << current->GetName() << " is "
                << current->GetId() << std::endl;
      return;
    }
    current = current->GetNext();
  }
  std::cout << "Name not found: " << name << std::endl;
}

void Operations(Node &head) {
  std::string operation;
  while (std::cin >> operation) {
    if (operation == "p") {
      Print(head);
    } else if (operation == "f") {
      std::string name;
      std::cin >> name;
      Find(name, head);
    } else if (operation == "u") {
      int id;
      std::string name;
      std::cin >> id;
      std::cin >> name;
      head.Update(id, name);
    } else if (operation == "i") {
      int id;
      std::string name;
      std::cin >> name;
      std::cin >> id;
      if (head.FindDuplicate(id)) {
        std::cout << "Sorry!  ID already exists : " << id << "!" << std::endl;
        continue;
      } else {
        head.Insert(id, name);
      }
    } else if (operation == "d") {
      int id;
      std::cin >> id;
      head.Delete(id);
    } else if (operation == "q") {
      break;
    } else if (operation == "EOF") {
      break;
    } else {
      std::cout << "Invalid operation!" << std::endl;
    }
  }
}

int main() {
  Node head;
  Operations(head);
  return 0;
}

bool Node::FindDuplicate(int id) {
  Node* current = next;
  while (current != nullptr) {
    if (current->id == id) {
      return true;
    }
    current = current->next;
  }
  return false;
}

void Node::Insert(int id, std::string name) {
  // Need
  Node* new_node = new Node(id, name);
  if (next == nullptr) {
    next = new_node;
  } else {
    Node* current = next;
    if (current->id > id) {
      new_node->next = current;
      next = new_node;
      return;
    }
    while (current->next != nullptr) {
      if (current->next->id > id) {
        Node *temp = current->next;
        current->next = new_node;
        new_node->next = temp;
        return;
      }
      current = current->next;
    }
    current->next = new_node;
  }
}

void Node::Delete(int id) {
  if (next == nullptr) {
    std::cout << "List is empty!" << std::endl;
    return;
  }
  Node* current = next;
  Node* previous = nullptr;
  while (current != nullptr && current->id != id) {
    previous = current;
    current = current->next;
  }
  if (current == nullptr) {
    std::cout << "Sorry!  There is no such person : " << id << "!" << std::endl;
    return;
  }
  if (previous == nullptr) {
    next = current->next; 
  } else {
    previous->next = current->next; 
  }
  delete current;
}

void Node::Update(int id, std::string name) {
  Node* current = next;
  while (current != nullptr && current->id != id) {
    current = current->next;
  }
  if (current == nullptr) {
    std::cout << "ID not found: " << id << std::endl;
    return;
  }
  current->name = name;
}
