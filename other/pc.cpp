#include<iostream>
using namespace std;

int main() {
    for(int i = 0; i < 10; i++) {  // range-based for loop
        if (i%2 == 0) {
            continue;
        }
        cout << i << endl;
    }
    return 0;
}
