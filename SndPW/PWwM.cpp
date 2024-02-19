#include <iostream>
using namespace std;

class MyArrayParent
{
protected:
//сколько памяти выделено?
int capacity;
//количество элементов - сколько памяти используем
int count;
//массив
double* ptr;
public:
//конструкторы и деструктор
MyArrayParent(int Dimension = 100)
{
cout << "\nMyArray constructor";
ptr = new double[Dimension];
capacity = Dimension;
count = 0;
}
//конструктор принимает существующий массив
MyArrayParent(double* arr, int len)
{
cout << "\nMyArray constructor";
//заполнить массив ptr, заполнить поля
}
//деструктор
~MyArrayParent()
{
cout << "\nMyArray destructor";
if (ptr != NULL)
{
delete[] ptr;
ptr = NULL;
}
}
//обращение к полям
int Capacity() { return capacity; }
int Size() { return count; }
double GetComponent(int index)
{
if (index >= 0 && index < count)
return ptr[index];
//сгенерировать исключение, если индекс неправильный
return -1;
}
void SetComponent(int index, double value)
{
if (index >= 0 && index < count)
ptr[index] = value;
//сгенерировать исключение, если индекс неправильный
}
//добавление в конец нового значения
void push(double value)
{
if (count < capacity)
{
ptr[count] = value;
count++;
}
//что делаем, если массив заполнен?
}
//удаление элемента с конца
void RemoveLastValue()
{
if (count >= 0)
count--;
//что делаем, если пуст?
}
double& operator[](int index)
{
//перегрузка оператора []
}
MyArrayParent& operator=(const MyArrayParent& V)
{
cout << "\noperator = ";
//оператор =
//arr1 = arr2 = arr3; где arr_i - объекты нашего класса
}
void MyArray(const MyArrayParent& V)
{
cout << "\nCopy constructor";
// создание копии объекта - в основном, при возвращении
// результата из функции / передаче параметров в функцию
}
void print()
{
cout << "\nMyArr, size: " << count << ", values: {";
int i = 0;
for (i = 0; i < count; i++)
{
cout << ptr[i];
if (i != count - 1)
cout << ", ";
}
cout << "}";
}
};
class MyArrayChild : public MyArrayParent
{
public:
//используем конструктор родителя. Нужно ли что-то ещё?
MyArrayChild(int Dimension = 100) : MyArrayParent(Dimension)
{ cout << "\nMyArrayChild constructor"; }
~MyArrayChild() { cout << "\nMyArrayChild destructor\n"; }
//удаление элемента
//void RemoveAt(int index = -1);
//поиск элемента
//int IndexOf(double value, bool bFindFromStart = true);
//вставка элемента
//void InsertAt(double value, int index = -1);
//выделение подпоследовательности
//MyArrayChild SubSequence(int StartIndex = 0, int Length =-1)
//добавление элемента в конец
//operator + ?
};
int main()
{
if (true)
{
MyArrayParent arr;
int i = 0;
for (i = 0; i < 10; i++)
{
arr.push(i + 1);
}
MyArrayParent p1;
p1 = arr;
p1.print();
cout << "\n";
}
char c; cin >> c;
return 0;
}