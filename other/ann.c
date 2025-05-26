# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <string.h>

# define NOT !
# define AND &&
# define OR ||
# define EQ ==

enum TokenType {
  IDENTIFIER = 34313,
  CONSTANT = 87424,
  SPECIAL = 29535
};

typedef char * CharPtr;

typedef struct TokenInfo {
  CharPtr token_str;
  enum TokenType token_type;
  int first_char_line;
  int first_char_column;
}TokenInfo;

typedef TokenInfo * TokenInfoPtr;

void GetNextChar(char *ch, int *line, int *column);
bool IsDigit(char ch);
bool IsLetter(char ch);
bool IsWhiteSpace(char ch);
bool IsSpecial(char ch);
void SkipWhiteSpaces(char *ch, int *line, int *column);
void SkipLineComment(char *ch, int *line, int *column);
void SkipMultiLineComment(char *ch, int *line, int *column);
CharPtr GetID(char *ch, int *line, int *column);
CharPtr GetNum(char *ch, int *line, int *column);
CharPtr GetCharConst(char *ch, int *line, int *column);
CharPtr GetStringConst(char *ch, int *line, int *column);
CharPtr GetSpecial(char *ch, int *line, int *column);
TokenInfoPtr GetToken(char *ch, int *current_line, int *current_column);

typedef struct Column {
  int column;
  struct Column * next;
}Column;

typedef Column * ColumnPtr;

typedef struct Line {
  int line;
  ColumnPtr first_appear_at;
  ColumnPtr last_appear_at;
  struct Line * next;
}Line;

typedef Line * LinePtr;

typedef struct Token {
  CharPtr token_str;
  enum TokenType type;
  LinePtr first_appear_on;
  LinePtr last_appear_on;
  struct Token * next;
}Token;

typedef Token * TokenPtr;

void PrintAllTokenInfo(TokenPtr head);
TokenPtr OrderInsertToken(TokenPtr head, TokenInfoPtr info);
void CountTokens(TokenPtr head);
void CountTypes(TokenPtr head);
void FindTokenAppearance(TokenPtr head, char *str);
void ListTokenAtLine(TokenPtr head, int line_no);
void HandleUI(TokenPtr head);

int g_next_char_line = 1;  // line-no of the next char
int g_next_char_column = 1;  // column-no of the next char

int main() {

  char ch = '\0';
  int current_line = -1;   // line-no of current char
  int current_column = -1;   // column-no of current char
  TokenInfoPtr info_ptr = NULL;
  TokenPtr list_head = NULL;

  GetNextChar(&ch, &current_line, &current_column);   // get the very first char

  do {
    info_ptr = GetToken(&ch, &current_line, &current_column);

    if ( info_ptr != NULL ) {
      if (strcmp(info_ptr->token_str, "END_OF_EVERYTHING") == 0) {
        free(info_ptr);
        info_ptr = NULL;
      } else
        list_head = OrderInsertToken(list_head, info_ptr);
    }
  } while ( info_ptr != NULL );

  HandleUI(list_head);

  return 0;
}
void HandleUI(TokenPtr head) {
  int option = 0;
  while (option != 5) {
    scanf("%d", &option);
    if (option == 1) {
      CountTokens(head);
    } else if (option == 2) {
      CountTypes(head);
    } else if (option == 3) {
      char ch;
      scanf("%c", &ch);
      TokenInfoPtr ans = NULL;
      int cur_lin = -1;
      int cur_col = -1;
      ans = GetToken(&ch, &cur_lin, &cur_col);
      FindTokenAppearance(head, ans->token_str);
    } else if (option == 4) {
      int line_no;
      scanf("%d", &line_no);
      ListTokenAtLine(head, line_no);
    } else if (option == 5) {
      PrintAllTokenInfo(head);
    } else if (option == 6) {
      break;
    }
  }
}

void CountTokens(TokenPtr head) {
  int count = 0;
  TokenPtr current = head;
  while (current != NULL) {
    count++;
    current = current->next;
  }
  printf("There are %d different tokens in total.\n", count);
}

void CountTypes(TokenPtr head) {
  int iden_count = 0, con_count = 0, spe_count = 0;
  TokenPtr current = head;
  while (current != NULL) {
    if (current->type == IDENTIFIER) {
      iden_count++;
    } else if (current->type == CONSTANT) {
      con_count++;
    } else if (current->type == SPECIAL) {
      spe_count++;
    }
    current = current->next;
  }
  printf("Identifer : %d\n", iden_count);
  printf("Constant : %d\n", con_count);
  printf("Special : %d\n", spe_count);
}

void FindTokenAppearance(TokenPtr head, char *str) {
  TokenPtr current = head;
  bool found = false;
  while (current != NULL) {
    if (strcmp(current->token_str, str) == 0) {
      found = true;
      LinePtr line = current->first_appear_on;
      while (line != NULL) {
        ColumnPtr column = line->first_appear_at;
        while (column != NULL) {
          printf("(%d,%d)", line->line, column->column);
          column = column->next;
        }
        line = line->next;
      }
      printf("\n");
    }
    current = current->next;
  }
  if (!found) {
    printf("There is no such token : %s\n", str);
  }
}

void ListTokenAtLine(TokenPtr head, int line_no) {
  TokenPtr current = head;
  bool found = false;
  while (current != NULL) {
    LinePtr line = current->first_appear_on;
    while (line != NULL) {
      if (line->line == line_no) {
        found = 1;
        printf("%s\n", current->token_str);
        break;
      }
      line = line->next;
    }
    current = current->next;
  }
  if (!found) {
    printf("There is no such line : %d\n", line_no);
  }
}
void PrintAllTokenInfo(TokenPtr head) {
  TokenPtr current_token = head;
  while (current_token != NULL) {
    printf("%s ", current_token->token_str);


    LinePtr current_line = current_token->first_appear_on;
    while (current_line != NULL) {
      ColumnPtr column = current_line->first_appear_at;
      while (column != NULL) {
        printf("(%d,%d)", current_line->line, column->column);
        column = column->next;
      }
      current_line = current_line->next;
    }

    printf("\n");
    current_token = current_token->next;
  }
}


TokenPtr OrderInsertToken(TokenPtr root, TokenInfoPtr detail) {
  TokenPtr node = (TokenPtr)malloc(sizeof(Token));
  node->token_str = detail->token_str;
  node->type = detail->token_type;
  node->first_appear_on = NULL;
  node->last_appear_on = NULL;
  node->next = NULL;

  LinePtr line_data = (LinePtr)malloc(sizeof(Line));
  line_data->line = detail->first_char_line;
  line_data->first_appear_at = (ColumnPtr)malloc(sizeof(Column));
  line_data->first_appear_at->column = detail->first_char_column;
  line_data->first_appear_at->next = NULL;
  line_data->last_appear_at = line_data->first_appear_at;
  line_data->next = NULL;

  if (!root) {
    node->first_appear_on = line_data;
    node->last_appear_on = line_data;
    return node;
  }

  TokenPtr iter = root;
  TokenPtr prev = NULL;

  while (iter && strcmp(iter->token_str, detail->token_str) < 0) {
    prev = iter;
    iter = iter->next;
  }

  if (iter && strcmp(iter->token_str, detail->token_str) == 0) {
    LinePtr line_iter = iter->first_appear_on;
    while (line_iter && line_iter->line != detail->first_char_line) {
      line_iter = line_iter->next;
    }

    if (!line_iter) {
      iter->last_appear_on->next = line_data;
      iter->last_appear_on = line_data;
    } else {
      if (line_iter->first_appear_at->column > detail->first_char_column) {
        ColumnPtr fresh_col = (ColumnPtr)malloc(sizeof(Column));
        fresh_col->column = detail->first_char_column;
        fresh_col->next = line_iter->first_appear_at;
        line_iter->first_appear_at = fresh_col;
      } else {
        ColumnPtr col_iter = line_iter->first_appear_at;
        while (col_iter->next &&
               col_iter->next->column < detail->first_char_column) {
          col_iter = col_iter->next;
        }
        ColumnPtr fresh_col = (ColumnPtr)malloc(sizeof(Column));
        fresh_col->column = detail->first_char_column;
        fresh_col->next = col_iter->next;
        col_iter->next = fresh_col;
        if (!fresh_col->next) {
          line_iter->last_appear_at = fresh_col;
        }
      }
    }
    return root;
  }

  if (!prev) {
    node->next = root;
    root = node;
  } else {
    node->next = iter;
    prev->next = node;
  }

  node->first_appear_on = line_data;
  node->last_appear_on = line_data;
  return root;
}



TokenInfoPtr GetToken(char *ch, int *current_line, int *current_column) {
  TokenInfoPtr new_node = (TokenInfoPtr)malloc(sizeof(TokenInfo));
  while (IsWhiteSpace(*ch) || *ch == '/' || *ch == EOF) {
    if (*ch == EOF) {
      return NULL;
    }
    if (IsWhiteSpace(*ch)) {
      SkipWhiteSpaces(ch, current_line, current_column);
    } else if (*ch == '/') {
      GetNextChar(ch, current_line, current_column);
      if (*ch == '*') {
        SkipMultiLineComment(ch, current_line, current_column);
      } else if (*ch == '/') {
        SkipLineComment(ch, current_line, current_column);
      } else {
        if (*ch == '=') {
          new_node->token_type = SPECIAL;
          new_node->token_str = "/=";
          new_node->first_char_line = *current_line;
          new_node->first_char_column = *current_column - 1;
          if (new_node->first_char_column == 0)
            new_node->first_char_column++;
          GetNextChar(ch, current_line, current_column);
        } else {
          new_node->token_type = SPECIAL;
          new_node->token_str = "/";
          new_node->first_char_line = *current_line;
          new_node->first_char_column = *current_column - 1;
          if (new_node->first_char_column == 0)
            new_node->first_char_column++;
          //  if (*ch == EOF) new_node->first_char_column++;
        }
        return new_node;
      }
    }
  }
  new_node->first_char_line = *current_line;
  new_node->first_char_column = *current_column;
  if (IsLetter(*ch) || *ch == '_') {
    new_node->token_type = IDENTIFIER;
    new_node->token_str = GetID(ch, current_line, current_column);
  } else if (IsDigit(*ch) || *ch == '.') {
    new_node->token_type = CONSTANT;
    new_node->token_str = GetNum(ch, current_line, current_column);
  } else if (*ch == '\'') {
    new_node->token_type = CONSTANT;
    new_node->token_str = GetCharConst(ch, current_line, current_column);
  } else if (*ch == '\"') {
    new_node->token_type = CONSTANT;
    new_node->token_str = GetStringConst(ch, current_line, current_column);
  } else if (IsSpecial(*ch)) {
    new_node->token_type = SPECIAL;
    new_node->token_str = GetSpecial(ch, current_line, current_column);
  }
  return new_node;
}

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

/** 讀進此ID的完整字串，儲存進heap且回傳該字串的起頭位置
  * 當此function結束時，ch/line/column的內容應更新成緊接此ID之後的字元。
  * Note: you should use GetNextChar() to get the next input char.
  * @param ch 傳入時是一個ID的開頭字元(letter或'_')
  * @param line ch的line-no
  * @param column ch的column-no
  * @return 指向此字串的pointer
  */
CharPtr GetID(char *ch, int *line, int *column) {
  char input[1000];
  int count = 0;
  // Collect all valid identifier characters (letters, digits, underscores)
  while ((IsLetter(*ch) || IsDigit(*ch) || *ch == '_') && *ch != EOF) {
    input[count++] = *ch;
    GetNextChar(ch, line, column);
  }
  // Null terminate the string
  input[count] = '\0';
  // Allocate memory and copy the string
  CharPtr result = (CharPtr)malloc(count + 1);
  strcpy(result, input);

  return result;
}

/** 讀進此數字的完整字串，儲存進heap且回傳該字串的起頭位置
  * 當此function結束時，ch/line/column的內容應更新成緊接此數字之後的字元。
  * Note: you should use GetNextChar() to get the next input char.
  * @param ch 傳入時是一個number的開頭字元(digit或DOT)
  * @param line ch的line-no
  * @param column ch的column-no
  * @return 指向此字串的pointer
  */
CharPtr GetNum(char *ch, int *line, int *column) {
  char input[1000];
  int count = 0;
  bool has_dot = false;
  
  // Handle the case where the number starts with a digit
  if (IsDigit(*ch)) {
    // Collect all digits
    while (IsDigit(*ch) && *ch != EOF) {
      input[count++] = *ch;
      GetNextChar(ch, line, column);
    }
    
    // Handle decimal point if present
    if (*ch == '.') {
      has_dot = true;
      input[count++] = *ch;
      GetNextChar(ch, line, column);
      
      // Collect digits after decimal point
      while (IsDigit(*ch) && *ch != EOF) {
        input[count++] = *ch;
        GetNextChar(ch, line, column);
      }
    }
  }
  // Handle the case where the number starts with a dot
  else if (*ch == '.') {
    has_dot = true;
    input[count++] = *ch;
    GetNextChar(ch, line, column);
    
    // Must have at least one digit after the decimal point
    if (IsDigit(*ch)) {
      while (IsDigit(*ch) && *ch != EOF) {
        input[count++] = *ch;
        GetNextChar(ch, line, column);
      }
    }
  }
  
  // Null terminate the string
  input[count] = '\0';
  // Allocate memory and copy the string
  CharPtr result = (CharPtr)malloc(count + 1);
  strcpy(result, input);

  return result;
}

/** 讀進此字元的完整字串，儲存進heap且回傳該字串的起頭位置
  * 當此function結束時，ch/line/column的內容應更新成緊接此數字之後的字元。
  * Note: Escape char (跳脫字元) ('\\') is allowed. 
  * Examples: '\\', '\n', '\'', '\t', etc.
  * Note: you should use GetNextChar() to get the next input char.
  * @param ch 傳入時是一個字元(如'a')的開頭(i.e., 單引號)
  * @param line ch的line-no
  * @param column ch的column-no
  * @return 指向此字串的pointer
  */
CharPtr GetCharConst(char *ch, int *line, int *column) {
  char input[1000];
  int count = 0;
  
  // Store the opening quote
  input[count++] = *ch;
  GetNextChar(ch, line, column);
  
  // Handle character content (either regular or escape sequence)
  if (*ch == '\\') {
    // Store the backslash
    input[count++] = *ch;
    GetNextChar(ch, line, column);
    
    // Store the escaped character
    if (*ch != EOF) {
      input[count++] = *ch;
      GetNextChar(ch, line, column);
    }
  } else if (*ch != '\'' && *ch != EOF) {
    // Store a regular character
    input[count++] = *ch;
    GetNextChar(ch, line, column);
  }
  
  // Store the closing quote if present
  if (*ch == '\'') {
    input[count++] = *ch;
    GetNextChar(ch, line, column);
  }
  
  // Null terminate the string
  input[count] = '\0';
  // Allocate memory and copy the string
  CharPtr result = (CharPtr)malloc(count + 1);
  strcpy(result, input);

  return result;
}

/** 讀進一個完整字串，儲存進heap且回傳該字串的起頭位置
  * 當此function結束時，ch/line/column的內容應更新成緊接此數字之後的字元。
  * Note: Escape char (跳脫字元) ('\\') is allowed. 
  * Examples: '\\', '\n', '\'', '\t', etc.
  * Note: you should use GetNextChar() to get the next input char.
  * @param ch 傳入時字串常數(如"Hi")的開頭(i.e., 雙引號)
  * @param line ch的line-no
  * @param column ch的column-no
  * @return 指向此字串的pointer
  */
CharPtr GetStringConst(char *ch, int *line, int *column) {
  CharPtr new_node = NULL;
  new_node = malloc(sizeof(char)*100);
  int count = 0;
  new_node[count] = *ch;
  count++;
  bool slash = false;
  GetNextChar(ch, line, column);
  while (*ch != EOF) {
    if (*ch == '\\' && !slash) {
      slash = true;
      new_node[count] = *ch;
      count++;
      GetNextChar(ch, line, column);
    } else if (*ch == '\\' && slash) {
      slash = false;
      new_node[count] = *ch;
      count++;
      GetNextChar(ch, line, column);
    } else {
      slash = false;
      new_node[count] = *ch;
      count++;
      GetNextChar(ch, line, column);
    }
    if (*ch == '\"' && !slash)
      break;
  }
  if (*ch == '\"') {
    new_node[count] = *ch;
    count++;
    GetNextChar(ch, line, column);
  }
  new_node[count] = '\0';
  return new_node;
}

/** 讀進一個SPECIAL token字串，儲存進heap且回傳該字串的起頭位置
  * 當此function結束時，ch/line/column的內容應更新成緊接此數字之後的字元。
  * Here is a list of all SPECIAL tokens :
  *   ^   ,   (   )   [   ]   {   }   :   ;   #  ?
  *   +   -   *   /   >   <   =   !   %   &   |
  *   +=  -=  *=  /=  >=  <=  ==  !=  %=  &&  ||
  *   ++  --          >>  
  *       ->
  * @param ch 傳入時是一個SPECIAL token(e.g., ==)的開頭
  * @param line ch的line-no
  * @param column ch的column-no
  * @return 指向此字串的pointer
  */
CharPtr GetSpecial(char *ch, int *line, int *column) {
  char buffer[3]; // Max 2 chars + null terminator
  int count = 0;
  char first = *ch;

  buffer[count++] = first;
  GetNextChar(ch, line, column); // Consume the first char

  char second = *ch; // Peek at the next character
  bool is_two_char = false;

  // Check for possible two-character tokens based on the first char
  switch (first) {
    case '+':
      if (second == '+' || second == '=') {
        is_two_char = true;
        break;
      }
    case '-':
      if (second == '-' || second == '>' || second == '=') {
        is_two_char = true;
        break;
      }
    case '*':
    case '/':
    case '%':
    case '=': // For ==
    case '!': // For !=
      if (second == '=') {
        is_two_char = true;
        break;
      }
    case '>':
      if (second == '=' || second == '>') {
        is_two_char = true; // Added >>
        break;
      }
    case '<':
      // **FIXED: Added << check**
      if (second == '=' || second == '<') {
        is_two_char = true;
        break;
      }
    case '&':
      if (second == '&') {
        is_two_char = true;
        break;
      }
    case '|':
      if (second == '|') {
        is_two_char = true;
        break;
      }
    
  }

  if (is_two_char) {
    buffer[count++] = second;      // Add the second character
    GetNextChar(ch, line, column); // Consume the second character
  }

  buffer[count] = '\0'; // Null terminate

  // **FIXED: Use strdup for safer memory allocation**
  CharPtr result = strdup(buffer);
  if (result == NULL) {
    perror("Failed to allocate memory for special token");
    // Handle error appropriately, maybe return NULL
    return NULL;
  }
  return result;
}
