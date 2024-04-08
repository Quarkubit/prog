#include<iostream>
#include<array>
#include<format>

class Matrix {
private:
  std::array<std::array<double, 2>, 2> mtrx;
public:
  Matrix(double a = 0, double b = 0, double c = 0, double d = 0) : mtrx({{{a,b},{c,d}}}) {}
  Matrix operator*(double A) {
    Matrix mtrx2(*this);
    for (int i = 0; i < 2;++i) {
      mtrx2[i][0] *= A;
      mtrx2[i][1] *= A;
    }
    return mtrx2;
  }

  Matrix operator*(Matrix A) {
    Matrix mtrx2(*this);
    for (int i = 0; i < 2; ++i) {
      mtrx2[i][0] = mtrx[i][0] * A[0][0] + mtrx[i][1] * A[1][0];
      mtrx2[i][1] = mtrx[i][0] * A[0][1] + mtrx[i][1] * A[1][1];
    }
    return mtrx2;
  }

  std::array<double, 2>& operator[](size_t argv) {
    return mtrx[argv];
  }

  const std::array<double, 2>& operator[](size_t argv) const {
    return mtrx[argv];
  }

  friend std::ostream& operator<<(std::ostream& print, const Matrix& mtrx) {
    print << std::format("Your matrix is:\n[{},{}]\n[{},{}]", mtrx[0][0], mtrx[0][1], mtrx[1][0], mtrx[1][1]);
    return print;
    }
  
};

Matrix setCells(void) {
  double a = 0, b = 0, c = 0, d = 0;
  std::cout << "Enter your matrix: \n";
  std::cin >> a >> b >> c >> d;
  return Matrix(a, b, c, d);
}

int main() {
  Matrix B = setCells();
  Matrix C = setCells();
  std::cout << B * C;
  return 0;
}