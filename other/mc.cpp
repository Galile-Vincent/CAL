#include<iostream>

class Matrix {
 private:
  int row;
  int column;
  int **mat;
 public:
  /* note: 這些function都只有宣告沒有實作 */
  void Read();
  void Transpose();
  void Shape();
  void Print();
};

int main() {
  Matrix m;
  m.Read();
  m.Shape();
  m.Print();
  m.Transpose();
  m.Shape();
  m.Print();
  return 0;
}
using namespace std;
void Matrix::Read() {
  cin >> row >> column;
  mat = new int*[row];
  for (int i = 0; i < row; i++) {
    mat[i] = new int[column];
    for (int j = 0; j < column; j++) {
      cin >> mat[i][j];
    }
  }
}

void Matrix::Shape() {
  cout << "This is a " << row << "-by-" << column << " matrix." << endl;
}

void Matrix::Print() {
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < column; j++) {
      cout << mat[i][j];
      if (j != column - 1) {
        cout << " ";
      }
    }
    cout << endl;
  }
}

void Matrix::Transpose() {
  int **temp = new int*[column];
  for (int i = 0; i < column; i++) {
    temp[i] = new int[row];
    for (int j = 0; j < row; j++) {
      temp[i][j] = mat[j][i];
    }
  }
  delete[] mat;
  mat = temp;
  int t = row;
  row = column;
  column = t;
}

