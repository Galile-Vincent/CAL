#include<iostream>
#include <vector>

/*
In c++ vector
add thing to the end: push_back
insert thing at a position: insert
*/

class Buffer {
 private:
  int current_line = 0;
  std::vector<std::string> contents;
 public:
  Buffer() {
  }
  bool Append(std::string input);
  bool Insert(std::string input);
  bool Change(std::string input, bool is_init);
  void PrintLast();
  bool Delete();
  void Print(bool print_all);
  int GetCurrent() {
    return current_line;
  }
  int GetSize() {
    return contents.size();
  }
  void UpdateCur(int cur) {
    current_line = cur;
  }
};

enum ErrorCode {
  NO_DATA,
  INVALID_COMMAND
};
void Error(ErrorCode error) {
  switch (error) {
    case NO_DATA:
      std::cout << "Error : There is no data! Please try again." << std::endl;
      break;
    case INVALID_COMMAND:
      std::cout << "Error : Illegal command! Please try again." << std::endl;
      break;
  }
}
std::string extractCommand(const std::string& input) {
  for (size_t i = 0; i < input.size(); ++i) {
    char c = input[i];

    if (std::isspace(c)) {
      continue;
    }

    if (c == 'a' || c == 'i' || c == 'p' || c == 'q' || c == 'd' || c == 'c' || c == '$') {
      if (i + 1 >= input.size() ||
          (i + 1 < input.size() && input[i + 1] == ' ')) {
        return std::string(1, c);
      }
    } else if (c == '%' && i + 1 < input.size() && input[i + 1] == 'p') {
      return "%p";
    } else {
      return "INVALID";
    }
  }

  return ""; // 全空白行
}


void Operations(Buffer &buffer) {
  std::string command;
  while (std::getline(std::cin, command)) {
    command = extractCommand(command);
    // std::cin.ignore();
    if (command == "a") {
      std::string input;
      while (std::getline(std::cin, input)) {
        if (input == ".") {
          break;
        } else {
          if (!buffer.Append(input)) {
            Error(INVALID_COMMAND);
          }
        }
      }
    } else if (command == "i") {
      /*
      if (buffer.GetCurrent() != 0) {
        buffer.UpdateCur(buffer.GetCurrent() - 1);
      }
      std::string input;
      while (std::getline(std::cin, input)) {
        if (input == ".") {
          break;
        } else {
          if (!buffer.Insert(input)) {
            Error(INVALID_COMMAND);
          }
        }
      }
      */
      while (std::getline(std::cin, command)) {
        if (command == ".") {
          break;
        } else {
          if (!buffer.Insert(command, false)) {
            Error(INVALID_COMMAND);
          }
        }
      }
      buffer.UpdateCur(buffer.GetCurrent() - 1);
    } else if (command == "p") {
      buffer.Print(false);
    } else if (command == "%p") {
      buffer.Print(true);
    } else if (command == "d") {
      buffer.Delete();
    } else if (command == "c") {
      if (buffer.GetCurrent() == 0 && buffer.GetSize() == 0) {
        Error(NO_DATA);
        continue;
      } else {
        bool is_init = true;
        std::string input;
        while (std::getline(std::cin, input)) {
          if (input == ".") {
           break;
          } else {
            if (!buffer.Change(input, is_init)) {
              Error(INVALID_COMMAND);
              break;
            }
            is_init = false;
          }
        }
      }
    } else if (command == "$") {
      buffer.PrintLast();
    } else if (command == "q") {
      break;
    } else {
      Error(INVALID_COMMAND);
    }
  }
}

int main() {
  Buffer buffer;
  std::cout << "Welcome to use CYCUICE editor..." << std::endl;
  Operations(buffer);
  std::cout << "Thank you for using CYCUICE editor!" << std::endl;
  return 0;
}

bool Buffer::Append(std::string input) {
  if (input.empty()) {
    Error(INVALID_COMMAND);
    return false;
  }
  contents.insert(contents.begin() + current_line, input);
  current_line++;
  return true;
}

/*
bool Buffer::Insert(std::string input) {
  if (input.empty()) {
    Error(INVALID_COMMAND);
    return false;
  }
  if (contents.size() == 0) {
    return Append(input);
  }
  contents.insert(contents.begin() + current_line, input);
  current_line++;
  return true;
}
*/

bool Buffer::Insert(std::string input) {
  if (input.empty()) {
    Error(INVALID_COMMAND);
    return false;
  }
  if (contents.size() == 0) { // Empty
    return Append(input);
  }
  contents.insert(contents.begin() + current_line - 1, input);
  current_line++;
  return true;
}

bool Buffer::Change(std::string input, bool is_init) {
  if (input.empty()) {
    return Delete();
  }
  if (contents.size() == 0) {
    Error(NO_DATA);
    return false;
  }
  if (is_init) {
    contents[current_line - 1] = input;
  } else {
    return Append(input);
  }
  
  return true;
}

bool Buffer::Delete() {
  if (contents.empty()) {
    Error(NO_DATA);
    return false;
  }
  if (current_line - 1 >= 0 && current_line <= contents.size()) {
    contents.erase(contents.begin() + current_line - 1);
    if (current_line == contents.size() + 1) {
      current_line--;
    }
    return true;
  } else {
    Error(NO_DATA);
    return false;
  }
}

void Buffer::PrintLast() {
  if (contents.empty()) {
    Error(NO_DATA);
  } else {
    current_line = contents.size();
    std::cout << current_line << " " << contents.back() << std::endl;
  }
}

void Buffer::Print(bool printall) {
  if (contents.empty()) {
    Error(NO_DATA);
  } else if (printall) {
    for (int i = 0; i < contents.size(); i++) {
      std::cout << i + 1 << " " << contents.at(i) << std::endl;
    }
  } else {
    if (current_line > 0 && current_line <= contents.size()) {
      std::cout << contents.at(current_line - 1) << std::endl;
    } else {
      Error(NO_DATA);
    }
  }
}

/*
  i
Whatever will be will be.
.
i
The future's not ours to see. Que Sera Sera.
.
%p
d
d
c
What will bee will bee.
.
a
This is a line
.
c
What will be will be.
.
%p
q 
你的輸出 : 
Welcome to use CYCUICE editor...
1 The future's not ours to see. Que Sera Sera.
2 Whatever will be will be.
1 What will bee will bee.
2 What will be will be.
Thank you for using CYCUICE editor!

----------------------輸出不包含此行虛線
正確輸出 : 
Welcome to use CYCUICE editor...
1 The future's not ours to see. Que Sera Sera.
2 Whatever will be will be.
Error : There is no data! Please try again.
Error : Illegal command! Please try again.
Error : Illegal command! Please try again.
1 What will be will be.
Thank you for using CYCUICE editor!

----------------------輸出不包含此行虛線
*/

/*
a
    This is the first line of input.
.
i
This is the third line of input.
This is the second line of input.
  .
.
%p
$
a
This is the end of input.
.
%p
q
你的輸出 :
Welcome to use CYCUICE editor...
1 This is the third line of input.
2 This is the second line of input.
3   .
4     This is the first line of input.
    This is the first line of input.
1 This is the third line of input.
2 This is the second line of input.
3   .
4     This is the first line of input.
5 This is the end of input.
Thank you for using CYCUICE editor!

----------------------輸出不包含此行虛線
正確輸出 :
Welcome to use CYCUICE editor...
1 This is the third line of input.
2 This is the second line of input.
3   .
4     This is the first line of input.
4     This is the first line of input.
1 This is the third line of input.
2 This is the second line of input.
3   .
4     This is the first line of input.
5 This is the end of input.
Thank you for using CYCUICE editor!

----------------------輸出不包含此行虛線
*/

/*
c
p
%p
i
This is the third line of input.
This is the fourth line of input.
.
%p
p
d
%p
p
i
This is the fifth line of input.
.
i
This is the sixth line of input.
.
p
  $
a
Hello world!
..
.
%p
q
你的輸出 :
Welcome to use CYCUICE editor...
Error : There is no data! Please try again.
Error : Illegal command! Please try again.
Error : There is no data! Please try again.
1 This is the third line of input.
2 This is the fourth line of input.
This is the fourth line of input.
1 This is the third line of input.
This is the third line of input.
This is the sixth line of input.
3 This is the third line of input.
1 This is the sixth line of input.
2 This is the fifth line of input.
3 This is the third line of input.
4 Hello world!
5 ..
Thank you for using CYCUICE editor!

----------------------輸出不包含此行虛線
正確輸出 :
Welcome to use CYCUICE editor...
Error : There is no data! Please try again.
Error : There is no data! Please try again.
Error : There is no data! Please try again.
1 This is the third line of input.
2 This is the fourth line of input.
This is the fourth line of input.
1 This is the third line of input.
This is the third line of input.
This is the sixth line of input.
3 This is the third line of input.
1 This is the sixth line of input.
2 This is the fifth line of input.
3 This is the third line of input.
4 Hello world!
5 ..
Thank you for using CYCUICE editor!

----------------------輸出不包含此行虛線
*/