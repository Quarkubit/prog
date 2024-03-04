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
		cout << "\nMyArrayParent constructor";
		//выделить память под массив ptr, заполнить поля
		ptr = new double[Dimension];
		capacity = Dimension;
		count = 0;
	}
	//конструктор принимает существующий массив
	MyArrayParent(double* arr, int len)
	{
		cout << "\nMyArrayParent constructor";
		//заполнить массив ptr, заполнить поля
	}
	//деструктор
	~MyArrayParent()
	{
		cout << "\nMyArrayParent destructor";
		//освободить память, выделенную под ptr
		delete[] ptr;
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
		if (count >= capacity)
			return;
		ptr[count] = value;
		count++;
	}

	//удаление элемента с конца
	void RemoveLastValue()
	{
		if (count > 0)
		{
			//ptr[count-1] = 0;
			count--;
		}
		//что делаем, если пуст?
	}

	double& operator[](int index)
	{
		//перегрузка оператора []
		return ptr[index];
	}

	MyArrayParent& operator=(MyArrayParent& V)
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

	MyArrayParent(const MyArrayParent& V)
	{
		//создание копии объекта - в основном, при возвращении результата из функции / передаче параметров в функцию
		ptr = new double[V.capacity];
		capacity = V.capacity;
		count = V.count;

		for (int i = 0; i < count; i++)
			ptr[i] = V.ptr[i];	//V[i]
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
};

void f(MyArrayParent p)
{
	cout << "\nIn f(): ";
	p.print();
}

class MyArrayChild : public MyArrayParent
{
public:
	//используем конструктор родителя. Нужно ли что-то ещё?
	MyArrayChild(int Dimension = 100) : MyArrayParent(Dimension) { cout << "\nMyArrayChild constructor"; }

	~MyArrayChild() { cout << "\nMyArrayChild destructor\n"; }

	//удаление элемента
	void RemoveAt(int index = -1)
	{
		if (index == -1) RemoveLastValue();
		if (index < 0 || index >= count) return;

		for (int i = index + 1; i < count; i++)
			ptr[i - 1] = ptr[i];
		count--;
	}

	//поиск элемента

	int IndexOf(double value, bool bFindFromStart = true)
	{
		for (int i = 0; i < count; i++)
			if (abs(ptr[i]-value)<0.001) return i;
		return -1;
	}

	//вставка элемента
	void InsertAt(double value, int index = -1)
	{
		if (index == -1) {push(value); return;}
		if (index < 0 || index >= count) return;

		for (int i = count-1; i >= index; i--) 
			ptr[i+1] = ptr[i];
		count++;
		ptr[index] = value;
	}

	//выделение подпоследовательности
	//MyArrayChild SubSequence(int StartIndex = 0, int Length = -1)

	//добавление элемента в конец
	//operator + ?

};

int main()
{
	MyArrayChild arr1;
	if (true)
	{
		MyArrayChild arr;
		//MyArrayChild arr;
		int i = 0;
		for (i = 0; i < 10; i++)
		{
			arr.push(i + 1);
		}
		arr[4] = 1000;
		arr.RemoveAt(6);
		arr.print();
		arr.InsertAt(100, 3); f(arr); cout << "\nAfter f(): ";
		arr.print();
		arr1 = arr;
		cout << "\nFind: "<<arr.IndexOf(100)<<"\n";
		//cout << "\n" << sp << "\n";
	}
	arr1.print();
	char c; cin >> c;
	return 0;
}