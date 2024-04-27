#include <iostream>

using namespace std;

class A1
{
protected:
    int a1;

public:
    A1(int V1 = 0)
    {
        a1 = V1;
        cout << "\nClass A1 constructor";
    }
    virtual void print() { cout << "\nVariable of A1 class"; }
    virtual void show() { cout << "\na1 = " << a1; }
};

class A2
{
protected:
    int a2;

public:
    A2(int V1 = 0)
    {
        a2 = V1;
        cout << "\nClass A2 constructor";
    }
    virtual void print() { cout << "\nVariable of A2 class"; }
    virtual void show() { cout << "\na2 = " << a2; }
};

class A3
{
protected:
    int a3;

public:
    A3(int V1 = 0)
    {
        a3 = V1;
        cout << "\nClass A3 constructor";
    }
    virtual void print() { cout << "\nVariable of A3 class"; }
    virtual void show() { cout << "\na3 = " << a3; }
};

class B1 : virtual public A1, virtual public A3
{
protected:
    int b1;

public:
    B1(int V1 = 0, int V2 = 0, int V3 = 0) : A1(V2), A3(V3)
    {
        b1 = V1;
        cout << "\nClass B1 constructor";
    }
    virtual void print() { cout << "\nVariable of B1 class"; }
    virtual void show() { cout << "\nb1 = " << b1 << ", a1 = " << a1 << ", a3 = " << a3; }
};

class B2 : virtual public A2, virtual public A3
{
protected:
    int b2;

public:
    B2(int V1 = 0, int V2 = 0, int V3 = 0) : A2(V2), A3(V3)
    {
        b2 = V1;
        cout << "\nClass B2 constructor";
    }
    virtual void print() { cout << "\nVariable of B2 class"; }
    virtual void show() { cout << "\nb2 = " << b2 << ", a2 = " << a2 << ", a3 = " << a3; }
};

class C1 : virtual public B1, virtual public B2
{
protected:
    int c1;

public:
    C1(int V1 = 0, int V2 = 0, int V3 = 0, int V4 = 0, int V5 = 0, int V6 = 0) : B1(V2, V4), B2(V3, V5, V6)
    {
        c1 = V1;
        cout << "\nClass C1 constructor";
    }
    virtual void print() { cout << "\nVariable of C1 class"; }
    virtual void show() { cout << "\nc1 = " << c1 << ", b1 = " << b1 << ", b2 = " << b2 << ", a1 = " << a1 << ", a2 = " << a2 << ", a3 = " << a3; }
};

class C2 : virtual public B1, virtual public B2
{
protected:
    int c2;

public:
    C2(int V1 = 0, int V2 = 0, int V3 = 0, int V4 = 0, int V5 = 0, int V6 = 0) : B1(V2, V4, V6), B2(V3, V5)
    {
        c2 = V1;
        cout << "\nClass C2 constructor";
    }
    virtual void print() { cout << "\nVariable of C2 class"; }
    virtual void show() { cout << "\nc2 = " << c2 << ", b1 = " << b1 << ", b2 = " << b2 << ", a1 = " << a1 << ", a2 = " << a2 << ", a3 = " << a3; }
};

class C3 : virtual public B1, virtual public B2
{
protected:
    int c3;

public:
    C3(int V1 = 0, int V2 = 0, int V3 = 0, int V4 = 0, int V5 = 0, int V6 = 0) : B1(V2, V4, V6), B2(V3, V5, V6)
    {
        c3 = V1;
        cout << "\nClass C3 constructor";
    }
    virtual void print() { cout << "\nVariable of C3 class"; }
    virtual void show() { cout << "\nc3 = " << c3 << ", b1 = " << b1 << ", b2 = " << b2 << ", a1 = " << a1 << ", a2 = " << a2 << ", a3 = " << a3; }
};

int main()
{
    A1 testA1(1);
    A2 testA2(1);
    A3 testA3(1);
    B1 testB1(1, 2, 3);
    B2 testB2(1, 2, 3);
    C1 testC1(1, 2, 3, 4, 5, 6);
    C2 testC2(1, 2, 3, 4, 5, 6);
    C3 testC3(1, 2, 3, 4, 5, 6);

    A1 *ptr;
    A2 *ptr1;
    A3 *ptr2;

    ptr = &testA1;
    ptr->print();
    ptr->show();

    ptr1 = &testA2;
    ptr1->print();
    ptr1->show();

    ptr2 = &testA3;
    ptr2->print();
    ptr2->show();

    ptr = &testB1;
    ptr->print();
    ptr->show();

    ptr1 = &testB2;
    ptr1->print();
    ptr1->show();

    ptr = &testC1;
    ptr->show();
    ptr->print();

    ptr = &testC2;
    ptr->show();
    ptr->print();

    ptr = &testC3;
    ptr->show();
    ptr->print();

    cout << "\n";
    return 0;
}
