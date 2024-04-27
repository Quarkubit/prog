#include <iostream>

using namespace std;

class BaseString
{
protected:
    char *p;
    int len;
    int capacity;

public:
    BaseString(char *ptr)
    {
        cout << "\nBase Constructor 1\n";
        int i = 0;
        char *p1 = ptr;
        while (*p1 != '\0')
        {
            *p1++;
            i++;
        }
        len = i;
        p = new char[len + 1];
        char *p2 = p;
        i = 0;
        p1 = ptr;
        while ((*p2++ = *p1++) != '\0')
            ;

        *p2 = '\0';
        capacity = len + 1;
    }
    BaseString(int Capacity = 256)
    {
        cout << "\nBase Constructor 0\n";
        capacity = Capacity;
        p = new char[capacity];
        len = 0;
    }
    ~BaseString()
    {
        cout << "\nBase Destructor\n";
        if (p != NULL)
            delete[] p;
        len = 0;
    }
    int Length() { return len; }
    int Capacity() { return capacity; }
    // char* get() {return p;}
    char &operator[](int i) { return p[i]; }
    BaseString &operator=(BaseString &s)
    {
        cout << "\nBase Operator = \n";
        len = s.Length();
        p = new char[s.capacity];
        capacity = s.capacity;
        for (int i = 0; i < s.Length(); i++)
        {
            p[i] = s[i];
        }
        // strcpy(p, s.get());
        p[len - 1] = '\0';
        return *this;
    }
    BaseString(BaseString &s)
    {
        cout << "\nBase Copy Constructor\n";
        len = s.Length();
        p = new char[s.capacity];
        capacity = s.capacity;
        for (int i = 0; i < s.Length() - 1; i++)
        {
            p[i] = s[i];
        }
        p[len - 1] = '\0';
    }
    virtual void print()
    {
        int i = 0;
        while (p[i] != '\0')
        {
            cout << p[i];
            i++;
        }
    }
};

int main()
{
    // if (true)
    // {
    //     String s("Topot");
    //     // s.print();
    //     // BaseString b("test");
    //     // BaseString* ptr = &b;
    //     // f(ptr);

    //     BaseString *ptr = &s;
    //     f(ptr);
    //     /*String s1 = s;
    //     s1.print();
    //     String s2; s2 = s1;
    //     s2.print();*/
    // }

    cout << "\n";
    return 0;
}