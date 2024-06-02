#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class Exception : public std::exception
{
protected:
	char* str;
public:
	Exception(const char* s)
	{
		str = new char[strlen(s) + 1];
		strcpy_s(str, strlen(s) + 1, s);
	}
	Exception(const Exception& ex)
	{
		str = new char[strlen(ex.str) + 1];
		strcpy_s(str, strlen(ex.str) + 1, ex.str);
	}
	~Exception() { delete[] str; }
	virtual void print() { cout << "Exception: " << str; }
};


class IndexOutOfBoundsException : public Exception
{
protected:
	int row, col;
public:
	IndexOutOfBoundsException(const char* _string, int _row, int _col) : Exception(_string) { row = _row; col = _col; }
	virtual void print()
	{
		cout << "IndexOutOfBoundsException: " << str << "; " << row << ", " << col << "; " << what();
	}
};

class NonPositiveElement : public Exception
{
protected:
	int value;
public:
	NonPositiveElement(const char* _string, int value_) : Exception(_string) { value = value_; }
	virtual void print()
	{
		cout << "NonPositiveElement: " << str << "; " << value << "; " << what();
	}
};
class Nullptr : public Exception
{
public:
	Nullptr(const char* _string) : Exception(_string) {}
	virtual void print()
	{
		cout << "Nullptr: " << str<<"; "<<what();
	}
};

class WrongSizeException : public Exception
{
protected:
	int Row1, Col1, Row2, Col2;
public:
	WrongSizeException(const char* s, int row1, int col1, int row2, int col2) : Exception(s) { Row1 = row1; Col1 = col1; Row2 = row2; Col2 = col2; }
	virtual void print()
	{
		cout << "WrongSizeException: " << str << "; " << Row1 << ", " << Col1 << ", " << Row2 << ", " << Col2 << "; " << what();
	}
};

class NonPositiveSize : public WrongSizeException
{
protected:
	int Row1, Col1, Row2, Col2;
public:
	NonPositiveSize(const char* s, int row1, int col1, int row2, int col2) : WrongSizeException(s,row1,col1,row2,col2) { Row1 = row1; Col1 = col1; Row2 = row2; Col2 = col2; }
	virtual void print()
	{
		cout << "NonPositiveSize: " << str << "; " << Row1 << ", " << Col1 << ", " << Row2 << ", " << Col2 << "; " << what();
	}
};

template<class T>
class matrixParent
{
protected:
	T** pointer;
	int height, width;
public:
	matrixParent(T** ptr, int Height = 2, int Width = 2) 
	{
		if (ptr == NULL) { throw Nullptr("Nullptr"); }
		if (Height < 0 || Width < 0) { throw NonPositiveSize("Non-Positive size of Matrix", height, width, -1,-1); }
		if (Height == 0 || Width == 0) { throw WrongSizeException("Wrong size of Matrix", height, width, -1, -1); }
		height = Height; width = Width;
		pointer = new T* [height];
		for (int i = 0; i < height; ++i)
		{
			*(pointer + i) = new T[width];
			for (int j = 0; j < width; ++j)
			{
				*(*(pointer + i) + j) = *(*(ptr + i) + j);
			}
		}
	}
	matrixParent(int Height = 2, int Width = 2)
	{
		if(Height < 0 || Width < 0) { throw NonPositiveSize("Non-Positive size of Matrix", height, width, -1, -1); }
		if (Height == 0 && Width == 0) { throw WrongSizeException("Wrong size of Matrix", height, width, -1, -1); }
		height = Height; width = Width;
		pointer = new T* [height];
		for (int i = 0; i <  height; ++i)
		{
			*(pointer+i) = new T[width];
			for (int j = 0; j < width; ++j)
			{
				*(*(pointer + i) + j) = 1;
			}
		}
	}
	matrixParent(const matrixParent& _copy)
	{
		height = _copy.height; width = _copy.width;
		pointer = new T* [height];
		for (int i = 0; i < height; ++i)
		{
			*(pointer + i) = new T[width];
			for (int j = 0; j < width; ++j)
			{
				*(*(pointer + i) + j) = *(*(_copy.pointer + i) + j);
			}
		}
	}
	virtual ~matrixParent()
	{
		if (pointer != nullptr)
		{
			for (int i = 0; i < height; ++i)
			{
				delete pointer[i];
			}
			delete[] pointer;
			pointer = nullptr;
		}
	}
	matrixParent operator=(matrixParent& eql)
	{
		if ((height != eql.height) || (width != eql.width))
		{
			if (pointer != nullptr)
			{
				for (int i = 0; i < height; ++i)
					delete pointer[i];
				delete[] pointer;
				pointer = nullptr;
			}
			height = eql.height;
			width = eql.width;
			pointer = new T* [height];
			for (int i = 0; i < height; ++i) 
			{
				pointer[i] = new T[width];
			}
		}
		for (int i = 0; i < height; ++i) 
		{
			for (int j = 0; j < width; ++j) 
			{
				pointer[i][j] = eql.pointer[i][j];
			}
		}
		return *this;
	}

	T& operator()(int row, int col)
	{
		if (row < 0 || col < 0 || row >= height || col >= width)
			throw IndexOutOfBoundsException("IndexOutOfBoundsException in operator()", row, col);
		return pointer[row][col];
	}
	template<class T>
	friend istream& operator>>(istream& input, matrixParent<T>& mtrx)
	{
		if (typeid(input) == typeid(ifstream))
		{
			int w, h; input >> h >> w;
		}
		for (int i = 0; i < mtrx.height; ++i)
		{
			for (int j = 0; j < mtrx.width; ++j)
			{
				input >> mtrx.pointer[i][j];
			}
		}
		return input;
	}
	
	template<class T>
	friend ostream& operator<<(ostream& output, matrixParent<T>& mtrx)
	{
		if (typeid(output) == typeid(ofstream))
		{
			output << mtrx.height << " " << mtrx.width << " ";
			for (int i = 0; i < mtrx.height; ++i)
			{
				for (int j = 0; j < mtrx.width; ++j)
				{
					output << mtrx.pointer[i][j] << " ";
				}
			}
			return output;
		}
		for (int i = 0; i < mtrx.height; ++i)
		{
			for (int j = 0; j < mtrx.width; ++j)
			{
				output << mtrx.pointer[i][j] << " ";
			}
			output << "\n";
		}
		return output;
	}
};

template<class T>
class matrixChild :virtual public matrixParent<T>
{
public:
	using matrixParent<T>::width; using matrixParent<T>::height; using matrixParent<T>::pointer;
	matrixChild(T** ptr, int row, int col) : matrixParent<T>(ptr, row, col) {}
	matrixChild (int Height = 2, int Width = 2) : matrixParent<T>(Height, Width)
	{
		for (int i = 0; i < height; ++i)
		{
			for (int j = 0; j < width; ++j)
			{
				*(*(pointer + i) + j) = i*(j+2) + i+(2<<(j+i));
			}
		}
	}
	matrixChild(const matrixChild& _copy) : matrixParent<T>(matrixChild& _copy) {}

	template<class T1> 
	T1* geometrix(T1* &vector) 
	{
		if (vector == nullptr) { throw Nullptr("Nullptr"); }
		for (int i = 0; i < width; ++i)
		{
			double mult = 1;
			for (int j = 0; j < height; ++j)
			{
				if (pointer[j][i] < 0) { throw NonPositiveElement("IrrationalElement", pointer[j][i]); }
				mult *= *(*(pointer + j) + i); 
			}
			vector[i] = pow(mult, 1 / (double)(width));
		}
		return vector;
	}
};

template<class T>
void print(T* ptr, int row)
{
	cout << "GMTRX is : ";
	for (int i = 0; i < row; ++i)
	{
		cout << ptr[i] << ' ';
	}
}

int main()
{
	try {
		int mtrx[2][2] = { {1,2}, {2,3} };
		const int r = 2, c = 2;
		double* vec = new double[r];
		int** ptr;
		ptr = new int* [r];
		for (int i = 0; i < r; ++i)
		{
			*(ptr + i) = new int[c];
			for (int j = 0; j < c; ++j)
			{
				*(*(ptr + i) + j) = *(*(mtrx + i) + j);
			}
		}
		matrixParent<int> M(ptr, r, c);
		matrixParent<int> M2(r,c);
		matrixChild<int> M3(r, c);
		matrixChild<int> M4(r + 1, c + 1), M5(r + 5, c + 5);
		matrixChild<int> M6(1, 5);
		cout << "For :\n" << M3;
		print((M3.geometrix(vec)), r);
		ofstream fout("1.txt");
		if (fout)
		{
			fout << M << M2 << M3 << M4 << M5 << M6;
			fout.close();
		}
		cout << "\nFrom file: ";
		ifstream fin("1.txt");
		if (fin)
		{
			int row, col;
			matrixChild<int>* M1;
			fin.seekg(0, fin.end);
			uint64_t fileEnd = fin.tellg();
			fin.seekg(0, fin.beg);
			while (uint64_t(fin.tellg()) < fileEnd - 1)
			{
				cout << '\n';
				fin >> row >> col;
				M1 = new matrixChild<int>(row, col);
				for (int i = 0; i < row; ++i)
				{
					cout << '\n';
					for (int j = 0; j < col; ++j)
					{
						fin >> (*M1)(i, j);
						cout << (*M1)(i, j) << ' ';
					}
				}
				fin.seekg(0, fin.cur);
			}
			cout << '\n';
		}
	}
	catch (IndexOutOfBoundsException& ex)
	{
		cout << "\nIndexOutOfBoundsException has been caught\n"; ex.print();
	}
	catch (NonPositiveSize& ex)
	{
		cout << "\n NonPositiveSize has been caught\n"; ex.print();
	}
	catch (WrongSizeException& ex)
	{
		cout << "\nWrongSizeException has been caught\n"; ex.print();
	}
	catch (NonPositiveElement& ex)
	{
		cout << "\nIrrationalElement has been caught\n"; ex.print();
	}
	catch (Nullptr& ex)
	{
		cout << "\nNullptr has been caught\n"; ex.print();
	}
	catch (Exception& ex)
	{
		cout << "\nCaught exeption\n"; ex.print();
	}
	catch (exception& ex)
	{
		cout << "\nSomething has been caught\n" << ex.what();
	}
}


// метод снизу использует unique_ptr (shared_ptr), однако при неквадратных матрицах - return -inf, но все считывается правильно.
			//using matrixShared = shared_ptr<matrixChild<int>>;
			////vector<matrixShared> M1;
			//fin.seekg(0, fin.end);
			//uint64_t fileEND = fin.tellg();
			//fin.seekg(0, fin.beg);
			//while (fin.tellg() < uint64_t(fileEND) - 1)
			//{
			//	fin >> row >> col;
			//	matrixShared m = make_shared<matrixChild<int>>(row, col);
			//	M1.push_back(m);
			//	cout << '\n';
			//	for (int i = 0; i < row; ++i)
			//	{
			//		for (int j = 0; j < col; ++j)
			//		{
			//			fin >> (*m)(i, j);
			//			cout << ((*m)(i, j)) << "  ";
			//		}
			//		cout << '\n';
			//	}
			//}
			//fin.close();