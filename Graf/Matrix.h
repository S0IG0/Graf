#pragma once
#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <ostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <initializer_list>

template <typename T>
class Matrix
{
public:
	Matrix(size_t n);
	Matrix(T** matrix, size_t n);
	Matrix(Matrix<T>& matrix);
	Matrix(std::initializer_list<std::initializer_list<T>> matrix);
	virtual ~Matrix();

	size_t size();
	T* operator[] (size_t index);

protected:
	size_t n;
	T** matrixArray;
};

#endif // !_MATRIX_H_

template<typename T>
Matrix<T>::Matrix(size_t n) : n(n)
{
	matrixArray = new T * [n];
	for (size_t i = 0; i < n; i++)
	{
		matrixArray[i] = new T[n];
		for (size_t j = 0; j < n; j++)
		{
			matrixArray[i][j] = T();
		}
	}
}

template<typename T>
inline Matrix<T>::Matrix(T** matrix, size_t n) : n(n)
{
	matrixArray = new T * [n];
	for (size_t i = 0; i < n; i++)
	{
		matrixArray[i] = new T[n];
		for (size_t j = 0; j < n; j++)
		{
			matrixArray[i][j] = matrix[i][j];
		}
	}
}

template<typename T>
Matrix<T>::Matrix(Matrix<T>& matrix)
{
	n = matrix.n;
	matrixArray = new T * [n];
	for (size_t i = 0; i < n; i++)
	{
		matrixArray[i] = new T[n];
		for (size_t j = 0; j < n; j++)
		{
			matrixArray[i][j] = matrix[i][j];
		}
	}
}

template<typename T>
inline Matrix<T>::Matrix(std::initializer_list<std::initializer_list<T>> matrix)
{
	n = matrix.size();
	matrixArray = new T * [n];

	auto iteratorArray = matrix.begin();

	for (size_t i = 0; i < n; i++)
	{
		auto iteratorItems = (*iteratorArray).begin();
		matrixArray[i] = new T[n];
		for (size_t j = 0; j < n; j++)
		{
			matrixArray[i][j] = *iteratorItems;
			iteratorItems++;
		}
		iteratorArray++;
	}
}


template<typename T>
Matrix<T>::~Matrix()
{
	for (size_t i = 0; i < n; i++)
	{
		delete[] matrixArray[i];
	}
	delete[] matrixArray;
}

template<typename T>
inline size_t Matrix<T>::size()
{
	return n;
}

template<typename T>
inline T* Matrix<T>::operator[](size_t index)
{
	return matrixArray[index];
}

namespace std
{
	template<typename T>
	string to_string(Matrix<T>& matrix)
	{
		stringstream stream;
		size_t n = matrix.size();
		size_t maxWidth = 1;

		for (size_t i = 0; i < n; i++)
		{
			for (size_t j = 0; j < n; j++)
			{
				size_t tempWidth = to_string(matrix[i][j]).size();
				if (tempWidth > maxWidth)
				{
					maxWidth = tempWidth;
				}
			}
		}

		stream << "{";
		for (size_t i = 0; i < n; i++)
		{
			if (i == 0)
			{
				stream << "{";
			}
			else
			{
				stream << " {";
			}
			for (size_t j = 0; j < n; j++)
			{
				stream << setw(maxWidth + 1) << matrix[i][j];
				if (j != (n - 1))
				{
					stream << ",";
				}
			}
			if (i != (n - 1))
			{
				stream << "},\n";
			}
		}
		stream << "}}";

		return stream.str();
	}
}
template<typename T>
std::ostream& operator<< (std::ostream& ostream, Matrix<T>& matrix)
{
	ostream << std::to_string(matrix);

	return ostream;
}