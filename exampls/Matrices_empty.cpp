// Matrices1.cpp: определяет точку входа для консольного приложения.
//

#include <iostream>
#include <string.h>

using namespace std;

/*class Exception: public exception
{
protected:
//сообщение об ошибке
char* str;
public:
Exception(const char* s)
{
str = new char[strlen(s) + 1];
strcpy_s(str, strlen(s) + 1, s);
}
Exception(const Exception& e)
{
str = new char[strlen(e.str) + 1];
strcpy_s(str, strlen(e.str) + 1, e.str);         для VS      fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff
}
~Exception()
{
delete[] str;
}

//функцию вывода можно будет переопределить в производных классах, когда будет ясна конкретика
virtual void print()
{
cout << "Exception: " << str<< "; "«what();
}
};*/

class Exception : public exception
{
protected:
	// сообщение об ошибке
	char *str;

public:
	Exception(const char *s)
	{
		str = new char[strlen(s) + 1];
		strcpy(str, s);
	}
	Exception(const Exception &e)
	{
		str = new char[strlen(e.str) + 1];
		strcpy(str, e.str);
	}
	~Exception()
	{
		delete[] str;
	}

	// функцию вывода можно будет переопределить в производных классах, когда будет ясна конкретика
	virtual void print()
	{
		cout << "Exception: " << str << "; " << what();
	}
};

class WrongSizeException : public Exception
{
protected:
	// сообщение об ошибке
	int Row1, Col1, Row2, Col2;

public:
	WrongSizeException(const char *s, int row1, int row2, int col1, int col2) : Exception(s)
	{
		Row1 = row1;
		Col1 = col1;
		Row2 = row2;
		Col2 = col2;
	}

	virtual void print()
	{
		cout << "WrongSizeExeption " << str << "; " << Row1 << ", " << Col1 << ", " << Row2 << ", " << Col2 << "; " << what();
	}
};

class IndexOutOfBounceException : public Exception
{
protected:
	// сообщение об ошибке
	int Row, Col;

public:
	IndexOutOfBounceException(const char *s, int row, int col) : Exception(s)
	{
		Row = row;
		Col = col;
	}

	virtual void print()
	{
		cout << "IndexOutOfBounce " << str << "; " << Row << ", " << Col << "; " << what();
	}
};

class BaseMatrix
{
protected:
	double **ptr;
	int height;
	int width;

public:
	BaseMatrix(int Height = 2, int Width = 2)
	{
		// конструктор
		if (Height <= 0 || Width <= 0)
			throw WrongSizeException("Attempt to create matrix of non-positive size", Height, Width, -1, -1);
		height = Height;
		width = Width;
		ptr = new double *[height];
		for (int i = 0; i < height; i++)
			ptr[i] = new double[width];
	}

	BaseMatrix(const BaseMatrix &M)
	{
		// конструктор копий
		height = M.height;
		width = M.width;
		ptr = new double *[height];
		for (int i = 0; i < height; i++)
		{
			ptr[i] = new double[width];
			for (int j = 0; j < width; j++)
			{
				ptr[i][j] = M.ptr[i][j];
			}
		}
	}

	BaseMatrix operator=(const BaseMatrix &V)
	{
		// оператор присваивания
		if (height != V.height & width != V.width)
		{
			if (ptr != NULL)
			{
				for (int i = 0; i < height; i++)
					delete[] ptr[i];
				delete[] ptr;
				ptr = NULL;
			}
			height = V.height;
			width = V.width;
			ptr = new double *[height];
			for (int i = 0; i < height; i++)
				ptr[i] = new double[width];
		}
		for (int i = 0; i < height; i++)
			for (int j = 0; j < width; j++)
				ptr[i][j] = V.ptr[i][j];
		return *this;
	}

	double &operator()(int row, int col)
	{
		if (row < 0 || col < 0 || row >= height || col >= width)
			throw IndexOutOfBounceException("IndexOutOfBounceException in operator()", row, col);
		return ptr[row][col];
	}

	~BaseMatrix()
	{
		// деструктор
		if (ptr != NULL)
		{
			for (int i = 0; i < height; i++)
				delete[] ptr[i];
			delete[] ptr;
			ptr = NULL;
		}
	}

	void print()
	{
		// вывод
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
				cout << ptr[i][j] << " ";
			cout << "\n";
		}
	}
};

class Matrix : public BaseMatrix
{
public:
	Matrix(int Height = 2, int Width = 2) : BaseMatrix(Height, Width) {}

	double Trace() const // traces of matrix
	{
		double result = 0;
		if (height == width)
		{
			for (int i = 0; i < height; i++)
				result += ptr[i][i];
		}
		else
			cout << "Не квадратная матрица\n";
		return result;
	}

	Matrix operator+(Matrix M) const
	{
		if (height != M.height || width != M.width)
			throw WrongSizeException("Unequal size of matrices to add", height, width, M.height, M.width);
		Matrix res(height, width);
		for (int i = 0; i < height; i++)
			for (int j = 0; j < height; j++)
				res(i, j) = ptr[i][j] + M(i, j);
		return res;
	}
};

int main()
{
	try
	{
		Matrix M/*(0, -1)*/;
		M(0, 0) = 1;
		M(0, 1) = 2;
		M(1, 0) = 3;
		M(1, 1) = 4;
		// M(1, 2) = 5;
		
		Matrix M1 = M;
		Matrix M2 = M1 + M;
		M2.print();
		cout << "\nTr(M) = " << M2.Trace();
	}
	catch (IndexOutOfBounceException ex)
	{
		cout << "\nIndexOutOfBounceException has been cought!!!\n";
		ex.print();
	}
	catch (WrongSizeException ex)
	{
		cout << "\nWrongSizeException has been cought!!!\n";
		ex.print();
	}

	char c;
	cin >> c;

	return 0;
}