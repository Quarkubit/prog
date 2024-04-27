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
class B1 : virtual public A1, virtual public A2
{
protected:
    int b1;
public:
    B1(int V1 = 0, int V2 = 0, int V3 = 0) : A1(V2), A2(V3)
    {
        b1 = V1;
        cout << "\nClass B1 constructor";
    }
    virtual void print() { cout << "\nVariable of B1 class"; }
    virtual void show() { cout << "\nb1 = " << b1 << ", a1 = " << a1 << ", a2 = " << a2; }
};
class B2 : virtual public A1, virtual public A2
{
protected:
    int b2;
public:
    B2(int V1 = 0, int V2 = 0, int V3 = 0) : A1(V2), A2(V3)
    {
        b2 = V1;
        cout << "\nClass B2 constructor";
    }
    virtual void print() { cout << "\nVariable of B2 class"; }
    virtual void show() { cout << "\nb2 = " << b2 << ", a1 = " << a1 << ", a2 = " << a2; }
};
class C1 : virtual public B1, virtual public B2
{
protected:
    int c1;
public:
    C1(int V1 = 0, int V2 = 0, int V3 = 0, int V4 = 0, int V5 = 0) : B1(V2,V4,V5), B2(V3, V4, V5)
    {
        c1 = V1;
        cout << "\nClass C1 constructor";
    }
    virtual void print() { cout << "\nVariable of C1 class"; }
    virtual void show() { cout << "\nc1 = " << c1 << ", b1 = " << b1 << ", b2 = " << b2 << ", a1 = " << a1 << ", a2 = " << a2;}
};
class C2 : virtual public B1, virtual public B2
{
protected:
    int c2;
public:
    C2(int V1 = 0, int V2 = 0, int V3 = 0, int V4 = 0, int V5 = 0) : B1(V2), B2(V3, V4, V5)
    {
        c2 = V1;
        cout << "\nClass C2 constructor";
    }
    virtual void print() { cout << "\nVariable of C2 class"; }
    virtual void show() { cout << "\nc2 = " << c2 << ", b1 = " << b1 << ", b2 = " << b2 << ", a1 = " << a1 << ", a2 = " << a2;}
};
int main(){
    A1 testA1 (1);
    A2 testA2 (1);
    B1 testB1 (1,2,3);
    B2 testB2 (1,2,3);
    C1 testC1(1, 2, 3, 4, 5);
    C2 testC2(1, 2, 3, 4, 5);
    
    A1 *ptr;
    A2 *ptr1;

    ptr = &testA1;
    ptr->print();
    ptr->show();

    ptr1 = &testA2;
    ptr1->print();
    ptr1->show();
    
    ptr = &testB1;
    ptr->print();
    ptr->show();

    ptr = &testB2;
    ptr->print();
    ptr->show();

    ptr = &testC1;
    ptr->show();
    ptr->print();

    ptr = &testC2;
    ptr->show();
    ptr->print();

    cout<<"\n";
    return 0;
}