#ifndef __MATRIX_H__  
#define __MATRIX_H__ 

#include <iostream>
using namespace std;

template <typename T, typename F>
class CMatrix
{
private:
    size_t m_rows = 0, m_cols = 0;
    T **m_pMat = nullptr;
public:
    //using TypeFunc = T (*)(size_t, size_t);
    CMatrix(size_t rows = 0, size_t cols = 0, T val = 0)
    {
        create(rows, cols, val);
    }
    CMatrix(size_t rows, size_t cols, F ope)
    {
        create(rows, cols, ope);
    }
    /*
    */
    CMatrix(CMatrix<T,F> *&other)
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
             //if (i < m_rows - 1) {(m_pMat[i] + m_cols) = m_pMat[i+1];}
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
    void create(size_t rows, size_t cols, F ope)
    {
        destroy();
        m_rows = rows;  m_cols = cols;
        m_pMat = new T *[m_rows];
        for(auto i = 0; i < m_rows; ++i)
        {    m_pMat[i]  = new T[m_cols];
             //if (i < m_rows - 1) {(m_pMat[i] + m_cols) = m_pMat[i+1];}
             //if (i > 0) { &m_pMat[i-1][m_cols - 1] = m_pMat[i];   }
             // *(m_pMat +i ) = new T[m_cols];
        }
        for(auto row = 0; row < m_rows; ++row)
            for(auto col = 0; col < m_cols; ++col)
            {
                    ope.plus2 = m_cols*row;
                     m_pMat[row][col] = ope(row,col);
            }
    }
    /*
    */
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
    size_t GetRows()
    {   return m_rows;   }
    size_t GetCols()
    {   return m_cols;   }
    //iterator begin() { iterator iter(this, m_pMat[0][0]);    return iter;    }
    //iterator end()   { iterator iter(this, nullptr);    return iter;    }
    CMatrix<T,F> operator*(CMatrix<T,F> &other)
    {
        CMatrix<T,F> &me = *this;
        assert(me.GetCols() == other.GetRows()); // Validar dimensiones
        CMatrix<T,F> rpta(GetRows(), other.GetCols(), 0);
        for(auto row = 0; row < GetRows(); ++row)
        {   for(auto col = 0; col < other.GetCols(); ++col)
            {   rpta[row][col] = 0 ;
                for(auto i = 0 ; i < GetCols() ; ++i)
                    rpta[row][col] +=  me[row][i] * other[i][col];
            }
        }
        //cout << rpta;
        return rpta;
    }
    CMatrix<T,F> operator+(CMatrix<T,F> &other)
    {
        CMatrix<T,F> &me = *this;
        assert(me.GetRows() == other.GetRows() && me.GetCols() == other.GetCols());
        CMatrix<T,F> rpta(GetRows(), GetCols(), 0);
        //rpta = other;
        /*
        vector<size_t> los_indices(m_rows);
        //iota(los_indices.begin(),los_indices.end(),1);
        //fill(los_indices.begin(), los_indices.end(), [](size_t i){return i;});
        //vector<size_t> indices(m_rows,0);
        //for_each(los_indices.begin(),los_indices.end(),[](size_t &i,CMatrix<T> &me,CMatrix<T> &rpta){transform(me[i].begin(),me[i].end(),rpta[i].begin(),rpta[i].end(),plus<T>{});});
        //transform(me,rpta,plus<T>{});
        //transform(me[0],rpta[0],[](T &e1,T &e2){return (e1 + e2);});
        //ransform(me.begin(),me.end(),rpta.begin(),rpta.end(),[](T &e1, T &e2){return e1 + e2;})

        */
        // De esta manera no
        for (auto row = 0; row < GetRows(); ++row)
            for (auto col = 0; col < GetCols(); ++col)
                //rpta[row][col] = me[row][col] + other[row][col];
                rpta[row][col] = suma_elem (me[row][col] , other[row][col]);
        
        return rpta;
    }
    T suma_elem(T &e1, T &e2)
    {
        return e1 + e2;
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
};

template <typename T, typename F>
ostream &operator<<(ostream &os, CMatrix<T,F> &mat)
{
    mat.print(os);
    return os;
}
#endif