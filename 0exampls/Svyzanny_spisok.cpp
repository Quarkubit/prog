using namespace std;

#include <iostream>

class my_class
{
public:
    int data;
    my_class(int v = 0)
    {
        data = v;
        cout << "\nmy_class constructor";
    }
    my_class(const my_class &m)
    {
        data = m.data;
        cout << "\nmy_class copy constructor";
    }

    ~my_class() { cout << "\nmy_class destructor"; }

    friend ostream &operator<<(ostream &s, my_class &value);
};

ostream &operator<<(ostream &s, my_class &value)
{
    s << value.data;
    return s;
}

template <class T>
class Element
{
    // protected:
public:
    // ����������� � protected
    Element *next;
    Element *prev;
    T info;

    Element(T data)
    {
        next = prev = NULL;
        info = data;
    }

    Element(Element *Next, Element *Prev, T data)
    {
        next = Next;
        prev = Prev;
        info = data;
    }

    Element(const Element &el)
    {
        next = el.next;
        prev = el.prev;
        info = el.info;
    }

    template <class T1>
    friend ostream &operator<<(ostream &s, Element<T1> &el);
};

template <class T1>
ostream &operator<<(ostream &s, Element<T1> &el)
{
    s << el.info;
    return s;
}

template <class T>
class LinkedList
{
    // protected:
public:
    // ����������� � protected
    Element<T> *head;
    Element<T> *tail;

    int count;

    LinkedList()
    {
        head = tail = NULL;
        count = 0;
    }

    // ������� ������/��������� ������� � ������� ��������� ��������
    virtual Element<T> *pop() = 0;
    // �������� ������� � ������
    virtual Element<T> *push(T value) = 0;
    // �������� ������/��������� ������� ������
    // virtual Element<T>* front(T value) = 0;
    // virtual Element<T>* back(T value) = 0;

    // ������ �� �������
    virtual Element<T> &operator[](int index) = 0;

    template <class T1>
    friend ostream &operator<<(ostream &s, LinkedList<T1> &list);

    // ���������� ����������
    virtual ~LinkedList()
    {
        if (head == NULL)
            return;
        count = 0;
        for (Element<T> *Current = head->next, *Previous = head; Current != NULL; delete Previous, Previous = Current, Current = Current->next)
            ;
        delete tail;
    }
};

template <class T>
ostream &operator<<(ostream &s, LinkedList<T> &list)
{
    for (Element<T> *Current = list.head; Current != NULL; s << *Current << "; ", Current = Current->next)
        ; // Current->info
    return s;
}

template <class T>
class Stack : virtual public LinkedList<T>
{
public:
    Stack() : LinkedList<T>() {}
    Element<T> &operator[](int index)
    {
        Element<T> *Current = LinkedList<T>::head;
        for (int i = 0; i < index && Current != NULL; Current = Current->next, i++)
            ;
        return *Current; // ������� ����������, ���� Current==NULL
    }

    Element<T> *push(T value)
    {
        Element<T> *newElem = new Element<T>(value);
        if (LinkedList<T>::tail != NULL)
            LinkedList<T>::tail->next = newElem;
        else
            LinkedList<T>::head = LinkedList<T>::tail = newElem;
        LinkedList<T>::tail = newElem; // tail = newElem
        LinkedList<T>::count++;
        return LinkedList<T>::tail;
    }

    Element<T> *pop() // T pop()
    {
        if (LinkedList<T>::tail == NULL)
            return NULL; // ������ ������

        Element<T> *Res = LinkedList<T>::tail;
        LinkedList<T>::count--;

        if (LinkedList<T>::head == LinkedList<T>::tail) // ���� �������
        {
            LinkedList<T>::head = LinkedList<T>::tail = NULL;
            return Res;
        }

        Element<T> *Current = LinkedList<T>::head;
        for (; Current->next != LinkedList<T>::tail; Current = Current->next)
            ; // Current->next->next!=NULL
        Current->next = NULL;
        LinkedList<T>::tail = Current;
        return Res;
    }

    Element<T> *insert(T value, Element<T> *previous = NULL)
    {
        if (previous == NULL || previous == LinkedList<T>::tail)
            return push(value);
        Element<T> *newElem = new Element<T>(value);
        newElem->next = previous->next;
        previous->next = newElem;
        LinkedList<T>::count++;
        return previous->next;
    }
};

/*template<class T>
class StackQueue: virtual protected Stack<T>, virtual protected Queue<T>
{
public:
    StackQueue(): Stack<T>(), Queue<T>() {}
    virtual Element<T>* push_back() {return Stack<T>::push();}
    virtual Element<T>* push_front() {...}
    virtual Element<T>* pop_back() {return Stack<T>::pop();}
    virtual Element<T>* pop_front() {return Queue<T>::pop();}
};*/

template <class T>
class DoubleLinkedStack : virtual public Stack<T>
{
public:
    DoubleLinkedStack() : Stack<T>() {}

    Element<T> *push(T value)
    {
        Element<T> *old_tail = LinkedList<T>::tail;
        Stack<T>::push(value);
        LinkedList<T>::tail->prev = old_tail;
        return LinkedList<T>::tail;
    }

    Element<T> *insert(T value, Element<T> *previous = NULL)
    {
        if (previous == NULL || previous == LinkedList<T>::tail)
            return push(value);
        Stack<T>::insert(value, previous);
        previous->next->prev = previous;
        previous->next->next->prev = previous->next;
        return previous->next;
    }

    Element<T> *pop()
    {
        if (LinkedList<T>::tail == NULL || LinkedList<T>::tail == LinkedList<T>::head)
            return Stack<T>::pop();

        Element<T> *new_tail = LinkedList<T>::tail->prev;
        Element<T> *res = LinkedList<T>::tail;
        new_tail->next = NULL;
        LinkedList<T>::tail->prev = NULL;
        LinkedList<T>::count--;
        LinkedList<T>::tail = new_tail;
        return res;
    }
    template <class T1>
    friend ostream &operator<<(ostream &s, DoubleLinkedStack<T1> &list);
};

template <class T>
ostream &operator<<(ostream &s, DoubleLinkedStack<T> &list)
{
    for (Element<T> *Current = list.head; Current != NULL; s << *Current << "; ", Current = Current->next); // Current->info
    return s;
}

int main()
{
    if (true)
    {
        DoubleLinkedStack<int> S;
        for (int i = 0; i < 10; i++)
            S.push(i);
        S.insert(100, &S[4]);
        Element<int> *res = S.pop();
        cout << *res << "\n"
             << S;
    }
    cout << "\n";
}