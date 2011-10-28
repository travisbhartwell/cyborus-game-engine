/**
 *  This file is part of "Paroxysm".
 *
 *  "Paroxysm" is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  "Paroxysm" is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with "Paroxysm".  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <iomanip>
using namespace std;

template<class T>
class Matrix
{
    public:
        Matrix();
        Matrix(const Matrix<T>& inMatrix);
        Matrix(int inRows, int inCols);
        Matrix(int inEdge);
        ~Matrix();

        int rows() const;
        int cols() const;
        int size() const;
        int lastRow() const;
        int lastCol() const;
        bool square() const;
        int toIndex(int inRow, int inCol) const;
        void set(int inRow, int inCol, T inValue);
        T determinant() const;
        Matrix<T> subMatrix(int inRow, int inCol, int inHeight, int inWidth);
        Matrix<T> minorMatrix(int inRow, int inCol) const;
        void transpose();
        const Matrix<T> transposed();

        Matrix<T>& operator=(const Matrix<T>& inMatrix);
        Matrix<T>& operator+=(const Matrix<T>& inMatrix);
        Matrix<T>& operator-=(const Matrix<T>& inMatrix);
        Matrix<T>& operator*=(const Matrix<T>& inMatrix);
        Matrix<T>& operator+=(const T inValue);
        Matrix<T>& operator-=(const T inValue);
        Matrix<T>& operator*=(const T inValue);
        Matrix<T>& operator/=(const T inValue);
        T& operator()(int inRow, int inCol);
        T operator()(int inRow, int inCol) const;
        T& operator[](int inIndex);
        T operator[](int inIndex) const;
        bool operator==(const Matrix<T>& inMatrix) const;
        bool operator!=(const Matrix<T>& inMatrix) const;
        const Matrix<T> operator+(const Matrix<T>& inMatrix) const;
        const Matrix<T> operator-(const Matrix<T>& inMatrix) const;
        const Matrix<T> operator*(const Matrix<T>& inMatrix) const;
        const Matrix<T> operator+(const T inValue) const;
        const Matrix<T> operator-(const T inValue) const;
        const Matrix<T> operator*(const T inValue) const;
        const Matrix<T> operator/(const T inValue) const;
        T* array();

    private:
        void copy(const Matrix<T>& inMatrix);
        T at(int inRow, int inCol) const;

        long mRows;
        long mCols;
        long mSize;
        T* mMatrix;
};

template<class T>
Matrix<T>::Matrix()
{
    // produces a square matrix
    mRows = 4;
    mCols = 4;
    mSize = mRows * mCols;
    mMatrix = new T[mSize];

    // default to identity matrix
    for (unsigned long i = 0; i < mSize; ++i)
        mMatrix[i] = (i % (mCols + 1) == 0 ? 1 : 0);
}

template<class T>
Matrix<T>::Matrix(int inRows, int inCols)
{
    mRows = inRows > 0 ? inRows : 1;
    mCols = inCols > 0 ? inCols : 1;
    mSize = mRows * mCols;
    mMatrix = new T[mSize];

    memset(mMatrix, 0, mSize * sizeof(T));
}

template<class T>
Matrix<T>::Matrix(int inEdge)
{
    // produces a square matrix
    mRows = inEdge > 0 ? inEdge : 1;
    mCols = mRows;
    mSize = mRows * mCols;
    mMatrix = new T[mSize];

    // default to identity matrix
    for (int i = 0; i < mSize; ++i)
        mMatrix[i] = (i % (mCols + 1) == 0 ? 1 : 0);
}

template<class T>
Matrix<T>::Matrix(const Matrix<T>& inMatrix)
{
    copy(inMatrix);
}

template<class T>
Matrix<T>::~Matrix()
{
    delete [] mMatrix;
}

template<class T>
inline int Matrix<T>::rows() const
{
    return mRows;
}

template<class T>
inline int Matrix<T>::cols() const
{
    return mCols;
}

template<class T>
inline int Matrix<T>::size() const
{
    return mSize;
}

template<class T>
inline int Matrix<T>::lastRow() const
{
    return mRows - 1;
}

template<class T>
inline int Matrix<T>::lastCol() const
{
    return mCols - 1;
}

template<class T>
bool Matrix<T>::square() const
{
    return mRows == mCols;
}

template<class T>
void Matrix<T>::copy(const Matrix<T>& inMatrix)
{
    mRows = inMatrix.mRows;
    mCols = inMatrix.mCols;
    mSize = inMatrix.mSize;
    mMatrix = new T[mSize];

    for (int i = 0; i < mSize; ++i) mMatrix[i] = inMatrix.mMatrix[i];
}

template<class T>
inline void Matrix<T>::set(int inRow, int inCol, T inValue)
{
    mMatrix[(inRow * mCols) + inCol] = inValue;
}

template<class T>
inline T Matrix<T>::at(int inRow, int inCol) const
{
    return mMatrix[(inRow * mCols) + inCol];
}

template<class T>
int Matrix<T>::toIndex(int inRow, int inCol) const
{
    if (inRow < 0 || inCol < 0) return 0;
    inRow %= mRows;
    inCol %= mCols;
    return (inRow * mCols) + inCol;
}

template<class T>
T Matrix<T>::determinant() const
{
    if (mRows != mCols)
    {
        return 0;
    }
    else if (mRows == 1)
    {
        return mMatrix[0];
    }
    else if (mRows == 2)
    {
        return (mMatrix[0] * mMatrix[3]) - (mMatrix[1] * mMatrix[2]);
    }

    T outValue = 0;

    for (int i = 0; i < mRows; ++i)
    {
        Matrix m = minorMatrix(0, i);
        int neg = ((i % 2 == 0) ? 1 : -1);
        outValue += neg * at(0, i) * m.determinant();
    }

    return outValue;
}

template<class T>
Matrix<T> Matrix<T>::subMatrix(int inRow, int inCol, int inHeight, int inWidth)
{
    int bottom = inRow + inHeight - 1;
    int right = inCol + inWidth - 1;

    if (inHeight < 1 || inWidth < 1 || inRow < 0 || bottom >= mRows || inCol < 0
        || right >= mCols)
        return Matrix(1, 1);

    Matrix<T> outMatrix(inHeight, inWidth);
    for (int i = 0; i < inHeight; ++i)
    {
        for (int j = 0; j < inWidth; ++j)
        {
            outMatrix(i, j) = at(i + inRow, j + inCol);
        }
    }

    return outMatrix;
}

template<class T>
Matrix<T> Matrix<T>::minorMatrix(int inRow, int inCol) const
{
    if (mRows != mCols || inRow < 0 || inRow >= mRows || inCol < 0
        || inCol >= mCols)
        return Matrix(1, 1);

    int p = 0;

    Matrix outMatrix(mRows - 1);

    for (int i = 0; i < mRows; ++i)
    {
        if (i != inRow)
        {
            int q = 0;
            for (int j = 0; j < mCols; ++j)
            {
                if (j != inCol)
                {
                    outMatrix(p, q) = at(i, j);
                    ++q;
                }
            }
            ++p;
        }
    }

    return outMatrix;
}

template<class T>
void Matrix<T>::transpose()
{
    if (mRows < 2 || mRows != mCols) return;
    for (int i = 0; i < mRows; ++i)
    {
        for (int j = i + 1; j < mCols; ++j)
        {
            T t = at(i, j);
            (*this)(i, j) = at(j, i);
            (*this)(j, i) = t;
        }
    }
}

template<class T>
const Matrix<T> Matrix<T>::transposed()
{
    Matrix<T> outMatrix(*this);
    outMatrix.transpose();
    return outMatrix;
}

template<class T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& inMatrix)
{
    if (this != &inMatrix)
    {
        delete [] mMatrix;
        copy(inMatrix);
    }
    return *this;
}

template<class T>
Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& inMatrix)
{
    if (mRows == inMatrix.mRows && mCols == inMatrix.mCols)
    {
        for (int i = 0; i < mSize; ++i) mMatrix[i] += inMatrix.mMatrix[i];
    }
    return *this;
}

template<class T>
Matrix<T>& Matrix<T>::operator+=(const T inValue)
{
    for (int i = 0; i < mSize; ++i) mMatrix[i] += inValue;
    return *this;
}

template<class T>
Matrix<T>& Matrix<T>::operator-=(const Matrix<T>& inMatrix)
{
    if (mRows == inMatrix.mRows && mCols == inMatrix.mCols)
    {
        for (int i = 0; i < mSize; ++i) mMatrix[i] -= inMatrix.mMatrix[i];
    }
    return *this;
}

template<class T>
Matrix<T>& Matrix<T>::operator-=(const T inValue)
{
    for (int i = 0; i < mSize; ++i) mMatrix[i] -= inValue;
    return *this;
}

template<class T>
Matrix<T>& Matrix<T>::operator*=(const Matrix<T>& inMatrix)
{
    if (mCols != inMatrix.mRows) return *this;
    Matrix<T> result = *this * inMatrix;
    delete [] mMatrix;
    copy(result);
    return *this;
}

template<class T>
Matrix<T>& Matrix<T>::operator*=(const T inValue)
{
    for (int i = 0; i < mSize; ++i) mMatrix[i] *= inValue;
    return *this;
}

template<class T>
Matrix<T>& Matrix<T>::operator/=(const T inValue)
{
    for (int i = 0; i < mSize; ++i) mMatrix[i] /= inValue;
    return *this;
}

template<class T>
inline T& Matrix<T>::operator()(int inRow, int inCol)
{
    return mMatrix[(inRow * mCols) + inCol];
}

template<class T>
T Matrix<T>::operator()(int inRow, int inCol) const
{
    if (inRow < 0 || inCol < 0) return mMatrix[0];

    inRow %= mRows;
    inCol %= mCols;
    return mMatrix[(inRow * mCols) + inCol];
}

template<class T>
inline T& Matrix<T>::operator[](int inIndex)
{
    return mMatrix[inIndex];
}

template<class T>
inline T Matrix<T>::operator[](int inIndex) const
{
    return mMatrix[inIndex];
}

template<class T>
const Matrix<T> Matrix<T>::operator+(const Matrix<T>& inMatrix) const
{
    if (mRows != inMatrix.mRows || mCols != inMatrix.mCols) return Matrix(1, 1);

    Matrix outMatrix(*this);
    for (int i = 0; i < mSize; ++i) outMatrix[i] += inMatrix[i];
    return outMatrix;
}

template<class T>
const Matrix<T> Matrix<T>::operator+(T inValue) const
{
    Matrix outMatrix(*this);
    for (int i = 0; i < mSize; ++i) outMatrix[i] += inValue;
    return outMatrix;
}

template<class T>
const Matrix<T> Matrix<T>::operator-(const Matrix<T>& inMatrix) const
{
    if (mRows != inMatrix.mRows || mCols != inMatrix.mCols) return Matrix(1, 1);

    Matrix outMatrix(*this);
    for (int i = 0; i < mSize; ++i) outMatrix[i] -= inMatrix[i];
    return outMatrix;
}

template<class T>
const Matrix<T> Matrix<T>::operator-(T inValue) const
{
    Matrix outMatrix(*this);
    for (int i = 0; i < mSize; ++i) outMatrix[i] -= inValue;
    return outMatrix;
}

template<class T>
const Matrix<T> Matrix<T>::operator*(const Matrix<T>& inMatrix) const
{
    if (mCols != inMatrix.mRows) return Matrix(1, 1);

    Matrix outMatrix(mRows, inMatrix.mCols);

    for (int i = 0; i < outMatrix.mRows; ++i)
    {
        for (int j = 0; j < outMatrix.mCols; ++j)
        {
            T value = 0;
            for (int k = 0; k < mCols; ++k)
            {
                value += (at(i, k) * inMatrix.at(k, j));
            }
            outMatrix(i, j) = value;
        }
    }

    return outMatrix;
}

template<class T>
const Matrix<T> Matrix<T>::operator*(T inValue) const
{
    Matrix outMatrix(*this);
    for (int i = 0; i < mSize; ++i) outMatrix[i] *= inValue;
    return outMatrix;
}

template<class T>
const Matrix<T> Matrix<T>::operator/(T inValue) const
{
    Matrix outMatrix(*this);
    for (int i = 0; i < mSize; ++i) outMatrix[i] /= inValue;
    return outMatrix;
}

template<class T>
bool Matrix<T>::operator==(const Matrix<T>& inMatrix) const
{
    if (mRows != inMatrix.mRows || mCols != inMatrix.mCols) return false;

    for (int i = 0; i < mSize; ++i)
    {
        if (at(i) != inMatrix.at(i)) return false;
    }

    return true;
}

template<class T>
bool Matrix<T>::operator!=(const Matrix<T>& inMatrix) const
{
    return !(*this == inMatrix);
}

template<class T>
T* Matrix<T>::array()
{
    return mMatrix;
}

template<class T>
ostream& operator<<(ostream& inStream, const Matrix<T>& inMatrix)
{
    inStream << setprecision(3);
    for (int i = 0; i < inMatrix.size(); ++i)
    {
        if (i % inMatrix.cols() == 0 && i > 0) inStream << endl;
        inStream << setw(8) << inMatrix.at(i);
    }

    inStream << endl;

    return inStream;
}

template<class T>
istream& operator>>(istream& inStream, Matrix<T>& inMatrix)
{
    int rows;
    int cols;
    inStream >> rows >> cols;
    inMatrix = Matrix<T>(rows, cols);

    for (int i = 0; i < inMatrix.size(); ++i) inStream >> inMatrix[i];

    return inStream;
}

#endif
