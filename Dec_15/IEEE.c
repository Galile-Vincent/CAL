/* 
 hidden code 已包含需要的data structures 與 
 FractionStrAnalysis(), DecimalToBinary(),
 FractionToBinary(), FindMantissaExponent(), DecimalToExcess127() 的實作內容 
*/
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef char Str24[24];  // 所使用的字串陣列的型別，用來存mantissa
typedef char Str9[9];  // 所使用的字串陣列的型別，用來存exponent
typedef char Str40[40];  // 所使用的字串陣列的型別，依照題意至少需33個char(包括結束位元) 

typedef struct floatInfo {  // 沒有符合命名規範...但算了，你自己寫的時候要留意
  bool non_negative;
  int decimal;
  int int_of_fraction;
  int num_digits;
} FloatInfo;
/** 
 * 把傳入的字串做拆出以下資訊：是正是負(存在'non_negative')，整數位(存在'decimal')，
 * 小數位(存在'int_of_fraction')，以及小數的位數(存在'num_digits')。
 * 以-35.0423為例，
 * non_negative: false; decimal: 35; int_of_fraction: 423; num_digits: 4;
 * @param float_str 一個代表浮點數的字串(如“35.0423”或“27”)
 * @return a struct contains: non_negative, decimal, int_of_fraction, num_digits 
 */
FloatInfo FractionStrAnalysis(Str40 float_str);

/** 
 * 把一個輸入的整數轉成二進位表示法字串
 * @param input_num 要轉的(非負)整數(例：35)
 * @param output_num 把轉完的二進位字串存在這裡。例："100011"
 */
void DecimalToBinary(int input_num, Str40 output_num);

/** 
 * 把一個浮點數(例：35.0423)的小數部位 (0.0423) 轉成二進位表示法字串
 * @param input_num 是小數部位之中的整數(以0.0423而言是423)
 * @param num_of_input_digits 是小數點之後的有效位數 (以0.0423而言是4)
 * @param output_num 把轉完的字串存在這裡。小數部位的二進位表示法字串(亦即(例子中的)0.0423的二進位表示法字串)
 */
void FractionToBinary(int input_num, int num_of_input_digits, Str40 output_num);

/**
 * 把一個浮點數的二進位表示法拿來予以正規化，計算出正規化後的mantissa(以字串表示之)與exponent(以整數表示之)。 
 * @param input_decimal 原浮點數(例：35.0423)的整數部位(例：35)的二進位表示法字串
 * @param input_fraction 原浮點數(例：35.0423)的小數部位(例：0.0423)的二進位表示法字串
 * @param mantissa 把原浮點數的二進位表示法拿來予以正規化之後、所得到的mantissa字串
                                  mantissa最長只有23個字元(最後是結束字元)
 * @param return exponent，此值是把原浮點數的二進位表示法拿來予以正規化之後
 * 所得到的指數的值(這是個整數)
 */
int FindMantissaExponent(Str40 input_decimal, Str40 input_fraction, Str24 mantissa);

/** 
 *把傳入的整數轉成以Excess_127表示法表示的字串(這是個有8個bit的二進位表示法字串)
 * @param exponent 傳入的指數值(例：-120)
 * @param excess127 exponent的excess_127表示法字串(例：先由-120得7，然後由7得"00000111")
 */
void DecimalToExcess127(int exponent, Str9 excess127);

int main() {

  Str40 input_string = "";  
  bool is_positive = true;     // true表示非負數 (true means non-negative)
  Str24 binary_mantissa = "";  // 計算出的 mantissa 
  Str9 binary_excess127 = "";  // excess127值的二進位表示法字串

  scanf("%s", input_string);  // 寫%39s比較安全

  // TODO: 分析輸入的float字串，須找出 sign, exponent, mantissa 三部分
  // step 1. 將整數與小數拆開
  FloatInfo info;
  info = FractionStrAnalysis(input_string);
  // step 2. 整數部分轉成二進位
  Str40 decimal_binary = "";
  DecimalToBinary(info.decimal, decimal_binary);
  // step 3. 小數部分轉成二進位
  Str40 fractin_binary = "";
  FractionToBinary(info.int_of_fraction, info.num_digits, fractin_binary);
  // step 4. 將轉換成二進位的整數與小數組合在一起，然後做正規化
  int exponent = FindMantissaExponent(decimal_binary, fractin_binary, binary_mantissa);
  // step 5. 將exponent改為用Excess_127表示法表示
  DecimalToExcess127(exponent, binary_excess127);
  // 以下判斷signbit應該要是0還是1，然後按照IEEE754表示法顯示
  // 各個部分間使用空格隔開
  // 實務上不隔開，這邊只是為了讓你更清楚的知道sign exponent mantissa 各自的內容
  if ( is_positive ) 
    printf("0 %s %s", binary_excess127 ,  binary_mantissa);
  else  // 負數 
    printf("1 %s %s", binary_excess127 ,  binary_mantissa);

  return 0;
} 