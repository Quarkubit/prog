// Matrices1.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

/*class Exception: public exception
{
protected:
//��������� �� ������
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
strcpy_s(str, strlen(e.str) + 1, e.str);         ��� VS      fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff
}
~Exception()
{
delete[] str;
}

//������� ������ ����� ����� �������������� � ����������� �������, ����� ����� ���� ����������
virtual void print()
{
cout << "Exception: " << str<< "; "�what();
}
};*/

class Exception : public exception
{
protected:
	// ��������� �� ������
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

	// ������� ������ ����� ����� �������������� � ����������� �������, ����� ����� ���� ����������
	virtual void print()
	{
		cout << "Exception: " << str << "; " << what();
	}
};

class WrongSizeException : public Exception
{
protected:
	// ��������� �� ������
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
	// ��������� �� ������
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
		// �����������
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
		// ����������� �����
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
		// �������� ������������
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
		// ����������
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
		// �����
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
			cout << "�� ���������� �������\n";
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

	friend ostream &operator<<(ostream &s, Matrix m);
	friend istream &operator>>(istream &s, Matrix &m);
};

ostream &operator<<(ostream &s, Matrix m)
{
	if (typeid(s) == typeid(ofstream))
	{
		s << m.height << " " << m.width;
		for (int i = 0; i < m.height; i++)
			for (int j = 0; j < m.width; j++)
				s << m.ptr[i][j] << " ";
		return s;
	}
	for (int i = 0; i < m.height; i++)
	{
		for (int j = 0; j < m.width; j++)
			s << m.ptr[i][j] << " ";
		s << "\n";
	}
	return s;
}

istream &operator>>(istream &s, Matrix &m)
{
	if (typeid(s) == typeid(ofstream))
	{
		s >> m.height >> " " >> m.width;
		for (int i = 0; i < m.height; i++)
			for (int j = 0; j < m.width; j++)
				s >> m[i][j];
	}
	for (int i = 0; i < m.height; i++)
		for (int j = 0; j < m.width; j++)
			s >> m.ptr[i][j];
	return s;
}

int main()
{
	try
	{
		Matrix M /*(0, -1)*/;
		/*M(0, 0) = 1;
		M(0, 1) = 2;
		M(1, 0) = 3;
		M(1, 1) = 4;
		// M(1, 2) = 5;

		Matrix M1 = M;
		Matrix M2 = M1 + M;
		M2.print();
		cout << "\nTr(M) = " << M2.Trace();*/
		cin >> M;

		ofstream fout("1.txt");
		if (fout)
		{
			fout << M;
			fout.close();
		}
		Matrix M1;
		ifstream fin("1.txt");
		if (fin)
		{
			fin >> M1;
			fin.close();
		}
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
	catch (exception ex)
	{
		cout << "\nSmth has been cought\n";
		ex.what();
	}

	char c;
	cin >> c;

	return 0;
}