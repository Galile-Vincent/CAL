#include <iostream>

class Date {
 private:
  int year;
  int month;
  int day;
 public:
  Date() {
  }
  Date(int y, int m, int d) {
    year = y;
    month = m;
    day = d;
  }
  void SetYear(int y) { 
    year = y; 
  }
  void SetMonth(int m) { 
    month = m; 
  };
  void SetDay(int d) { 
    day = d; 
  };
  int GetYear() { 
    return year; 
  }
  int GetMonth() { 
    return month; 
  }
  int GetDay() { 
    return day; 
  }
};

class Age {
 private:
  int n_year;
  int n_month;
  int n_day;
 public:
  Age() {
    n_year = 0;
    n_month = 0;
    n_day = 0;
  }
  Age(int n_y, int n_m, int n_d) {
    n_year = n_y;
    n_month = n_m;
    n_day = n_d;
  }
  void DisplayAge(bool show_month, bool show_day) {
    std::cout << "year:" << n_year << std::endl;
    if (show_month && n_month != 0) {
      std::cout << "month:" << n_month << std::endl;
    }
    if (show_day && n_day != 0) {
      std::cout << "day:" << n_day << std::endl;
    }
  }
};

class Person {
 private:
  std::string name;
  Age age;
 public:
  Person(std::string n, Age a) {
    name = n;
    age = a;
  }
  
  void DisplayInfo(bool show_month, bool show_day) {
    std::cout << "name:" << name << std::endl;
    age.DisplayAge(show_month, show_day);  
  }
};
bool IsLeap(int year) {
  return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int DaysInMonth(int year, int month) {
  static int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  if (month == 2 && IsLeap(year)) {
    return 29;
  }
  return days[month - 1];
}

Age CalculateAge(Date birth_date, Date current_date) {
  int year = current_date.GetYear() - birth_date.GetYear();
  int month = current_date.GetMonth() - birth_date.GetMonth();
  int day = current_date.GetDay() - birth_date.GetDay();

  if (day < 0) {
    month--;
    day += DaysInMonth(current_date.GetYear(), current_date.GetMonth());
  }
  if (month < 0) {
    year--;
    month += 12;
  }
  return Age(year, month, day);
}

int main() {
  Date birth_date;
  Date current_date;
  std::string name;
  int year, month, day;
  int type = 0;
  bool show_month = false;
  bool show_day = false;

  std::cin >> year >> month >> day;
  birth_date.SetYear(year);
  birth_date.SetMonth(month);
  birth_date.SetDay(day);

  std::cin >> year >> month >> day;
  current_date.SetYear(year);
  current_date.SetMonth(month);
  current_date.SetDay(day);
  std::cin >> name;

  std::cin >> type;

  if (type == 1) {
    show_month = false;
    show_day = false;
  } else if (type == 2) {
    show_month = true;
    show_day = false;
  } else if (type == 3) {
    show_month = true;
    show_day = true;
  }

  Age age = CalculateAge(birth_date, current_date);
  
  Person person(name, age);
  person.DisplayInfo(show_month, show_day);

  return 0;
}