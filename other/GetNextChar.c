# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <string.h>

void GetNextChar(char *ch, int *line, int *column);
bool IsDigit(char ch);
bool IsLetter(char ch);
bool IsWhiteSpace(char ch);
bool IsSpecial(char ch);

int g_next_char_line = 1;  // line-no of the next char
int g_next_char_column = 1;  // column-no of the next char

int main() {

  /*
   * ch: the char we just read in
   * currentLine: line-no of nextChar (the char we just read in)
   * currentColumn: column-no of nextChar (the char we just read in)
   */
  char ch = '\0';
  int current_line = -1;  // line-no of current char
  int current_column = -1;  // column-no of current char

  for ( ;; ) {

    GetNextChar(&ch, &current_line, &current_column);

    if (ch == EOF) {
      exit(0);
    }

    if ( IsLetter(ch) )
      printf("%c is a letter", ch);
    else if ( IsDigit(ch) )
      printf("%c is a digit", ch);
    else if ( IsWhiteSpace(ch) )
      if ( ch== '\n' )
        printf("'\\n' is a white space");
      else if (ch== '\t')
        printf("'\\t' is a white space");
      else
        printf("' ' is a white space");
    else if ( IsSpecial(ch) )
      printf("%c is a special character", ch);
    else  // neither letter, nor digit, nor white-space, nor "special"
      printf("%c is a character with an unknown type", ch);

    printf(" (%d,%d).\n", current_line, current_column);
  }

  return 0;
}
/** 讀進一個字元，存在ch裡面，函數結束後要把g_next_char_line與g_next_char_column
  * 更新成下一個讀入字元所在的line-no與column-no
  * @param ch 指向讀入字元的指標
  * @param line 一個指標，
        函數結束後須更新成指向目前取得的字元的line-no
  * @param column 一個指標，
        函數結束後須更新成指向目前取得的字元的column-no
  */
void GetNextChar(char *ch, int *line, int *column) {
  if (scanf("%c", ch) == EOF) { // Check for input failure (e.g., EOF)
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
void GetNextChar(char *ch, int *line, int *column) {
  char input[500] = "";
  scanf("%s", input);

  *line = g_next_char_line;
  *column = g_next_char_column;

  char eof[50] = {'E', 'N', 'D', '_', 'O', 'F', '_', 'F', 'I', 'L', 'E'};
  int is_eof = true;
  for (int i = 0; i < strlen(eof); i++) {
    if (input[i] != eof[i]) {
      is_eof = false;
      break;
    }
  }
  if (is_eof) {
    *ch = EOF;
    return;
  }
  
  *ch = input[g_next_char_column - 1];
  if (*ch == '\n') {
    g_next_char_line++;
    g_next_char_column = 1;
  } else {
    g_next_char_column++;
  }
}



/* Is ch a digit ('0', '1', '2', ..., '9')? */
bool IsDigit(char ch) {
  return (ch >= '0' && ch <= '9');
}

/* Is ch a letter ('a', 'b', ..., 'z', 'A', 'B', ..., 'Z')? */
bool IsLetter(char ch) {
  return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

/* Is ch a white-space? */
bool IsWhiteSpace(char ch) {
  return (ch == '\t' || ch == ' ' || ch == '\n');
} 

/* Is ch a special character ? */
bool IsSpecial(char ch) {
  char special_chars[] = "^,()[]{}!:;#?+-*/><=%&|";
  int size = sizeof(special_chars) - 1;  // Exclude null terminator

  for (int i = 0; i < size; i++) {
    if (ch == special_chars[i]) {
      return true;
    }
  }
  return false;
}





