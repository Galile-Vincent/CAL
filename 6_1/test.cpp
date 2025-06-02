#include <sstream>
#include <vector>
#include <algorithm>
#include <iostream>

/*
指令
功能
b 印出目前的「工作buffer」的名字
rb name 把目前的「工作buffer」的名字改為name (rb means "rename buffer")
lb 把所有的buffer的名字依照buffer建立的順序列出來 (lb means "list buffers")
cb name 切換到name這個buffer(以name這個buffer作為目前的「工作buffer」)，若無此buffer，就是error (cb means "change buffer")
db 刪除目前的工作buffer。當目前的buffer被刪除後，接在其後產生的buffer就應該要優先「往前遞補」。若此buffer已經是唯一剩下的buffer，要視為錯誤，不能刪除。
db name 刪除指定名字的buffer。當此buffer被刪除後，接在其後產生的buffer就應該要優先「往前遞補」。若無此名字的buffer，就是error；此外，若此buffer已經是唯一剩下的buffer，也要視為錯誤，不能刪除。
nb 產生一個新的、由系統取名的buffer，並以它作為目前的「工作buffer」。(buffer之預設名稱是依"第幾次"產生的buffer的順序命名，e.g., 第五次產生的buffer其預設名稱為"Buffer-4"，不管前面幾次產生的buffer是否有被改名或是被刪除)
nb name 產生一個新的、名叫'name'的buffer，並以它作為目前的「工作buffer」 (nb means "new buffer")
*/

// Helper: case-insensitive string compare
bool iequals(const std::string& a, const std::string& b) {
  if (a.size() != b.size()) return false;
  for (size_t i = 0; i < a.size(); ++i) {
    if (tolower(a[i]) != tolower(b[i])) return false;
  }
  return true;
}

// Helper: list of valid commands (case-insensitive)
bool IsNormalCommand_Buffer(const std::string& cmd) {
  static std::vector<std::string> valid = {"b", "rb", "lb", "cb", "db", "nb"};
  for (const auto& v : valid) {
    if (iequals(cmd, v)) {
      return true;
    }
  }
  return false;
}

// Modified IsValidCommand (no transform)
bool IsValidCommand_Buffer(std::string &command, std::string &name) {
  std::istringstream iss(command);
  std::string token;
  std::string found_cmd, found_name;

  while (iss >> token) {
    if (IsNormalCommand_Buffer(token)) {
      found_cmd = token;
      // Try to get the next token as name (if needed)
      if (iequals(found_cmd, "rb") || iequals(found_cmd, "cb") ||
          iequals(found_cmd, "db") || iequals(found_cmd, "nb")) {
        if (iss >> found_name) {
          name = found_name;
        } else {
          name = "";
       }
      } else {
       name = "";
      }
      command = found_cmd;
      return true;
    }
  }
  // No valid command found
  command = "";
  name = "";
  return false;
}

int main() {
 std::string input;
 std::cout << "Enter command lines (Ctrl+D to end):\n";
 while (std::getline(std::cin, input)) {
  std::string cmd = input;
  std::string name;
  if (IsValidCommand_Buffer(cmd, name)) {
   std::cout << "Extracted command: " << cmd << "\n";
   if (!name.empty())
    std::cout << "Extracted name: " << name << "\n";
   else
    std::cout << "No name extracted.\n";
  } else {
   std::cout << "No valid command found.\n";
  }
  std::cout << "----\n";
 }
 return 0;
}