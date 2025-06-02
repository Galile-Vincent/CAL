#include <iostream>

void Input(int num[], int &sign);

class HugeInt {
 private:
  int value[20];
  int sign;  // 1 for positive, -1 for negative

 public:
  HugeInt() {
    for (int i = 0; i < 20; ++i) value[i] = 0;
    sign = 1;
  }
  explicit HugeInt(int num[], int s = 1) {
    for (int i = 0; i < 20; ++i) value[i] = num[i];
    sign = s;
  }
  void GetValue(int arr[]) {
    for (int i = 0; i < 20; ++i) arr[i] = value[i];
  }
  int GetSign() { 
    return sign; 
  }
  void SetSign(int s) { 
    sign = s; 
  }
  void Add(HugeInt &hugeint2, int ans[], bool &broken);
  void Subtract(HugeInt &hugeint2, int ans[]);
  bool IsEqual(HugeInt &hugeint2);
  bool IsGreaterThan(HugeInt &hugeint2);
  bool IsLessThan(HugeInt &hugeint2);
};

void Parse(std::string str, int arr[], int &sign) {
  int index = 19;
  sign = 1;  // Default to positive
  for (int place = str.length() - 1; place >= 0; place--) {
    if (str[place] == '-') {
      sign = -1;
      return;
    }
    if (str[place] >= '0' && str[place] <= '9') {
      arr[index--] = str[place] - '0';
    } else {
      return; 
    }
  }
}
void Operation(HugeInt &hugeint, HugeInt &hugeint2);

int main() {
  int num[20] = {0};
  int sign = 1;
  Input(num, sign);
  HugeInt hugeint(num, sign);
  int num2[20] = {0};
  Input(num2, sign);
  HugeInt hugeint2(num2, sign);
  Operation(hugeint, hugeint2);
  return 0;
}

void Print(int arr[], int is_sign = 1, bool broken = false) {
  bool leading = false;
  if (broken) {
    leading = true;
  } else if (is_sign == -1) {
    std::cout << "-";
  }
  for (int i = 0; i < 20; ++i) {
    if (arr[i] != 0) {
      leading = true;
    }
    if (leading) {
      std::cout << arr[i];
    }
  }
  if (!leading) {
    std::cout << "0";
  }
  std::cout << std::endl;
}

void Input(int arr[], int &sign) {
  std::string str;
  std::cin >> str;
  Parse(str, arr, sign);
}


void HugeInt::Add(HugeInt &hugeint2, int ans[], bool &broken) {
  int carry = 0;
  int arr1[20], arr2[20];
  GetValue(arr1);
  hugeint2.GetValue(arr2);
  for (int i = 19; i >= 0; i--) {
    int sum = arr1[i] + arr2[i] + carry;
    if (sum >= 10) {
      if (i == 0) {
        broken = true;
      }
      carry = sum / 10;
      ans[i] = sum % 10;
    } else {
      carry = 0;
      ans[i] = sum;
    }
  }
}

void HugeInt::Subtract(HugeInt &hugeint2, int ans[]) {
  int borrow = 0;
  int arr1[20], arr2[20];
  GetValue(arr1);
  hugeint2.GetValue(arr2);
  for (int i = 19; i >= 0; i--) {
    int diff = arr1[i] - arr2[i] - borrow;
    if (diff < 0) {
      borrow = 1;
      diff += 10;
    } else {
      borrow = 0;
    }
    ans[i] = diff;
  }
}
bool HugeInt::IsEqual(HugeInt &hugeint2) {
  if (sign != hugeint2.GetSign()) {
    return false;
  }
  int arr1[20], arr2[20];
  GetValue(arr1);
  hugeint2.GetValue(arr2);
  for (int i = 0; i < 20; ++i) {
    if (arr1[i] != arr2[i]) {
      return false;
    }
  }
  return true;
}
bool HugeInt::IsGreaterThan(HugeInt &hugeint2) {
  if (sign != hugeint2.GetSign()) {
    return sign > hugeint2.GetSign();
  }

  int arr1[20], arr2[20];
  GetValue(arr1);
  hugeint2.GetValue(arr2);

  for (int i = 0; i < 20; ++i) {
    if (arr1[i] > arr2[i]) {
      return sign == 1;  // Positive is greater
    } else if (arr1[i] < arr2[i]) {
      return sign == -1;  // Negative is less
    }
  }
  return false;  // They are equal
}
bool HugeInt::IsLessThan(HugeInt &hugeint2) {
  if (sign != hugeint2.GetSign()) {
    return sign < hugeint2.GetSign();
  }
  if (sign == hugeint2.GetSign() && sign == -1) {
    return !IsGreaterThan(hugeint2);
  }
  if (sign == hugeint2.GetSign() && sign == 1) {
    return !IsGreaterThan(hugeint2);
  }
  return false;
}

void PrintBool(bool value) {
  if (value) {
    std::cout << "true" << std::endl;
  } else {
    std::cout << "false" << std::endl;
  }
}

void Operation(HugeInt &hugeint, HugeInt &hugeint2) {
  int operation;
  while (true) {
    std::cin >> operation;
    int ans[20] = {0};
    bool broken = false;
    switch (operation) {
      case 1: {
        if (hugeint.GetSign() == hugeint2.GetSign()) {
          hugeint.Add(hugeint2, ans, broken);
          Print(ans, hugeint.GetSign(), broken);
        } else {
          if (!hugeint.IsGreaterThan(hugeint2)) {
            hugeint2.Subtract(hugeint, ans);
            Print(ans, hugeint2.GetSign());
          } else {
            hugeint.Subtract(hugeint2, ans);
            Print(ans, hugeint.GetSign());
          }
        }
        break;
      }
      case 2: {
        if (hugeint.IsEqual(hugeint2)) {
          Print(ans, 1);
        } else if (hugeint.GetSign() != hugeint2.GetSign()) {
          hugeint.Add(hugeint2, ans, broken);
          Print(ans, hugeint.GetSign());
        } else {
          if (hugeint.GetSign() == -1 && hugeint2.GetSign() == -1) {
            if (hugeint.IsLessThan(hugeint2)) {
              hugeint.Subtract(hugeint2, ans);
              if (hugeint.IsEqual(hugeint2)) {
                Print(ans, 1);
              } else {
                Print(ans, -1);
              }
            } else {
              hugeint2.Subtract(hugeint, ans);
              Print(ans, 1);
            }
          } else {
            if (hugeint.IsLessThan(hugeint2)) {
              hugeint2.Subtract(hugeint, ans);
              Print(ans, -hugeint.GetSign());
            } else {
              hugeint.Subtract(hugeint2, ans);
              Print(ans, hugeint.GetSign());
            }
          }
        }
        break;
      }
      case 3:
        PrintBool(hugeint.IsEqual(hugeint2));
        break;
      case 4:
        PrintBool(hugeint.IsGreaterThan(hugeint2));
        break;
      case 5:
        PrintBool(hugeint.IsLessThan(hugeint2));
        break;
      case 6:
        return;
    }
  }
}

