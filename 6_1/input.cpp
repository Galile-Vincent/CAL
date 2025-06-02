#include<iostream>

bool IsInt(char ch) {
  return ch >= '0' && ch <= '9';
}

bool IsInvalid(char ch) {
  
  return !(IsInt(ch) || ch == 'a' || ch == 'i' || ch == 'p' || ch == 'q' ||
            ch == 'd' || ch == 'c' || ch == '$' || ch == '%' ||
            ch == '.');
}

bool IsCommand(std::string &command) {
  std::string valid[] = {"a", ".a", "$a", "i", ".i", "$i", "c", ".c", "$c", "d", ".d", "$d", ".p", "%p", "p", "q", "$p", "$", "."};
  for (auto &valid_command: valid) {
    if (command == valid_command) {
    }
  }
  return false;
}

bool IsInt(std::string &command) {
  if (command.empty()) return false;
  for (char c : command) {
    if (!IsInt(c)) {
      return false;
    }
  }
  return true;
}

bool IsValidCommand(std::string &command) {
  std::string temp;
  bool skip_next = false; // Ignore string section with invalid characters
  bool is_sign = false;
  bool is_int = false;
  bool previous_is_int = false; // Track if the previous character was an integer
  std::string int_str;
  if (command.empty()) return false;
  for (char c : command) {
    if (c == '$') {
      is_sign = true;
      continue;
    }
    if (previous_is_int) {
        if (IsInt(c)) {
            int_str += c;
            continue;
        } else {
            std::string ch = std::string(1, c);
            if (c == ' ') {
                command = int_str;
                return true;
            } else if (IsCommand(ch)) {
                command = int_str + ch;
                return true;
            } else {
                is_int = false;
                previous_is_int = false;
                skip_next = false;
                temp = "";
                continue;
            }
        }
    } else {
        if (IsInt(c)) {
            is_int = true;
            int_str += c;
            previous_is_int = true;
            temp = "";
            continue;
        }
    }
    if (c == ' ') {
        if (previous_is_int) {
            break;
        }
        is_int = false;
        previous_is_int = false;
        skip_next = false;

        if (IsCommand(temp)) {
            break;
        } else {
            continue;
        }
    }
    c = std::tolower(c);
    if (!IsInvalid(c) && !skip_next) {
        // is_sign = false;
        skip_next = false;
        temp += c;
    } else {
        is_int = false;
        if (is_sign || is_int) {
            break;
        }
        skip_next = true;
        temp = "";
        if (IsCommand(temp)) {
            break;
        }
    }
  }
  if (is_int && temp != "a" && temp != "i" && temp != "c" && temp != "d" &&
    temp != "p") {
    command = int_str;
    // return true;
  } else if (is_int) {
    command = int_str + temp;
    // return true;
  } else if (is_sign && (temp != "a" && temp != "i" && temp != "c" && temp != "d" &&
    temp != "p")) {
    command = "$";
    return true;
  } else if (is_sign ) {
    command = "$" + temp;
    return true;
  } else {
    command = temp;
  }
  return !command.empty() && IsCommand(command);
}

int main() {
  std::string command;
  while (std::getline(std::cin, command))
  {
      if (IsValidCommand(command))
      {
          std::cout << "Valid command: " << command << std::endl;
      }
      else
      {
          std::cout << "Invalid command: " << command << std::endl;
      }
  }
  return 0;
}




