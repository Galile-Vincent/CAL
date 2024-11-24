/* hidden code */
#include<stdio.h>
#include<stdbool.h>
typedef char Str50[50];  // 新型別；一個可存放50字元的陣列

struct Customer {
  int id;  // 客戶編號
  Str50 name;  // 名字, 長度50的字元陣列
  int balance;  // 存款
};

typedef Customer CustomerArray[200]; // 新型別：一個可存放200個Customer的陣列

/* hidden code */

/**
 * 讀入客戶資料並存起來
 * @param cus_arr 要存入客戶資料的陣列
 * @return 讀入的客戶資料數
 */
#include <string.h>
int Read(CustomerArray cus_arr) {
  int count = 0;
  int id = 0;
  char name[50];
  int balance = 0;
  while (1) {
    scanf("%d", &id);
    if (id == -1) break;
    scanf("%49s", name);
    scanf("%d", &balance);
    int repeat = 0;
    for (int i = 0; i <= count; i++) {
      if (cus_arr[i].id == id) {
        repeat = 1;
        break;
      }
    }

    if (!repeat) {
      cus_arr[count].id = id;
      strcpy(cus_arr[count].name, name);
      cus_arr[count].balance = balance;
      count++;
    }
    if (count >= 200) break;
  }
  return count;
}

/**
 * 印出錯誤紀錄
 * @param err_num 錯誤碼(應該只有0,1,2三種)
 * @param id 客戶id
 * @param money 客戶要提款的金額
 * @param cus_arr 儲存客戶資料的陣列
 * @param num_of_customer 客戶的數量
 */
/*
1. 如果err_num是0，那就啥也不做。
2. 如果err_num是1，那就印出"No such account: {客戶id}"
3. 如果err_num是2，那就要找出「這個id的客戶資料」並計算「餘額差多少」，
然後印出"{客戶名稱}'s balance is {金額} dollars short."
(note: 這邊的{}只是為了表達內部的字串是一個變數，並不是要印出{})
*/
#include <string.h>
void ErrorLog(int err_num, int id, int money,
    CustomerArray cus_arr, int num_of_customer) {
  if (err_num == 1) {
    printf("No such account: %d\n", id);
  } else if (err_num == 2) {
    int balance = 0;
    char name[50];
    for (int i = 0; i < num_of_customer; i++) {
      if (cus_arr[i].id == id) {
        balance = cus_arr[i].balance;
        strcpy(name, cus_arr[i].name);
      }
    }
    int s_money = money - balance;
    printf("%s's balance is %d dollars short.\n", name, s_money);
  }
}

/**
 * 印出指定數量的客戶資訊
 * @param cus_arr 儲存客戶資料的陣列
 * @param num_of_customer 客戶的數量
 */
void Print(CustomerArray cus_arr, int num_of_customer) {
  for (int i = 0; i < num_of_customer; i++) {
    printf("%d\n", cus_arr[i].id);
    printf("%s\n", cus_arr[i].name);
    printf("%d\n", cus_arr[i].balance);
  }
}

/**
 * 根據輸入的資訊，從客戶資料中扣款
 * @param id 客戶id
 * @param money 提款金額
 * @param cus_arr 儲存客戶資料的陣列
 * @param num_of_customer 客戶的數量
 * @return 錯誤碼(0: 正常交易, 1:查無此人, 2:餘額不足)
 */
/*
1. 宣告一個變數err_num來儲存錯誤碼
2. 從cus_arr中找出是否有此id。如果沒有的話，把err_num設成1
3. 如果有找到對應的id，則檢查戶頭餘額(也就是balance)是否足夠。足夠的話就扣款，然後把err_num設成0
4. 如果不夠扣，把err_num設成2，並且無多餘動作
回傳err_num
*/
int Process(int id, int money, CustomerArray cus_arr, int num_of_customer) {
  int err_num = 0;
  int place = 0; // Where the id is
  // Check if id exist
  bool exist = false;
  for (int i = 0; i < num_of_customer; i++) {
    if (cus_arr[i].id == id) {
        exist = true;
        place = i;
        break;
    }
  }
  if (!exist) return 1;

  // Check balance -> enough return 0 and calculate the balance
  if (cus_arr[place].balance - money < 0) {
    return 2;
  }
  cus_arr[place].balance = cus_arr[place].balance - money;
  return err_num;
}

int main() {

  CustomerArray customer;  // 所有顧客的資料
  int num_of_customer;  // 有多少顧客

  // step 1: 讀入所有輸入的客戶資料
  num_of_customer = Read(customer);
  // step 2: 處理扣款
  int id = 0;
  int money = 0;
  while (1) {
    scanf("%d", id);
    if (id == -1) break; // Break while get the -1
    scanf("%d", &money);

    int error = Process(id, money, customer, num_of_customer); // return 錯誤碼(0: 正常交易, 1:查無此人, 2:餘額不足)

    ErrorLog(error, id, money, customer, num_of_customer); // 根據給予的錯誤碼以及客戶資訊，印出錯誤紀錄(只處理一筆資料)
  }
  // step 3: 處理錯誤資訊
  // step 2 & 3 一次只會處理一筆提款資料

  // step 4: 印出客戶資料
  print(customer, num_of_customer);
  return 0;
}