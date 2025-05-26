#include <iostream>
using namespace std;
/**
 * CodePrinter 要能被設定起始的英文字母與起始的數字
 * 然後透過PrintCodeword()輸出26組codewords
 */
class CodePrinter {
  public:
    char start_char;
    int start_num;
    void SetInitialValues(char c, int i) {
      start_char = c;
      start_num = i;
    }
    void PrintCodeword() {
      for (int i = 0; i < 26; i++) {
        if (start_char > 'Z') {
          start_char = 'A';
        }
        start_num = start_num % 10;
        cout << start_char << start_num << endl;
        start_char++;
        start_num++;
      }
    }
};

// I strongly suggest that you do not modify the main()
int main() {
  CodePrinter cp;
  char c;
  int i;
  std::cin >> c >> i;
  cp.SetInitialValues(c, i);
  cp.PrintCodeword();
  return 0;
}