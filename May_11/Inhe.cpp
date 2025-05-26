#include <iostream>

// TODO: put your class design here
class Employee {
 protected:  // use protected keyword so that this member data can be inherited
  std::string name;
 public:
  Employee() {
  }
  explicit Employee(std::string name) { 
    this->name = name; 
  }
  std::string GetName() { 
    return name; 
  }
  void SetName(std::string name) { 
    this->name = name; 
  }
  // pure virtual function which forces derived classes to override
  virtual std::string SalaryDescription() = 0;
};

class Salesperson: public Employee {
 private:
  double gross_sales;
  double commission_rate;
  double salary_per_month;
 public:
  Salesperson() {
  }
  explicit Salesperson(double salary_per_month, double commission_rate) {
    this->salary_per_month = salary_per_month;
    this->commission_rate = commission_rate;
  }

  void SetGrossSales(double gross_sales) {
    this->gross_sales = gross_sales;
  }

  int GetAnnualSalary() {
    double annual_salary =
        salary_per_month * 12 + gross_sales * commission_rate;
    return int(annual_salary);
  }
  std::string SalaryDescription() {
    std::string str = "Salesperson:" + std::to_string(int(GetAnnualSalary()));
    return str;
  }
};

class SalariedEmployee: public Employee {
 private:
  double salary_per_month;
 public:
  SalariedEmployee() {
  }
  explicit SalariedEmployee(double salary_per_month) {
    this->salary_per_month = salary_per_month; 
  }
  double GetAnnualSalary() { 
    return salary_per_month * 12; 
  }
  double GetSalaryPerMonth() { 
    return int(salary_per_month); 
  }
  void SetSalary(double salary_per_month) { 
    this->salary_per_month = salary_per_month;
  }
  std::string SalaryDescription() {
    std::string str = "Salaried employee:"; 
    str+=std::to_string(int(GetAnnualSalary()));
    return str;
  }
};
 
class ConsolePrinter {
 public:
  void Print(std::string str) {
    std::cout << str << std::endl;
  }
};
int main() {
  ConsolePrinter printer;
  double salary = 0.0;
  std::cin >> salary;
  SalariedEmployee tom = SalariedEmployee(salary);
  printer.Print(tom.SalaryDescription());
  double rate = 0.0;
  std::cin >> salary >> rate;
  Salesperson mary = Salesperson(salary, rate);
  double gross_sales = 0.0;
  std::cin >> gross_sales;
  mary.SetGrossSales(gross_sales);
  printer.Print(mary.SalaryDescription());
  return 0;
}