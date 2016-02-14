// lab3.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

//static const int SIZE = 1;

struct SquareMatrix
{
	double **matrix;
	size_t size;

	SquareMatrix(size_t Size);
	SquareMatrix(const SquareMatrix &SquareMatrix);
	size_t getSize();
	void ReadFromFile(std::ifstream &fin);
	void Print();
	void Transpose();
	SquareMatrix operator*= (const double number);
	double &operator() (size_t i, size_t j);
	~SquareMatrix();
};

SquareMatrix Minor(SquareMatrix &matrix, const size_t x, const size_t y);
double Determinant(SquareMatrix &matrix);
SquareMatrix AdditionMatrix(SquareMatrix &matrix);
int IntSqrt(int number);
int ElementsCount(std::ifstream &fin);


SquareMatrix::SquareMatrix(size_t Size)
{
	size = Size;
	matrix = new double *[size];
	for (size_t i = 0; i < size; i++)
		matrix[i] = new double[size];
}

SquareMatrix::SquareMatrix(const SquareMatrix &Matrix)
{
	size = Matrix.size;
	matrix = new double *[size];
	for (size_t i = 0; i < size; i++)
	{
		matrix[i] = new double[size];
		for (size_t j = 0; j < size; j++)
			matrix[i][j] = Matrix.matrix[i][j];
	}
}

size_t SquareMatrix::getSize()
{
	return size;
}

void SquareMatrix::ReadFromFile(std::ifstream &fin)
{
	for (size_t i = 0; i < size; i++)
		for (size_t j = 0; j < size; j++)
		{
			double temp;
			fin >> temp;
			matrix[i][j] = temp;
		}
}

void SquareMatrix::Print()
{
	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = 0; j < size; j++)
			std::cout << std::fixed << std::setprecision(3) << matrix[i][j] << ' ';
		std::cout << std::endl;
	}
}

void SquareMatrix::Transpose()
{
	SquareMatrix Matrix = *this;
	for (size_t i = 0; i < size; i++)
		for (size_t j = 0; j < size; j++)
			matrix[i][j] = Matrix.matrix[j][i];
}

SquareMatrix SquareMatrix::operator*= (const double number)
{
	for (size_t i = 0; i < size; i++)
		for (size_t j = 0; j < size; j++)
			matrix[i][j] *= number;
	return *this;
}

double &SquareMatrix::operator() (size_t i, size_t j)
{
	return matrix[i][j];
}

SquareMatrix::~SquareMatrix()
{
	for (size_t i = 0; i < size; i++)
		delete[] matrix[i];
	delete[] matrix;
}

SquareMatrix Minor(SquareMatrix &matrix, const size_t x, const size_t y)
{
	size_t size = matrix.getSize();
	SquareMatrix minor(size - 1);
	
	size_t minorI = 0;
	for (size_t i = 0; i < size; i++)
	{
		size_t minorJ = 0;
		if (i != x)
		{
			for (size_t j = 0; j < size; j++)
				if (j != y)
				{
					minor(minorI, minorJ) = matrix(i, j);
					minorJ++;
				}
			minorI++;
		}
	}
	return minor;
}

double Determinant(SquareMatrix &matrix)
{
	size_t size = matrix.getSize();
	if (size == 1)
		return matrix(0, 0);
	double det = 0;
	double norm = 1.f;
	for (size_t i = 0; i < size; i++)
	{
		SquareMatrix minor = Minor(matrix, 0, i);
		det += norm * matrix(0, i) * Determinant(minor);
		norm = -norm;
	}
	return det;
}

SquareMatrix AdditionMatrix(SquareMatrix &matrix)
{
	size_t size = matrix.getSize();
	SquareMatrix addMat(size);

	double coef;
	for (size_t i = 0; i < size; i++)
		for (size_t j = 0; j < size; j++)
		{
			coef = (i + j) % 2 ? 1.0 : -1.0;
			SquareMatrix minor = Minor(matrix, i, j);
			addMat(i, j) = coef * Determinant(minor);
		}
	
	return addMat;
}

int IntSqrt(int number)
{
	for (int i = 0, iSqr = 0; iSqr <= number; i++, iSqr = i * i)
		if (iSqr == number)
			return i;
	return 0;
}

int ElementsCount(std::ifstream &fin)
{
	int count = 0;
	for (count; !fin.eof();)
	{
		double t;
		if (fin >> t)
			count++;
		else
			return 0;
	}
	return count;
}


int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		std::cout << "invalid parameters-format" << std::endl;
		std::cout << "enter <file-name>" << std::endl;
		return 1;
	}
	std::ifstream fin(argv[1], std::ios_base::in);

	if (!fin.is_open())
	{
		std::cout << "file can't be opened" << std::endl;
		return 2;
	}

	int count = ElementsCount(fin);
	if (!count)
	{
		std::cout << "invalid file-format" << std::endl;
		return 3;
	}

	int size = IntSqrt(count);
	if (!size)
	{
		std::cout << "invaild matrix-format" << std::endl;
		return 4;
	}
	fin.close();

	fin.open(argv[1], std::ios_base::in);

	SquareMatrix initMatrix(size);
	initMatrix.ReadFromFile(fin);
	initMatrix.Print();
	std::cout << std::endl;


	double det = Determinant(initMatrix);
	if (!det)
	{
		std::cout << "the determinant is 0" << std::endl;
		return 0;
	}

	SquareMatrix addMatrix = AdditionMatrix(initMatrix);
	addMatrix *= (1 / abs(det));

	addMatrix.Transpose();
	addMatrix.Print();
	std::cout << std::endl;


    return 0;
}