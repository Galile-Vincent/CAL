# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <string.h>

void GetNextChar(char *ch, int *line, int *column);
bool IsDigit(char ch);
bool IsLetter(char ch);
bool IsWhiteSpace(char ch);
bool IsSpecial(char ch);

void SkipWhiteSpaces(char *ch, int *line, int *column);
void SkipLineComment(char *ch, int *line, int *column);
void SkipMultiLineComment(char *ch, int *line, int *column);

int g_next_char_line = 1;  // line-no of the next char
int g_next_char_column = 1;  // column-no of the next char

int main() {

  /*
   * nextChar: the char we just read in
   * currentLine: line-no of nextChar (the char we just read in)
   * currentColumn: column-no of nextChar (the char we just read in)
   */
  char ch = '\0';
  int current_line = -1;  // line-no of current char
  int current_column = -1;  // column-no of current char

  GetNextChar(&ch, &current_line, &current_column);

  for ( ;; ) {

    if (ch == EOF)
      exit(0);

    if (IsWhiteSpace(ch))
      SkipWhiteSpaces(&ch, &current_line, &current_column);  // update nextChar

    // note: ch is a non-white-space waiting to be examined

    if ( ch == '/' ) {

      // in this problem, we assume there are only '//' or '/*' in the code
      // that is, there are no divide operator, e.g., 'a/(4+b)'

      // after GetNextChar() ch should be '/' or '*',
      // which is the second char of a comment
      GetNextChar(&ch, &current_line, &current_column);

      if ( ch == '/' )
        SkipLineComment(&ch, &current_line, &current_column);

      else if ( ch == '*' )
        SkipMultiLineComment(&ch, &current_line, &current_column);

      else {  // the previous '/' is DIVIDE (should not happen)

        // Since we assume the previous '/' is not DIVIDE for this problem
        printf("Wrong test data (Prob. 2): the char behind '/' "
               "at (%d,%d) is '%c'",
               current_line, current_column, ch);

        GetNextChar(&ch, &current_line, &current_column);

      }
    } else if ( ch != EOF ) {
      printf("%c (%d,%d).\n", ch, current_line, current_column);
      GetNextChar(&ch, &current_line, &current_column);
    }
  }

  return 0;
}

//=======================
// functions you have already written
void GetNextChar(char *ch, int *line, int *column) {
  if (scanf("%c", ch) == EOF) {
    *ch = EOF;
    return;
  }
  *line = g_next_char_line;
  *column = g_next_char_column;

  if (*ch == '\n') {
    g_next_char_line++;
    g_next_char_column = 1;
  } else {
    g_next_char_column++;
  }
}

bool IsWhiteSpace(char ch) {
  return (ch == '\t' || ch == ' ' || ch == '\n');
}

//=======================
// new functions you need to implement
/**
  * 忽略所有的white-space家族。這邊的white-space家族指的是空白、換行、tab。
  * 本函數結束時，ch應該是指向一個非空白的字元
  * @param ch 指著非空白字元的指標
  * @param line 指向該字元的line-no
  * @param column 指向該字元的column-no
  */
void SkipWhiteSpaces(char *ch, int *line, int *column) {
  while (IsWhiteSpace(*ch)) {
    GetNextChar(ch, line, column);
  }
}

/**
 * 忽略一整行的註解。
 * 本函數結束時，ch應該是指向下一行的第一個字元(不管它是什麼)
 * @param ch 指著該字元的指標
 * @param line 指向該字元的line-no
 * @param column 指向該字元的column-no
 */
void SkipLineComment(char *ch, int *line, int *column) {
  while (*ch != '\n' && *ch != EOF) {
    GetNextChar(ch, line, column);
  }
  GetNextChar(ch, line, column);
}

/**
 * 忽略多行的註解。
 * 本函數結束時，ch應該是指向多行註解結束的第一個字元(不管它是什麼)
 * @param ch 指著該字元的指標
 * @param line 指向該字元的line-no
 * @param column 指向該字元的column-no
 */
void SkipMultiLineComment(char *ch, int *line, int *column) {
  while (true) {
    GetNextChar(ch, line, column);
    
    if (*ch == '*') {
      GetNextChar(ch, line, column);
      if (*ch == '/') {
        GetNextChar(ch, line, column);
        return;
      }
    }
  }
}