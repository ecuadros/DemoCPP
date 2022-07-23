#ifndef __MATRIX_H__  
#define __MATRIX_H__ 

#include <iostream>
using namespace std;

template <typename T>
class CMatrix
{
private:
    size_t m_rows = 0, m_cols = 0;
    T **m_pMat = nullptr;
public:
    CMatrix(size_t rows = 0, size_t cols = 0, T val = 0)
    {
        create(rows, cols, val);
    }
    CMatrix(CMatrix<T> &&other)
    {
        m_pMat = move(other.m_pMat);
        other.m_rows = other.m_cols = 0;
    }
    ~CMatrix()
    {
        destroy();
    }

private:
    void create(size_t rows, size_t cols, T &val)
    {
        destroy();
        m_rows = rows;  m_cols = cols;
        m_pMat = new T *[m_rows];
        for(auto i = 0; i < m_rows; ++i)
        {    m_pMat[i]  = new T[m_cols];
        // *(m_pMat +i ) = new T[m_cols];
        }
        init(val);
    }
    void init(T &val)
    {
        for(auto row = 0; row < m_rows; ++row)
            for(auto col = 0; col < m_cols; ++col)
            {
                     m_pMat[row][col] = val;
            //    (*(m_pMat+row))[col] = val;
            //   *(*(m_pMat+row)+col)  = val;
            //     *(m_pMat[row]+col)  = val;
            }
    }
    void destroy()
    {
        for(auto row = 0; row < m_rows; ++row)
            delete [] m_pMat[row];
        delete [] m_pMat;
        m_rows = m_cols = 0;
        m_pMat = nullptr;
    }
public:    
    T *operator[](size_t row)
    {
        assert(row < m_rows);
        return m_pMat[row];
    }
    T *operator[](string str)
    {
        return m_pMat[0];
    }
    T &operator()(size_t row, size_t col)
    {
        assert(row < m_rows && col < m_cols);
        // cout << &m_pMat[row][col] << endl;
        return m_pMat[row][col];
    }
    CMatrix<T> operator*(CMatrix<T> &other)
    {
        assert(GetCols() == other.GetRows()); // Validar dimensiones
        CMatrix<T> rpta(GetRows(), other.GetCols(), 0);
        CMatrix<T> &me = *this;
        for(auto row = 0; row < GetRows(); ++row)
        {   for(auto col = 0; col < other.GetCols(); ++col)
            {   rpta[row][col] = 0 ;
                for(auto i = 0 ; i < GetCols() ; ++i)
                    rpta[row][col] +=  me[row][i] * other[i][col];
            }
        }
        return rpta;
    }
    void help(size_t row, size_t col)
    {
        assert(row < m_rows && col < m_cols);
        cout << &m_pMat[row][col] << endl;
        cout <<  m_pMat[row][col] << endl;
    }
    ostream &print(ostream &os)
    {
        for(auto row = 0; row < m_rows; ++row)
        {   for(auto col = 0; col < m_cols; ++col)
                os << m_pMat[row][col] << " ";
            os << endl;
        } 
        os << endl;   
        return os;
    }
    size_t GetRows()
    {
        return m_rows;
    }
    size_t GetCols()
    {
        return m_cols;
    }
};

template <typename T>
ostream &operator<<(ostream &os, CMatrix<T> &mat)
{
    mat.print(os);
    return os;
}
#endif