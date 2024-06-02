#include <iostream>
#include <fstream>
#include <string.h>
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
public:
    WrongSizeException(const char *s) : Exception(s) {}
    WrongSizeException(const WrongSizeException &e) : Exception(e) {}
};

class IndexOutOfBoundsException : public Exception
{
public:
    IndexOutOfBoundsException(const char *s) : Exception(s) {}
    IndexOutOfBoundsException(const IndexOutOfBoundsException &e) : Exception(e) {}
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
            throw WrongSizeException("Attempt to create matrix of non-positive size");
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
            throw IndexOutOfBoundsException("IndexOutOfBoundsException in operator()");
        return ptr[row][col];
    }

    int getHeight() const { return height; }
    int getWidth() const { return width; }
    double **getPtr() { return ptr; }
};

class Matrix : public BaseMatrix
{
public:
    Matrix(int Height = 2, int Width = 2) : BaseMatrix(Height, Width)
    {
        // cout << "\nMatrix constructor";
    }
    ~Matrix()
    {
        // cout << "\nMatrix destructor";
    }

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
            throw WrongSizeException("Unequal size of matrices to add in operator+()");
        Matrix res(getHeight(), getWidth());
        for (int i = 0; i < getHeight(); i++)
            for (int j = 0; j < getWidth(); j++)
                res(i, j) = getPtr()[i][j] + M.getPtr()[i][j];
        return res;
    }

    pair<double, double> getCenterOfMass()
    {
        double totalMass = 0;
        double x = 0;
        double y = 0;
        for (int i = 0; i < getHeight(); i++)
        {
            for (int j = 0; j < getWidth(); j++)
            {
                totalMass += getPtr()[i][j];
                x += j * getPtr()[i][j];
                y += i * getPtr()[i][j];
            }
        }
        x /= totalMass;
        y /= totalMass;
        return make_pair(y, x);
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
            M = Matrix(h, w);
        }
    }
    for (int i = 0; i < M.getHeight(); i++)
        for (int j = 0; j < M.getWidth(); j++)
            s >> M.getPtr()[i][j];
    return s;
}

int main()
{
    try
    {
        Matrix M(3, 4);
        M(0, 0) = 0;
        M(0, 1) = 0;
        M(0, 2) = 30000;
        M(0, 3) = 0;
        M(1, 0) = 0;
        M(1, 1) = 0;
        M(1, 2) = 0;
        M(1, 3) = 0;
        M(2, 0) = 0;
        M(2, 1) = 0;
        M(2, 2) = 0;
        M(2, 3) = 0;
        cout << M << endl;

        Matrix Matrica[10];
        for (int i = 0; i < 10; i++)
        {
            Matrica[i](0, 0) = i;
            Matrica[i](0, 1) = i;
            Matrica[i](1, 0) = i;
            Matrica[i](1, 1) = i;
        }

        cout << "3d matrix:" << "\n__________________" << endl;
        for (int i = 0; i < 10; i++)
        {
            cout << Matrica[i] << endl;
            if (i<9) cout << "_______" << endl;
        }
        cout << "__________________" << endl;

        Matrix M2(3, 3);
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                M2(i, j) = i + j;
        Matrica[5] = M2;

        ofstream fout("pract5.txt");
        if (fout)
        {
            for (int i = 0; i < 10; i++)
                fout << Matrica[i] << "\n";
            fout.close();
        }
        Matrix *M1;
        Matrix M3;
        ifstream fin("pract5.txt");
        if (fin)
        {
            int n;
            fin >> n;
            M1 = new Matrix[n];
            for (int i = 0; i < 10; i++)
            {
                fin >> M1[i];
                cout << M1[i] << "\n";
            }
            while (!fin.eof())
            {
                fin >> M3;
                cout << M3;
            }
            fin.close();
            delete[] M1;
        }

        pair<double, double> CenterOfMass = M.getCenterOfMass();

        cout << "Center of mass: ";
        cout << "{" << CenterOfMass.first << ", " << CenterOfMass.second << "}\n"
             << endl;
        cout << "end of code" << endl;
    }
    catch (WrongSizeException ex)
    {
        cout << "\nWrongSizeException has been caught\n";
        ex.print();
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
