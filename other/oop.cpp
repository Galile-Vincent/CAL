#include <iostream>
#include <string.h>

/*
void Swim(char *type) {
  if ( strcmp(type, "human") == 1 ) {
    printf("human is swimming.");
  } else if ( strcmp(type, "dog") == 1 ) {
    printf("dog is swimming.");
  } else if ( strcmp(type, "fish") == 1 ) {
    printf("fish is swimming.");
  }
}
*/

class Human {
 public:
  void Swim() {
    std::cout << "human is swimming." << std::endl;    
  }
};
class Fish {
 public:
  void Swim() {
    std::cout << "fish is swimming." << std::endl;    
  }
};
class Dog {
 public:
  void Swim() {
    std::cout << "dog is swimming." << std::endl;    
  }
};



int main() {

  /* as a c programmer, you may want to use
  char s1[] = "human";
  char s2[] = "dog";
  char s3[] = "fish";
  Swim(s1);
  Swim(s2);
  Swim(s3);
  to get desired output. However, this is not object-oriented.
  Look at the provided class and think about how to get the desired output
  in object-oriented way.
 */
  Human h;
  Fish f;
  Dog d;
  h.Swim();
  f.Swim();
  d.Swim();
}