#include <iostream>
#include <stdlib.h>

class Matrix
{
private:
    // matrix cells
    double m1, m2, m3, m4;

public:
    // constructor
    Matrix(double Matrix1 = 0, double Matrix2 = 0, double Matrix3 = 0, double Matrix4 = 0)
    {
        m1 = Matrix1, m2 = Matrix2, m3 = Matrix3, m4 = Matrix4;
    }
    // Matrix multiply matrix
    Matrix operator*(Matrix D)
    {
        Matrix Res;
        Res.m1 = m1 * D.m1 + m2 * D.m3;
        Res.m3 = m3 * D.m1 + m4 * D.m3;
        Res.m2 = m1 * D.m2 + m2 * D.m4;
        Res.m4 = m3 * D.m2 + m4 * D.m4;
        return Res;
    }
    // Matrix multiply number
    Matrix operator*(double C)
    {
        Matrix Res;
        Res.m1 = m1 * C;
        Res.m2 = m2 * C;
        Res.m3 = m3 * C;
        Res.m4 = m4 * C;
        return Res;
    }
    // Print matrix function
    void print()
    {
        std::cout << "[" << m1 << "," << m2 << "]" << std::endl
                  << "[" << m3 << "," << m4 << "]\n"
                  << std::endl;
    }
};

Matrix getNumber(void)
{
    // Initializing elements of matrix
    double a, b, c, d;
    std::cout << "Enter your matrix: \n";
    std::cin >> a >> b >> c >> d;
    system("cls");
    return Matrix(a, b, c, d);
}

Matrix setFunctional()
{
    double num;
    short a, b;
    Matrix B, C;
    std::cout << "What do you want?\n0.Multiplying matrix (default).\n1.Multiply matrix by num.\n";
    std::cin >> a;
    system("cls");
    Matrix A(getNumber());
    switch (a)
    {
    default:
    {
        std::cout << "Add another one.\n";
        Matrix B(getNumber());
        system("cls");
        std::cout << "Choose correct operaion.\n0.Matrix 1 * Matrix 2 (default).\n1.Matrix 2 * Matrix 1.\n";
        std::cin >> b;
        system("cls");
        switch (b)
        {
        default:
        {
            return C = A * B;
            break;
        }
        case 1:
        {
            return C = B * A;
            break;
        }
        }
        return C;
    }
    case 1:
    {
        std::cout << "Enter your number.\n";
        std::cin >> num;
        system("cls");
        return C = A * num;
        break;
    }
    }
}

int main(void)
{
    Matrix C = (setFunctional());
    system("cls");
    std::cout << "Your answer is: \n";
    C.print();
    char c; std::cin >> c;
    return 0;
}
