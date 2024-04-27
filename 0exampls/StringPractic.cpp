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

        p1 = ptr;
        while (*p2++ = *p1++)
            ;

        *p2 = '\0';
        capacity = len + 1;
        // ����������� ptr => p?
    }

    BaseString(const char *ptr)
    {
        cout << "\nBase const char* Constructor 1\n";

        int i = 0;
        while (ptr[i] != '\0')
            i++;

        len = i;
        capacity = len + 1;
        p = new char[capacity];
        for (i = 0; i < len; i++)
            p[i] = ptr[i];

        p[len] = '\0';
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
        if (capacity < s.capacity)
        {
            delete[] p;
            p = new char[s.capacity];
            capacity = s.capacity;
        }
        len = s.len;
        char *p1 = p;
        char *p2 = s.p;
        while (*p1++ = *p2++)
            ;
        *p1 = '\0';

        return *this;
    }
    BaseString(BaseString &s)
    {
        cout << "\nBase Copy Constructor\n";
        // ptr=>s.p
        capacity = s.capacity;
        len = s.len;

        p = new char[capacity];
        char *p1 = p;
        char *p2 = s.p;
        while (*p1++ = *p2++)
            ;
        *p1 = '\0';
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

    virtual int IndexOf(char c)
    {
        cout << "\nIndexOf from BaseString";
        int i = 0;
        for (; i < len; i++)
        {
            if (p[i] == c)
                return i;
        }
        return -1;
    }

    virtual bool isPalindrome()
    {
        // ���������?
        cout << "\nVersion of Palindrome from Base";

        char *p1 = p;
        char *p2 = &p[len - 1];
        while (p1 < p2)
        {
            if (*p1++ != *p2--)
                return false;
        }
        return true;
    }

    virtual void test() = 0; // ���
};

class String : public BaseString
{
protected:
    char tolower(char c)
    {
        return (c >= 'A' && c <= 'Z' ? 'a' + c - 'A' : c);
    }

public:
    String(char *ptr) : BaseString(ptr) {}
    String(const char *ptr) : BaseString(ptr) {}
    String(int Capacity = 256) : BaseString(Capacity) {}

    int IndexOf(char c)
    {
        cout << "\nIndexOf from String";
        int i = len - 1;
        for (; i >= 0; i--)
            if (p[i] == c)
                return i;
        return -1;
    }

    bool isPalindrome()
    {
        // ���������?
        cout << "\nVersion of Palindrome from Derived";

        char *p1 = p;
        char *p2 = &p[len - 1];
        while (p1 < p2)
        {
            if (tolower(*p1++) != tolower(*p2--))
                return false;
        }
        return true;
    }

    void test() { cout << "\ntest: " << isPalindrome(); }
};

void f(BaseString *ptr)
{
    bool b = ptr->isPalindrome();
    int f = ptr->IndexOf('t');
    cout << "\n"
         << b << " " << f;
}

int main()
{
    if (true)
    {
        String s("Topot");
        // s.print();
        // BaseString b("test");
        // BaseString* ptr = &b;
        // f(ptr);

        BaseString *ptr = &s;
        f(ptr);
        /*String s1 = s;
        s1.print();
        String s2; s2 = s1;
        s2.print();*/
    }
    char c;
    cin >> c;
    return 0;
}