#include<iostream>



using namespace std;

class User {
 public:
  string name;
  char gender;
  float height;
  float weight_latest;
  float weight_history[100];
  string date_history[100];

  void RecordWeight();

  void ShowData(); 
  void ShowLatestWeight();
  void CalculateBMI();
  void ShowWeightHistory();
  void ShowBMIHistory();
  void SmartCalculator();
};

int main() {
  User user;
  cin >> user.name;
  cin >> user.gender;
  cin >> user.height;
  user.RecordWeight();
  user.SmartCalculator();
  return 0;
}

void User::RecordWeight() {
  string date;
  float weight;
  for (int i = 0; i < 5; i++) {
    cin >> date;
    cin >> weight;
    date_history[i] = date;
    weight_history[i] = weight;
    weight_latest = weight;
  }
}

void User::ShowData() {
  cout << name << "/" << gender << "/" << height << endl;
}

void User::ShowLatestWeight() {
  cout << weight_latest << endl;
}

void User::CalculateBMI() {
  float h = height / 100;
  float bmi = weight_latest / (h * h);
  bmi = int(bmi * 10) / 10.0;
  cout << fixed << setprecision(1) << bmi << endl;
}


void User::ShowWeightHistory() {
  for (int i = 0; i < 5; i++) {
    cout << weight_history[i] << endl;
  }
}

void User::ShowBMIHistory() {
  for (int i = 0; i < 5; i++) {
    float h = height / 100;
    float bmi = weight_history[i] / (h * h);
    bmi = int(bmi * 10) / 10.0;
    cout << fixed << setprecision(1) << bmi << endl;
  }
}


void User::SmartCalculator() {
  int operation = 6;
  cin >> operation;
  while (operation != 6) {
    if (operation == 1) {
      ShowData();
    } else if (operation == 2) {
      ShowLatestWeight();
    } else if (operation == 3) {
      CalculateBMI();
    } else if (operation == 4) {
      ShowWeightHistory();
    } else if (operation == 5) {
      ShowBMIHistory();
    }
    cin >> operation;
  }
}