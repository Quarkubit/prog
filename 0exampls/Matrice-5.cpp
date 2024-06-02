#include <iostream>
#include <fstream>
#include<string.h>
#include <vector>

using namespace std;

/*class Exception: public exception
{
protected:
    //????????? ?? ??????
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
        strcpy_s(str, strlen(e.str) + 1, e.str);
    }
    ~Exception()
    {
        delete[] str;
    }

    //??????? ?????? ????? ????? ?????????????? ? ??????????? ???????, ????? ????? ???? ??????????
    virtual void print()
    {
        cout << "Exception: " << str<< "; "<<what();
    }
};*/

class Exception : public exception
{
protected:
    //????????? ?? ??????
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

    //??????? ?????? ????? ????? ?????????????? ? ??????????? ???????, ????? ????? ???? ??????????
    virtual void print()
    {
        cout << "Exception: " << str << "; " << what();
    }
};

class WrongSizeException : public Exception
{
protected:
    int Row1, Col1, Row2, Col2;

public:
    WrongSizeException(const char *s, int row1, int col1, int row2, int col2) : Exception(s)
    {
        Row1 = row1;
        Col1 = col1;
        Row2 = row2;
        Col2 = col2;
    }
    virtual void print()
    {
        cout << "WrongSizeException: " << str << "; " << Row1 << ", " << Col1 << ", " << Row2 << ", " << Col2 << "; " << what();
    }
};

class IndexOutOfBoundsException : public Exception
{
protected:
    int Row, Col;

public:
    IndexOutOfBoundsException(const char *s, int row, int col) : Exception(s)
    {
        Row = row;
        Col = col;
    }
    virtual void print()
    {
        cout << "IndexOutOfBoundsException: " << str << "; " << Row << ", " << Col << "; " << what();
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
        //???????????
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
        //??????????? ?????
        height = M.height;
        width = M.width;
        ptr = new double *[height];
        for (int i = 0; i < height; i++)
        {
            ptr[i] = new double[width];
            for (int j = 0; j < width; j++)
                ptr[i][j] = M.ptr[i][j];
        }
    }

    BaseMatrix operator=(const BaseMatrix &V)
    {
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

    ~BaseMatrix()
    {
        //??????????
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
        //?????
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
                cout << ptr[i][j] << " ";
            cout << "\n";
        }
    }

    double &operator()(int row, int col)
    {
        if (row < 0 || col < 0 || row >= height || col >= width)
            throw IndexOutOfBoundsException("IndexOutOfBoundsException in operator()", row, col);
        return ptr[row][col];
    }

    int getHeight() const { return height; }
    int getWidth() const { return width; }
    double **getPtr() { return ptr; }
};

class Matrix : public BaseMatrix
{
public:
    Matrix(int Height = 2, int Width = 2) : BaseMatrix(Height, Width) { cout << "\nMatrix constructor"; }
    ~Matrix() { cout << "\nMatrix destructor"; }

    double Trace()
    {
        double summ = 0;
        for (int i = 0; i < getHeight(); i++)
            summ += getPtr()[i][i];
        return summ;
    }

    Matrix operator+(Matrix M)
    {
        if (getHeight() != M.getHeight() || getWidth() != M.getWidth())
            throw WrongSizeException("Unequal size of matrices to add in operator+()", getHeight(), getWidth(), M.getHeight(), M.getWidth());
        Matrix res(getHeight(), getWidth());
        for (int i = 0; i < getHeight(); i++)
            for (int j = 0; j < getWidth(); j++)
                res(i, j) = getPtr()[i][j] + M.getPtr()[i][j];
        return res;
    }

    friend ostream &operator<<(ostream &s, Matrix M);
    friend istream &operator>>(istream &s, Matrix &M);
};

ostream &operator<<(ostream &s, Matrix M)
{
    if (typeid(s) == typeid(ofstream))
    {
        s << M.getHeight() << " " << M.getWidth() << " ";
        for (int i = 0; i < M.getHeight(); i++)
            for (int j = 0; j < M.getWidth(); j++)
                s << M.getPtr()[i][j] << " ";
        return s;
    }
    for (int i = 0; i < M.getHeight(); i++)
    {
        for (int j = 0; j < M.getWidth(); j++)
            s << M.getPtr()[i][j] << " ";
        s << "\n";
    }
    return s;
}

istream &operator>>(istream &s, Matrix &M)
{
    if (typeid(s) == typeid(ifstream))
    {
        int w, h;
        s >> h >> w;
        if (h != M.getHeight() || w != M.getWidth())
        {
            //...
        }
    }
    for (int i = 0; i < M.getHeight(); i++)
        for (int j = 0; j < M.getWidth(); j++)
            s >> M.getPtr()[i][j];
    return s;
}

vector<double> getMaxElements(Matrix &M)
{
    vector<double> maxElements(M.getHeight());
    for (int i = 0; i < M.getHeight(); i++)
    {
        double maxElement = M.getPtr()[i][0];
        for (int j = 1; j < M.getWidth(); j++)
        {
            if (M.getPtr()[i][j] > maxElement)
                maxElement = M.getPtr()[i][j];
        }
        maxElements[i] = maxElement;
    }
    return maxElements;
}

int main()
{
    try
    {
        Matrix M(3, 4);
        M(0, 0) = 1;
        M(0, 1) = 2000;
        M(0, 2) = 3;
        M(0, 3) = 4;
        M(1, 0) = 5;
        M(1, 1) = 667;
        M(1, 2) = 7;
        M(1, 3) = 8;
        M(2, 0) = 9;
        M(2, 1) = 10;
        M(2, 2) = 13;
        M(2, 3) = 12;
        
        Matrix Mat[10];
        for(int i=0;i<10;i++)
    	{
    	    Mat[i](0, 0) = i;
    	    Mat[i](0, 1) = i;
    	    Mat[i](1, 0) = i;
    	    Mat[i](1, 1) = i;
    	}
    	Matrix M2(3, 3); 
    	for(int i=0;i<3;i++)
    	    for(int j=0;j<3;j++)
    	        M2(i, j) = i+j;
    	Mat[5] = M2;
    	
    	ofstream fout("1.txt");
    	if(fout)
    	{
    	    fout<<"10\n";
    	    for(int i=0;i<10;i++)
    	        fout<<Mat[i]<<"\n";
    	    fout.close();   
    	}
    	Matrix* M1;
    	Matrix M3;
    	ifstream fin("1.txt");
    	if(fin)
    	{
    	    int n;
    	    fin>>n;
    	    M1 = new Matrix[n];
    	    for(int i=0;i<10;i++)
    	    {
    	        fin>>M1[i];
    	        cout<<M1[i]<<"\n";
    	    }
    	    while(!fin.eof())
    	    {
    	        fin>>M3;
    	        cout<<M3;
    	    }
    	    fin.close();
    	    delete[] M1;
    	}

        vector<double> maxElements = getMaxElements(M);

        cout << " Max elements: ";
        for (int i = 0; i < maxElements.size(); i++)
            cout << maxElements[i] << " ";
        cout << endl;
    }
    catch (IndexOutOfBoundsException ex)
    {
        cout << "\nIndexOutOfBoundsException has been caught\n";
        ex.print();
    }
    catch (Exception ex)
    {
        cout << "\nSomething has been caught\n";
        ex.print();
    }
    catch (exception ex)
    {
        cout << "\nSomething has been caught\n";
        ex.what();
    }
    
    char c;
    cin >> c;

    return 0;
}
