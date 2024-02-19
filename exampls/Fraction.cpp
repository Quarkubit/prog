#include <iostream>
using namespace std;
class Fraction
{
private:
    // поля: числитель и знаменатель
    int denominator;
    int numerator;

public:
    // Daddy конструктор
    Fraction(int n = 0, int d = 1)
    {
        numerator = n;
        denominator = d;
    }

    void print()
    {
        std::cout << numerator << "/" << denominator;
    }

    Fraction operator*(Fraction F)
    {
        Fraction res;
        res.numerator = numerator * F.numerator;
        res.denominator = denominator * F.denominator;
        return res;
    }

    Fraction operator*(int x)
    {
        Fraction res;
        res.numerator = numerator * x;
        res.denominator = denominator;
        return res;
    }

    Fraction operator/(Fraction F)
    {
        Fraction res;
        res.numerator = numerator * F.denominator;
        res.denominator = denominator * F.numerator;
        return res;
    }

    Fraction operator/(int x)
    {
        Fraction res;
        res.numerator = numerator;
        res.denominator = denominator * x;
        return res;
    }

    bool operator==(Fraction F)
    {
        return numerator * F.denominator == denominator * F.numerator;
    }

    bool operator!=(Fraction F)
    {
        return numerator * F.denominator != denominator * F.numerator;
    }

    // Алгоритм Евклида
    int gcd(int a, int b)
    {
        if (b == 0)
            return a;
        return gcd(b, a % b);
    }

    // бинарные +, -, <, >
    Fraction operator+(Fraction F)
    {
        Fraction res;
        res.numerator = numerator * F.denominator + F.numerator * denominator;
        res.denominator = denominator * F.denominator;
        return res;
    }

    Fraction operator+(int F)
    {
        Fraction res;
        res.numerator = numerator + F * denominator;
        res.denominator = denominator;
        return res;
    }

    Fraction operator-(Fraction F)
    {
        Fraction res;
        res.numerator = numerator * F.denominator - F.numerator * denominator;
        res.denominator = denominator * F.denominator;
        return res;
    }
    //

    Fraction operator-()
    {
        Fraction res;
        res.numerator = -numerator;
        res.denominator = denominator;
        return res;
    }

    friend Fraction operator*(int a, Fraction F);
};

Fraction operator*(int a, Fraction F)
{
    Fraction res;
    res.numerator = a * F.numerator;
    res.denominator = F.denominator;
    return res;
}

int main()
{
    Fraction F(1, 2);
    Fraction G(3, 4);
    Fraction H = F / G * 2;
    Fraction K(2, 2);
    Fraction J = K / 2;
    J.print();
    Fraction D = 2 * K;
    D.print();
    cout << "\nF*G = ";
    H.print();
    cout << "\nF==F " << (F == F);
    cout << "\nF!=F " << (F != F);
    cout << "\n-F = ";
    (-F).print();

    return 0;
}
