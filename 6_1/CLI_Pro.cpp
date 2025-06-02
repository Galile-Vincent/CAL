#include<iostream>
#include <vector>
#include <sstream>

/*
In c++ vector
add thing to the end: push_back
insert thing at a position: insert
*/

class Buffer {
 private:
  std::string name = "buffer";
  int current_line = 0;
  std::vector<std::string> contents;
 public:
  Buffer() {
  }
  bool Append(std::string input);
  bool Insert(std::string input, bool is_init);
  bool Change(std::string input, bool is_init);
  void PrintLast();
  bool Delete();
  void Print(bool print_all);
  int GetCurrent() {
    return current_line;
  }
  void SetName(std::string name) {
    this->name = name;
  }
  std::string GetName() {
    return name;
  }
  int GetSize() {
    return contents.size();
  }
  std::string GetContent(int index) {
    if (index >= 0 && index < contents.size()) {
      return contents[index];
    }
    return "ERROR";
  }
  void UpdateCur(int cur) {
    current_line = cur;
  }
};

class BufferManager {
 private:
  std::vector<Buffer> buffers;
  int current_buffer_index = -1;

 public:
  void AddBuffer(Buffer buffer, std::string name = "") {
    if (name.empty()) {
      name = "Buffer-" + std::to_string(buffers.size());
    }
    buffer.SetName(name);
    buffers.push_back(buffer);
    current_buffer_index = buffers.size() - 1; // Set the new buffer as current
  }
  BufferManager() {
    // Initialize with a default buffer
    Buffer default_buffer;
    default_buffer.SetName("Buffer-0");
    buffers.push_back(default_buffer);
    current_buffer_index = 0; // Set the first buffer as current
  }
  Buffer& GetCurrentBuffer() {
    if (current_buffer_index >= 0 && current_buffer_index < buffers.size()) {
      return buffers[current_buffer_index];
    }
    throw std::out_of_range("No current buffer available.");
  }
  int GetBufferByName(std::string name) {
    for (size_t i = 0; i < buffers.size(); ++i) {
      if (buffers[i].GetName() == name) {
        return i;
      }
    }
    return -1; // Not found
  }
  void SetCurrentBuffer(int index) {
    if (index >= 0 && index < buffers.size()) {
      current_buffer_index = index;
    } else {
      throw std::out_of_range("Invalid buffer index.");
    }
  }
  int GetCurrentBufferIndex() {
    return current_buffer_index;
  }

  int GetBufferCount() {
    return buffers.size();
  }

  /*
  Remember to check if the name exist
  Call the GetBufferByName function to find the index
  */
  void DeleteBuffer(int index) {
    if (index >= 0 && index < buffers.size()) {
      buffers.erase(buffers.begin() + index);
      if (current_buffer_index >= buffers.size()) {
        current_buffer_index = buffers.size() - 1; // Adjust current index
      }
    } else {
      throw std::out_of_range("Invalid buffer index.");
    }
  }

  void RenameBuffer(std::string name) {
    if (current_buffer_index >= 0 && current_buffer_index < buffers.size()) {
      if (name.empty()) {
        throw std::invalid_argument("Buffer name cannot be empty.");
      }
      buffers[current_buffer_index].SetName(name);
    } else {
      throw std::out_of_range("No current buffer available.");
    }
  }

  void PrintBuffer(Buffer &buffer, int place) {
    std::cout << buffer.GetName() << " " << buffer.GetSize() << std::endl;
  }

  void PrintCurrentBuffer() {
    if (current_buffer_index >= 0 && current_buffer_index < buffers.size()) {
      Buffer &current_buffer = buffers[current_buffer_index];
      PrintBuffer(current_buffer, current_buffer_index);
    } else {
      throw std::out_of_range("No current buffer available.");
    }
  }
  void PrintAllBuffer() {
    for (size_t i = 0; i < buffers.size(); ++i) {
      PrintBuffer(buffers[i], i);
    }
  }
};



enum ErrorCode {
  NO_DATA,
  NO_BUFFER,
  BUFFER_EMPTY,
  INVALID_COMMAND,
  OUT_OF_RANGE
};
void Error(ErrorCode error) {
  switch (error) {
    case NO_DATA:
      std::cout << "Error : There is no data! Please try again." << std::endl;
      break;
    case INVALID_COMMAND:
      std::cout << "Error : Illegal command! Please try again." << std::endl;
      break;
    case OUT_OF_RANGE:
      std::cout << "Error : Line number out of range! Please try again."
                << std::endl;
      break;
    case NO_BUFFER:
      std::cout << "Error : There is no such buffer! Please try again." 
                << std::endl;
      break;
    case BUFFER_EMPTY:
      std::cout << "Error : buffer name cannot be empty! Please try again." 
                << std::endl;
      break;
  }
}


void PrintLine(int line, Buffer &buffer) {
  if (line < 1 || line > buffer.GetSize()) {
    Error(NO_DATA);
  } else {
    std::cout << line << ": " << buffer.GetContent(line - 1) << std::endl;
    buffer.UpdateCur(line);
  }
}

bool Operations(Buffer &buffer, std::string command);
void OperationPro();

int main() {
  std::cout << "Welcome to use CYCUICE editor..." << std::endl;
  OperationPro();
  std::cout << "Thank you for using CYCUICE editor!" << std::endl;
  return 0;
}


bool BufferAction(BufferManager &buffer_manager, std::string command, 
                  std::string name = "") {
  if (command == "b") {
    buffer_manager.PrintCurrentBuffer();
    return true;
  } else if (command == "lb") {
    buffer_manager.PrintAllBuffer();
    return true;
  } else if (command == "db") {
    if (name.empty()) {
      if (buffer_manager.GetBufferCount() > 1) {
        buffer_manager.DeleteBuffer(buffer_manager.GetCurrentBufferIndex());
        return true;
      } else {
        Error(INVALID_COMMAND);
        return true;
      }
    } else {
      int index = buffer_manager.GetBufferByName(name);
      if (index != -1) {
        buffer_manager.DeleteBuffer(index);
      } else {
        Error(NO_BUFFER);
        return true;
      }
    }
    return true;
  } else if (command == "nb") {
    if (name.empty()) {
      buffer_manager.AddBuffer(Buffer());
    } else {
      buffer_manager.AddBuffer(Buffer(), name);
    }
    return true;
  } else if (command == "cb") {
    if (name.empty()) {
      Error(BUFFER_EMPTY);
      return true;
    } else {
      int index = buffer_manager.GetBufferByName(name);
      if (index != -1) {
        buffer_manager.SetCurrentBuffer(index);
        buffer_manager.RenameBuffer(name);
      } else {
        Error(NO_BUFFER);
      }
      return true;
    }
  } else if (command == "rb") {
    if (name.empty()) {
      Error(BUFFER_EMPTY);
      return true;
    } else {
      // Change the name of current buffer
      buffer_manager.RenameBuffer(name);
    }
    return true;
  } else {
    Error(INVALID_COMMAND);
    return true;
  }
  return false;
}

// Helper: case-insensitive string compare
bool Iequals(const std::string& a, const std::string& b) {
  if (a.size() != b.size()) return false;
  for (size_t i = 0; i < a.size(); i++) {
    if (tolower(a[i]) != tolower(b[i])) return false;
  }
  return true;
}

// Helper: list of valid commands (case-insensitive)

bool IsNormalCommandBuffer(const std::string& cmd) {
  static std::vector<std::string> valid;
  if (valid.empty()) {
    valid.push_back("b");
    valid.push_back("rb");
    valid.push_back("lb");
    valid.push_back("cb");
    valid.push_back("db");
    valid.push_back("nb");
  }
  for (const auto& v : valid) {
    if (Iequals(cmd, v)) {
      return true;
    }
  }
  return false;
}

// Modified IsValidCommand (no transform)
bool IsValidCommandBuffer(std::string &command, std::string &name, int &place) {
  std::istringstream iss(command);
  std::string token;
  std::string found_cmd, found_name;
  int token_index = 0;
  place = 0;
  while (iss >> token) {
    place += token.length(); // Update place to the end of the token
    if (IsNormalCommandBuffer(token)) {
      found_cmd = token;
      // Try to get the next token as name (if needed)
      if (Iequals(found_cmd, "rb") || Iequals(found_cmd, "cb") ||
          Iequals(found_cmd, "db") || Iequals(found_cmd, "nb")) {
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
    token_index++;
  }
  // No valid command found
  command = "";
  name = "";
  place = -1;
  return false;
}

bool IsInt(char ch) {
  return ch >= '0' && ch <= '9';
}

bool IsInvalid(char ch) {
  
  return !(IsInt(ch) || ch == 'a' || ch == 'i' || ch == 'p' || ch == 'q' ||
           ch == 'd' || ch == 'c' || ch == '$' || ch == '%' || ch == '.');
}

bool IsNormalCommand(std::string &command) {
  std::string valid[] = {"a",  ".a", "$a", "i",  ".i", "$i", "c",
                         ".c", "$c", "d",  ".d", "$d", ".p", "%p",
                         "p",  "q",  "$p", "$",  "."};
  for (auto &valid_command : valid) {
    if (command == valid_command) {
      return true;
    }
  }
  return false;
}

bool IsInt(std::string &command) {
  if (command.empty()) {
    return false;
  }
  for (char c : command) {
    if (!IsInt(c)) {
      return false;
    }
  }
  return true;
}

bool IsValidCommand(std::string &command, int &place) {
  std::string temp;
  bool skip_next = false; 
  bool is_sign = false;
  bool is_int = false;
  bool previous_is_int = false; 
  std::string int_str;
  if (command.empty()) return false;
  int idx = 0;
  for (char c : command) {
    if (c == '$') {
      is_sign = true;
      idx++;
      continue;
    }
    if (previous_is_int) {
      if (IsInt(c)) {
        int_str += c;
        idx++;
        continue;
      } else {
        std::string ch = std::string(1, c);
        if (c == ' ') {
          command = int_str;
          place = idx - int_str.size(); // Set place to start of int
          return true;
        } else if (IsNormalCommand(ch)) {
          command = int_str + ch;
          place = idx - int_str.size(); // Set place to start of int
          return true;
        } else {
          is_int = false;
          previous_is_int = false;
          skip_next = false;
          temp = "";
          idx++;
          continue;
        }
      }
    } else {
      if (IsInt(c)) {
        is_int = true;
        int_str += c;
        previous_is_int = true;
        temp = "";
        idx++;
        continue;
      }
    }
    if (c == ' ') {
      if (previous_is_int) {
        place = idx - int_str.size();
        break;
      }
      is_int = false;
      previous_is_int = false;
      skip_next = false;

      if (IsNormalCommand(temp)) {
        place = idx - temp.size();
        break;
      } else {
        idx++;
        continue;
      }
    }
    c = std::tolower(c);
    if (!IsInvalid(c) && !skip_next) {
      skip_next = false;
      temp += c;
    } else {
      is_int = false;
      if (is_sign || is_int) {
        break;
      }
      skip_next = true;
      temp = "";
      if (IsNormalCommand(temp)) {
        place = idx - temp.size();
        break;
      }
    }
    idx++;
  }
  place = idx; // Set place to the end of the command
  if (is_int && temp != "a" && temp != "i" && temp != "c" && temp != "d" &&
      temp != "p") {
    command = int_str;
  } else if (is_int) {
    command = int_str + temp;
  } else if (is_sign &&
             (temp != "a" && temp != "i" && temp != "c" && temp != "d" &&
              temp != "p")) {
    command = "$";
    return true;
  } else if (is_sign) {
    command = "$" + temp;
    return true;
  } else {
    command = temp;
  }
  return !command.empty() && (IsNormalCommand(command) || IsInt(command));
}

void InsertOperation(Buffer &buffer) {
  bool is_init = false;
  if (buffer.GetCurrent() == 0 && buffer.GetSize() == 0) {
    is_init = true;
  }
  int count = 0;
  std::string input;
  while (std::getline(std::cin, input)) {
    if (input == ".") {
      break;
    } else {
      if (count == 0) {
        if (!buffer.Insert(input, is_init)) {
          Error(INVALID_COMMAND);
        } else {
          count++;
        }
      } else {
        if (!buffer.Append(input)) {
          Error(INVALID_COMMAND);
        }
      }
    }
  }
  // std::cout << "Current line: " << buffer.GetCurrent() << std::endl;
}

void ChangeOperation(Buffer &buffer) {
  if (buffer.GetCurrent() == 0 && buffer.GetSize() == 0) {
    Error(NO_DATA);
    return;
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
}

void AddOperation(Buffer &buffer) {
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
}

bool Operations(Buffer &buffer, std::string command) {
  int temp_place = buffer.GetCurrent();
  bool updated = false;
  int a;
  if (!IsValidCommand(command, a)) {
    Error(INVALID_COMMAND);
    return true;
  }

  if (command.at(0) == '$' && command.size() > 1) {
    command = command.substr(1);
    // No data
    if (buffer.GetSize() == 0) {
      Error(NO_DATA);
      return true;
    } else {
      buffer.UpdateCur(buffer.GetSize());
      // updated = true;
    }
  } else if (IsInt(command.at(0)) && !IsInt(command)) {
    std::string temp_command;
    for (char c : command) {
      if (IsInt(c)) {
        temp_command += c;
      } else {
        break;
      }
    }
    command = command.at(command.size() - 1);
    int line_number = std::stoi(temp_command);
    if (line_number < 1 || line_number > buffer.GetSize()) {
      Error(OUT_OF_RANGE);
      return true;
    } else {
      buffer.UpdateCur(line_number);
      if (command == "p") {
        updated = true;
      }
    }
  }
    
  if (command == "a" || command == ".a") {
    AddOperation(buffer);
    return true;
  } else if (command == "i" || command == ".i") {
    InsertOperation(buffer);
    return true;
  } else if (command == "p" || command == ".p") {
    buffer.Print(false);
    if (updated) {
      buffer.UpdateCur(temp_place);
    }
    return true;
  } else if (command == "%p") {
    buffer.Print(true);
    return true;
  } else if (command == "d" || command == ".d") {
    buffer.Delete();
    return true;
  } else if (command == "c" || command == ".c") {
    ChangeOperation(buffer);
    return true;
  } else if (command == ".") {
    if (buffer.GetCurrent() == 0 && buffer.GetSize() == 0) {
      Error(NO_DATA);
      return true;
    }
    std::cout << "You're on line " << buffer.GetCurrent() << "." << std::endl;
    return true;
  } else if (command == "$") {
    buffer.PrintLast();
    return true;
  } else if (IsInt(command)) {
    int line_number = std::stoi(command);
    if (line_number < 1 || line_number > buffer.GetSize()) {
      Error(OUT_OF_RANGE);
      return true;
    }
    PrintLine(std::stoi(command), buffer);
    return true;
  } else {
    Error(INVALID_COMMAND);
    return true;
  }
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

bool Buffer::Insert(std::string input, bool is_init) {
  if (input.empty()) {
    Error(INVALID_COMMAND);
    return false;
  }
  if (contents.size() == 0) {
    return Append(input);
  }
  if (!is_init) {
    current_line--;
  }
  contents.insert(contents.begin() + current_line, input);
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
    std::cout << current_line << ": " << contents.back() << std::endl;
  }
}

void Buffer::Print(bool printall) {
  if (contents.empty()) {
    Error(NO_DATA);
  } else if (printall) {
    for (int i = 0; i < contents.size(); i++) {
      std::cout << i + 1 << ": " << contents.at(i) << std::endl;
    }
  } else {
    if (current_line > 0 && current_line <= contents.size()) {
      std::cout << contents.at(current_line - 1) << std::endl;
    } else {
      Error(NO_DATA);
    }
  }
}

void OperationPro() {
  BufferManager buffer_manager;
  std::string command;
  std::string command2;
  int place1, place2;
  while (std::getline(std::cin, command)) {
    command2 = command;
    std::string name;
    bool is_valid = IsValidCommand(command, place1);
    bool is_buffer = IsValidCommandBuffer(command2, name, place2);
    if (is_valid && is_buffer) {
      if (place1 > place2) {
        is_valid = false;
      }
    }
    if (is_valid) {
      if (buffer_manager.GetCurrentBufferIndex() == -1) {
        Error(NO_BUFFER);
        continue;
      }
      if (command == "q") {
        break;
      } else if (Operations(buffer_manager.GetCurrentBuffer(), command)) {
        // Operation successful
        continue;
      } else {
        Error(INVALID_COMMAND);
      }
    } else {
      if (!is_buffer) {
        Error(INVALID_COMMAND);
        continue;
      }
      if (command2 == "q") {
        break;
      } else if (BufferAction(buffer_manager, command2, name)) {
        continue;
      } else {
        Error(INVALID_COMMAND);
      }
    }
  }
}