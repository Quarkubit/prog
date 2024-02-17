#include <iostream>
#include <cmath>

using namespace std;

class Complex
{
private:
    // Действительная и мнимая части
    double real, image;

public:
    // Конструкторы
    /*Complex()
    {
        real = 0;
        image = 0;
    }*/
    Complex(double r = 0, double im = 0)
    {
        real = r;
        image = im;
    }
    /*Complex(double r)
    {
        real = r;
        image = 0;
    }*/

    // Получатели
    double getReal() { return real; }
    double getImage() { return image; }

    // Установщики
    Complex setReal(double x)
    {
        real = x;
        return *this;
    }
    Complex setImage(double y)
    {
        image = y;
        return *this;
    }
    Complex setComplex(double r, double im)
    {
        real = r;
        image = im;
        return *this;
    }

    // Вывод числа в формате "x + y*i"
    void print()
    {
        if (image == 0 && real == 0)
        {
            cout << "0\n";
            return;
        }
        if (real != 0)
        {
            // !?!?!? уточнить на правктике
            cout << ' ' << real; // в VS code не выводятся отрицательные числа, если перед этим не добавить любой другой символ
        }
        if (image > 0)
        {
            cout << " + ";
        }
        if (image < 0)
        {
            cout << " - ";
        }
        if (image != 0)
        {
            cout << abs(image) << "i\n" << endl;
            return;
        }
        cout << '\n';
    }

    // Модуль комплексного числа
    double Module() { return sqrt(real * real + image * image); }

    // Операторы
    Complex add(Complex z) // сложение методом
    {
        Complex res;
        res.real = real + z.real;
        res.image = image + z.image;
        return res;
    }

    Complex add(double value)
    {
        Complex res;
        res.real = real + value;
        res.image = image;
        return res;
    }

    Complex operator+(Complex z) // сложение знаком
    {
        Complex res;
        res.real = real + z.real;
        res.image = image + z.image;
        return res;
    }

    Complex operator+(double value)
    {
        Complex res;
        res.real = real + value;
        res.image = image;
        return res;
    }

    Complex operator+() // комплексное сопряжение унарным плюсом
    {
        Complex res;
        res.real = real;
        res.image = -image;
        return res;
    }

    Complex operator*(double z) // умножение комплексного на
    {
        Complex res;
        res.real = real * z;
        res.image = image * z;
        return res;
    }

    Complex operator*(Complex z)
    {
        Complex res;
        res.real = real * z.real - image * z.image;
        res.image = real * z.image + image * z.real;
        return res;
    }

    friend Complex operator*(double x,Complex z)
    {
        Complex res;
        res.real = z.real * x;
        res.image = z.image * x;
        return res;
    }

    bool operator==(Complex z) // равенство
    {
        return (real == z.real && image == z.image);
    }

    Complex operator=(Complex z) // присваивание
    {
        real = z.real;
        image = z.image;
        return *this;
    }
};

int main()
{
    Complex H;    // test1
    H.setComplex(1, 1).print();
    H.setComplex(2, -2).print();
    H.setComplex(-3, 3).print();
    H.setComplex(-4, -4).print();

    Complex y, x(2);    // test2
    y.print();
    x.print();

    Complex A, z(1, 2);    // test3
    A = z * 8;
    A.print();
    A = 8 * z;
    A.print();
    return 0;
}