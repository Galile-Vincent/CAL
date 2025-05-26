#include<stdio.h>
#include<stdbool.h>
#include<string.h>
/**
* 檢查輸入的字串是否是迴文
* @param a     輸入的字串
* @param start 這個字串的"起點"
* @param end   這個字串的"終點"
* @return      如果是迴文，回傳true，否則回傳false
*/
bool IsPalindrome(const char *a, int start, int end) {
  if (a[start] != a[end]) {
    return false;
  } else if (start == end) {
    return true;
  } else {
    IsPalindrome(a, start + 1, end - 1);
  }
}

int main() {
  int start = 0;
  int end = 0;
  char str[31] = {0};
  scanf("%s", str);
  end = strlen(str) - 1;
  if (IsPalindrome(str, start, end)) {
    printf("%s is a palindrome.", str);
  } else {
    printf("%s is not a palindrome.", str);
  }
  return 0;
}