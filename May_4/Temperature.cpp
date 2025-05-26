/*
請實作一個溫度計。這個溫度計應該具備以下幾個功能：

使用者能設定溫度
使用者能設定要顯示的是攝氏溫度或華氏溫度
能顯示目前記錄的溫度
輸入的規則是這樣的：使用者會先輸入一個數字(代表選項)，如果輸入的是1或是2，則後面接著的那個數字就是要設定的溫度(輸入1表示要設定攝氏溫度，輸入2 表示要設定華氏溫度)。如果輸入的是3，表示要顯示出目前記錄的溫度，如果輸入的是4，則要切換目前顯示的溫度標準(例如，如果目前是攝氏溫度標準，輸入4後會切換為華氏溫度標準)

所有的數字請顯示到小數點後第1位。(小數點後第2位四捨五入)
*/
#include<iostream>
#include <iomanip>
class Temperature {
  private:
    float celsius;
    float fahrenheit;
    int mode; // 1: Celsius, 2: Fahrenheit
  public:
    void SetTemperature(int mode, float temp);
    void ShowTemperature();
    void SwitchMode();
};
int main() {
  int mode;
  float temp = 0;
  Temperature t;

  while (std::cin >> mode) {
    if (mode == 1 || mode == 2) {
      if (std::cin >> temp) {
        t.SetTemperature(mode, temp);
      } else {
        break; // EOF or invalid input
      }
    } else if (mode == 3) {
      t.ShowTemperature();
    } else if (mode == 4) {
      t.SwitchMode();
    }
  }
}

void Temperature::SetTemperature(int m, float temp) {
  mode = m;
  if (mode == 1) {
    celsius = temp;
    fahrenheit = (celsius * 9 / 5) + 32;
    float temp = int(celsius * 10) / 10.0;
    std::cout << std::fixed << std::setprecision(1) << "the temperature is " << temp << " degree Celsius." << std::endl;
  } else if (mode == 2) {
    fahrenheit = temp;
    celsius = (fahrenheit - 32) * 5 / 9;
    float temp = int(fahrenheit * 10) / 10.0;
    std::cout << std::fixed << std::setprecision(1) << "the temperature is " << temp << " degree Fahrenheit." << std::endl;
  }
}

void Temperature::ShowTemperature() { // 3
  std::cout << "current temperature is ";
  if (mode == 1) {
    celsius = int(celsius * 10) / 10.0;
    std::cout << std::fixed << std::setprecision(1) << celsius << " degree Celsius." << std::endl;
  } else if (mode == 2) {
    fahrenheit = int(fahrenheit * 10) / 10.0;
    std::cout << std::fixed << std::setprecision(1) << fahrenheit << " degree Fahrenheit." << std::endl;
  }
}

void Temperature::SwitchMode() {
  if (mode == 1) {
    mode = 2;
    std::cout << "now display the tempature in Fahrenheit." << std::endl;
  } else if (mode == 2) {
    mode = 1;
    std::cout << "now display the tempature in Celsius." << std::endl;
  }
}