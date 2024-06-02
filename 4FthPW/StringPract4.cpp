#include <iostream>
#include <cstring>

using namespace std;

class BaseString
{
protected:
    char *p;
    int len;
    int capacity;

public:
    BaseString(const char *ptr)
    {
        // cout << "\nBase Constructor 1\n";
        len = strlen(ptr) + 1; // почему выдёт ошибку на strlen?
        capacity = 256;
        p = new char[capacity];
        for (int i = 0; i < len; i++)
        {
            p[i] = ptr[i];
        }
        p[len] = '\0';
    }

    BaseString(int Capacity = 256)
    {
        // cout << "\nBase Constructor 0\n";
        capacity = Capacity;
        p = new char[capacity];
        len = 0;
    }

    ~BaseString()
    {
        // cout << "\nBase Destructor\n";
        if (p != NULL)
            delete[] p;
        len = 0;
    }

    int Length() { return len; }
    int Capacity() { return capacity; }
    char *get() { return p; }
    char &operator[](int i) { return p[i]; }

    /*BaseString &operator=(BaseString &s)
    {
        // cout << "\nBase Operator = \n";
        if (capacity < s.capacity)
        {
            delete[] p;
            p = new char[s.capacity];
            capacity = s.capacity;
        }
        len = s.len;
        p = new char[s.capacity];
        capacity = s.capacity;
        for (int i = 0; i < s.Length(); i++)
        {
            p[i] = s[i];
        }
        p[len - 1] = '\0';
        return *this;
    }*/

    BaseString(BaseString &s)
    {
        // cout << "\nBase Copy Constructor\n";
        len = s.Length();
        p = new char[s.capacity];
        capacity = s.capacity;
        char *p1 = p;
        char *p2 = s.p;
        while (*p1++ = *p2++);
        *p1 = '\0';
    }

    BaseString &operator=(const BaseString &s)
    {
        if (this != &s)
        {
            if (capacity < s.capacity)
            {
                delete[] p;
                p = new char[s.capacity];
                capacity = s.capacity;
            }
            len = s.len;
            for (int i = 0; i < len; i++)
            {
                p[i] = s.p[i];
            }
            p[len] = '\0';
        }
        return *this;
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

class String : virtual public BaseString
{
public:
    String(char *ptr) : BaseString(ptr) {}

    String(int Capacity = 256) : BaseString(Capacity) {}

    ~String() {}

    String &operator=(const String &s)
    {
        BaseString::operator=(s);
        return *this;
    }

    String(String &s) : BaseString(s) {}

    int LastIndexOf(const char *substr) const
    {
        int substrLen = strlen(substr);
        int strLen = len;
        int lastIndex = -1;

        for (int i = strLen - substrLen; i >= 0; --i)
        {
            const char *strPtr = p + i;
            const char *substrPtr = substr;

            while (*substrPtr != '\0' && *strPtr == *substrPtr)
            {
                ++strPtr;
                ++substrPtr;
            }

            if (*substrPtr == '\0')
            {
                lastIndex = i;
                break;
            }
        }

        return lastIndex;
    }
};

int main()
{
    // Class BaseString
    BaseString a1("Hello, World!");
    BaseString a2(a1);
    BaseString a3 = a2;
    cout << a1.get() << "\n"
         << a2.get() << "\n"
         << a3.get() << "\n"
         << endl;

    // Class String
    String s1("Hello, World!");
    String s2("World");
    int index = s1.LastIndexOf(s2.get());
    cout << "Last index of \"" << s2.get() << "\": " << index << endl;

    String s3(s1);
    cout << "\ns3 copy constructor: ";
    s3.print();

    String s4;
    s4 = s1;
    cout << "\ns4 operator=: ";
    s4.print();

    cout << "\n";
    return 0;
}

// operator= дублируется
// искать индекс методом указателей