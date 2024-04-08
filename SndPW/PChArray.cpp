#include <iostream>
#include <cmath>

using namespace std;

class MyArrayParent
{
protected:
    int capacity; // памяти выделено
    int count;    // кол-во элементов - сколько памяти используем
    double *ptr;

public:
    // конструкторы
    MyArrayParent(int Dimension = 100)
    {
        cout << "\nMyArrayParent constructor 1 ";
        ptr = new double[Dimension];
        capacity = Dimension;
        count = 0;
    }

    // конструктор принимает существующий массив
    MyArrayParent(double *arr, int len)
    {
        cout << "\nMyArrayParent constructor 2 ";
        ptr = new double[len];
        capacity = len;
        count = len;
        for (int i = 0; i < count; i++)
            ptr[i] = arr[i];
    }

    // создание копии объекта - в основном, при возвращении результата из функции / передаче параметров в функцию
    MyArrayParent(const MyArrayParent &V)
    {
        cout << "\nMyArrayParent constructor 3 ";
        ptr = new double[V.capacity];
        capacity = V.capacity;
        count = V.count;

        for (int i = 0; i < count; i++)
            ptr[i] = V.ptr[i];
    }

    // деструктор
    ~MyArrayParent()
    {
        cout << "\nMyArrayParent destructor ";
        if (ptr != NULL)
        {
            delete[] ptr;
            ptr = NULL;
        }
    }

    // обращение к полям
    int getCapacity() { return capacity; }
    int getSize() { return count; }

    double GetComponent(int index)
    {
        if (index >= 0 && index < count)
            return ptr[index];
        else
        {
            throw std::out_of_range("Index out of range!");
            char stop;
            cin >> stop;
        }
        return -1;
    }

    void SetComponent(int index, double value)
    {
        if (index >= 0 && index < count)
            ptr[index] = value;
        else
        {
            throw std::out_of_range("Index out of range.");
            char stop;
            cin >> stop;
        }
    }

    // перегрузки оператора []
    double &operator[](int index)
    {
        cout << "\nMyArrayParent operator [] 1 ";
        return ptr[index];
    }

    const double &operator[](int index) const
    {
        cout << "\nMyArrayParent operator [] 2 ";
        return ptr[index];
    }

    // оператор =
    MyArrayParent &operator=(MyArrayParent &V)
    {
        cout << "\nMyArrayParent operator \"=\" ";
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

    int IndexOf(double value, bool bFindFromStart = true)
    {
        cout << "\nMyArrayParent Index Of function ";
        if (bFindFromStart)
        {
            for (int i = 0; i < count; i++)
                if (fabs(ptr[i] - value) < 0.001)
                    return i;
        }
        else
        {
            for (int i = count - 1; i >= 0; i--)
                if (fabs(ptr[i] - value) < 0.001)
                    return i;
        }
        return -1;
    }

    void print()
    {
        cout << "\nSize: " << count << ", values: {";
        int i = 0;
        for (i = 0; i < count; i++)
        {
            cout << ptr[i];
            if (i != count - 1)
                cout << ", ";
        }
        cout << "}";
    }

    // добавление в конец нового значения
    void push(double value)
    {
        if (count >= capacity)
        {
            throw std::out_of_range("Array run out of memory");
            char stop;
            cin >> stop;
        }
        ptr[count] = value;
        count++;
    }

    // удаление элемента с конца
    void RemoveLastValue()
    {
        if (count >= 0)
            count--;
        throw std::out_of_range("Empty");
        char stop;
        cin >> stop;
    }
};

class MyArrayChild : public MyArrayParent
{
public:
    MyArrayChild(int Dimension = 100) : MyArrayParent(Dimension) { cout << "\nMyArrayChild constructor 1 "; }
    MyArrayChild(double *arr, int len) : MyArrayParent(arr, len) { cout << "\nMyArrayChild constructor 2 "; }

    ~MyArrayChild() { cout << "\nMyArrayChild destructor "; }

    // удаление элемента
    void RemoveAt(int index = -1)
    {
        cout << "\nMyArrayChild Remove At function ";
        if (index == -1)
            RemoveLastValue();
        if (index < 0 || index >= count)
            return;

        for (int i = index + 1; i < count; i++)
            ptr[i - 1] = ptr[i];
        count--;
    }

    // вставка элемента
    void InsertAt(double value, int index = -1)
    {
        cout << "\nMyArrayChild Insert At function ";
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

    MyArrayChild getMinMax()
    {
        double min = ptr[0], max = ptr[0];
        for (int i = 1; i < count; ++i)
        {
            if (min > ptr[i])
                min = ptr[i];
            else if (max < ptr[i])
                max = ptr[i];
        }
        MyArrayChild res(2);
        res.push(min);
        res.push(max);
        return res;
    }

    MyArrayChild IndexOfMax()
    {
        double maxVal = getMinMax()[1];
        MyArrayChild resArr;
        for (int i = 0; i < count; i++)
            if (fabs(ptr[i] - maxVal) < 0.001)
                resArr.push(i);
        return resArr;
    }

    MyArrayChild &operator+=(const double value)
    {
        push(value);
        return *this;
    }

    MyArrayChild Subsequence(int start, int end)
    {
        if (start < 0 || start >= count || end < 0 || end >= count || start > end)
        {
            throw std::out_of_range("Invalid index!");
            char stop;
            cin >> stop;
        }
        MyArrayChild res(end - start + 1);
        for (int i = start; i <= end; i++)
            res.push(ptr[i]);
        return res;
    }
};

class MySortedArray : public MyArrayChild
{
protected:
    int BinSearch(double value, int le, int re)
    {
        cout << "\nMySoretefArray Bin Search Function 1 ";
        int mid = (le + re) / 2;
        while (le <= re)
        {
            if (fabs(ptr[mid] - value) < 0.001)
                return mid;
            if (ptr[mid] < value)
                le = mid + 1;
            else
                re = mid - 1;
        }
        return -1;
    }

    int BinSearch2(double value, int le, int re)
    {
        cout << "\nMySoretedArray Bin Search Function 2 ";
        int mid = (le + re) / 2;
        if (fabs(ptr[mid] - value) < 0.001)
            return mid;
        if (re == le + 1)
        {
            if (fabs(ptr[re] - value) < 0.001)
                return re;

            if (ptr[le] < value && ptr[re] > value)
                return re;
            if (ptr[re] < value)
                return re + 1;
            return le;
        }

        if (ptr[mid] > value)
            return BinSearch2(value, le, mid);
        if (ptr[mid] < value)
            return BinSearch2(value, mid, re);
    }

public:
    MySortedArray(int Dimension = 100) : MyArrayChild(Dimension) { cout << "\nMySortedArray constructor 1 "; }
    MySortedArray(double *arr, int len) : MyArrayChild(arr, len)
    {
        cout << "\nMySortedArray constructor 2 ";
        ptr = arr;
        count = len;
        capacity = len;

        // сортировка массива вставками
        insertionSort(ptr, count);
    }

    void insertionSort(double *arr, int len)
    {
        for (int i = 1; i < len; i++)
        {
            double temp = arr[i];
            int j = i - 1;
            while (j >= 0 && arr[j] > temp)
            {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = temp;
        }
    }

    ~MySortedArray() { cout << "\nMySortedArray destructor "; }

    int IndexOf(double value, bool bFindFromStart = true)
    {
        cout << "\nMySortedArray Index Of function ";
        return BinSearch(value, 0, count - 1);
    }

    void push(double value)
    {
        cout << "\nMySortedArray push function ";
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
};

int main()
{
    // часть 2.1

    double arr1[5] = {3, 6, 8, 10, 13};
    MyArrayParent a(arr1, 5);
    MyArrayParent b(a);
    b.GetComponent(2);
    cout << "\n ";

    MyArrayParent c;
    c = b;
    cout << "\n ";

    c[2];
    cout << "\n ";

    double arr[10] = {3, 6, 9, 18, 27, 35, 48, 65, 79, 98};
    MyArrayParent d(arr, 4);
    d.print();
    
    cout << "\n ";

    cout << '\n'
         << d.IndexOf(3);
    cout << "\n ";

    // часть 2.2
    cout << "\n \n ";

    MyArrayChild e(arr, 10);
    e.RemoveAt(0);
    e.print();
    cout << "\n ";

    e.InsertAt(3, 1);
    e.print();
    cout << "\n ";

    double max[5] = {0, 5, 5, 0, 5};
    MyArrayChild f(max, 5);
    f.IndexOfMax().print();
    cout << "\n ";

    MySortedArray s(arr, 10);
    s += 50;
    s.print();

    char stop;
    cin >> stop;
    return 0;
}