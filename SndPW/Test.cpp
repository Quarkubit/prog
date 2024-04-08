#include <cmath>
#include <iostream>

using namespace std;

class MyArrayParent
{
protected:
    int capacity;
    int count;
    // массив
    double *ptr;

public:
    // конструкторы и деструктор
    MyArrayParent(int Dimension = 100)
    {
        cout << "\nMyArrayParent constructor";
        // выделить память под массив ptr, заполнить поля
        ptr = new double[Dimension];
        capacity = Dimension;
        count = 0;
    }
    // конструктор принимает существующий массив
    MyArrayParent(double *arr, int len)
    {
        cout << "\nMyArrayParent constructor";
        ptr = arr;
        count = len;
        capacity = len;
        // заполнить массив ptr, заполнить поля
    }
    // деструктор
    ~MyArrayParent()
    {
        cout << "\nMyArrayParent destructor";
        if (ptr == NULL)
        {
            return;
        }
        // освободить память, выделенную под ptr
        delete[] ptr;
        ptr = NULL;
    }

    // обращение к полям
    int Capacity() { return capacity; }
    int Size() { return count; }
    double GetComponent(int index)
    {
        if (index >= 0 && index < count)
            return ptr[index];
        else
        {
            cout << "Incorrect Index";
        }
        return -1;
    }
    void SetComponent(int index, double value)
    {
        if (index >= 0 && index < count)
            ptr[index] = value;
        else
        {
            cout << "Incorrect Index";
        }
        // сгенерировать исключение, если индекс неправильный
    }

    // добавление в конец нового значения
    void push(double value)
    {
        if (count >= capacity)
            return;
        ptr[count] = value;
        count++;
    }

    // удаление элемента с конца
    void RemoveLastValue()
    {
        if (count > 0)
        {
            count--;
        }
        return;
    }

    double &operator[](int index)
    {
        // перегрузка оператора []
        return ptr[index];
    }

    MyArrayParent &operator=(MyArrayParent &V)
    {
        if (capacity < V.capacity)
        {
            delete[] ptr;
            ptr = new double[V.capacity];
        }
        capacity = V.capacity;
        count = V.count;

        for (int i = 0; i < count; i++)
            ptr[i] = V[i];

        return *this;
    }

    MyArrayParent(const MyArrayParent &V)
    {
        // создание копии объекта - в основном, при возвращении результата из функции
        /// передаче параметров в функцию
        ptr = new double[V.capacity];
        capacity = V.capacity;
        count = V.count;

        for (int i = 0; i < count; i++)
            ptr[i] = V.ptr[i]; // V[i]
    }

    void print()
    {
        cout << "\nMyArrParent, size: " << count << ", values: {";
        int i = 0;
        for (i = 0; i < count; i++)
        {
            cout << ptr[i];
            if (i != count - 1)
                cout << ", ";
        }
        cout << "}";
    }

    // поиск элемента
    int IndexOf(double value)
    {
        for (int i = 0; i < count; i++)
            if (fabs(ptr[i] - value) < 0.001)
                return i;
        return -1;
    }
};

class MyArrayChild : public MyArrayParent
{
public:
    // используем конструктор родителя. Нужно ли что-то ещё?
    MyArrayChild(int Dimension = 100) : MyArrayParent(Dimension)
    {
        cout << "\nMyArrayChild constructor";
    }
    MyArrayChild(double *arr, int len) : MyArrayParent(arr, len)
    {
        cout << "\nArrChild constructor's working";
    }
    ~MyArrayChild() { cout << "\nMyArrayChild destructor\n"; }

    // удаление элемента
    void RemoveAt(int index = -1)
    {
        if (index == -1)
            RemoveLastValue();
        else if (index < 0 || index >= count)
            return;
        else
        {
            for (int i = index + 1; i < count; i++)
                ptr[i - 1] = ptr[i];
            count--;
        }
    }

    // вставка элемента
    void InsertAt(double value, int index = -1)
    {
        if (index == -1 || index == count)
        {
            push(value);
            return;
        }
        if (index < 0 || index > count)
            return;

        for (int i = count - 1; i >= index; i--)
            ptr[i + 1] = ptr[i];
        count++;
        ptr[index] = value;
    }

    // получение всех индексов элемента
    MyArrayChild AllIndexes(double value)
    {
        MyArrayChild resArr;
        for (int i = 0; i < count; i++)
            if (fabs(ptr[i] - value) < 0.001)
                resArr.push(i);
        return resArr;
    }
};

class MySortedArray : public MyArrayChild
{
protected:
    int BinSearch(double value, int left, int right)
    {
        int middle = (left + right) / 2;
        // база рекурсии
        if (fabs(ptr[middle] - value) < 0.001)
            return middle;
        if (right == left + 1)
            return (fabs(ptr[right] - value) < 0.001) ? right : -1;

        if (ptr[middle] > value)
            return BinSearch(value, left, middle);
        if (ptr[middle] < value)
            return BinSearch(value, middle, right); // можно без if
        return -1;
    }

    int BinSearch2(double value, int left, int right)
    {
        int middle = (left + right) / 2;
        // база рекурсии
        if (fabs(ptr[middle] - value) < 0.001)
            return middle;
        if (right == left + 1)
        {
            if (fabs(ptr[right] - value) < 0.001)
                return right;

            if (ptr[left] < value && ptr[right] > value)
                return right;
            if (ptr[right] < value)
                return right + 1;
            return left;
        }

        if (ptr[middle] > value)
            return BinSearch2(value, left, middle);
        if (ptr[middle] < value)
            return BinSearch2(value, middle, right);
        return -1;
    }

public:
    MySortedArray(int Dimension = 100) : MyArrayChild(Dimension)
    {
        cout << "\nMySortedArray constructor";
    }
    MySortedArray(double *arr, int len) : MyArrayChild(arr, len)
    {
        cout << "\nMySortedArray constructor's working";
    }
    ~MySortedArray() { cout << "\nMySortedArray destructor\n"; }

    int IndexOf(double value) { return BinSearch(value, 0, count - 1); }

    void push(double value)
    {
        if (count >= capacity)
            return;
        if (count == 0)
        {
            MyArrayParent::push(value);
            return;
        }
        if (count == 1)
        {
            if (ptr[0] > value)
            {
                ptr[1] = ptr[0];
                ptr[0] = value;
                count++;
            }
            else
                MyArrayParent::push(value);
            return;
        }
        int index = BinSearch2(value, 0, count - 1);
        InsertAt(value, index);
    }
    MySortedArray AllIndexes(double value)
    {
        MySortedArray resArr;
        int val = this->IndexOf(value);
        if (val >= 0)
        {
            int i = val;

            while ((i >= 0) && (fabs(ptr[i] - value) < 0.001))
            {
                resArr.push(i);
                i--;
            }
            i = val+1;
            while ((i < count) && (fabs(ptr[i] - value) < 0.001))
            {
                resArr.push(i);
                i++;
            }
        }
        return resArr;
    }
};
int main()
{
    MySortedArray arr1;
    if (true)
    {
        MySortedArray arr;
        int i = 0;
        int count = 10;
        for (i = 0; i < count; i++)
        {
            arr.push(abs(1 - i));
        }
        arr.print();
        cout << "\nFind 1: " << arr.IndexOf(1) << "\n";
        cout << "all indexes of 1 ";
        arr.AllIndexes(1).print();
    }
    char c;
    // cin >> c;
    return 0;
}
