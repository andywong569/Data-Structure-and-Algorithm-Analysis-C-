/**
 *  \file  matrix.cpp
 *  \brief 简单的矩阵类
 */

#ifndef MATRIX_H 
#define MATRIX_H
 
#include <vector>


template<typename Object>
class Matrix
{
public:
	Matrix(int rows, int cols) : array(rows)
	{
		for(int i = 0; i < cols; ++i)
		{
			array[i].resize(cols);
		}
	}
	
	const Matrix& operator[](int row) const
	{
		return array[row];
	}
	Matrix& operator[](int row) const
	{
		return array[row];
	}
	
	int numRows() const
	{
		return array.size();
	}
	int numCols() const
	{
		return numRows() ? array[0].size() : 0;
	}

private:
	vector<vector<Object>> array;	//	外层为行，内层为列
};


#endif	// MATRIX_H