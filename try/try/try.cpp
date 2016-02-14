// lab3.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

static const int SIZE = 3;

struct SquareMatrix
{
	double **matrix;
	int size;

	SquareMatrix(int Size);
	SquareMatrix(const SquareMatrix &SquareMatrix);
	int getSize();
	void ReadFromFile(std::ifstream &fin);
	void Print();
	void PrintTransposed();
	SquareMatrix operator*= (const double number);
	double &operator() (int i, int j);
	~SquareMatrix();
};

SquareMatrix::SquareMatrix(int Size)
{
	std::cout << "constructor" << std::endl;
	size = Size;
	matrix = new double *[size];
	for (int i = 0; i < size; i++)
		matrix[i] = new double[size];
}

SquareMatrix::SquareMatrix(const SquareMatrix &Matrix)
{
	std::cout << "copy constructor" << std::endl;
	size = Matrix.size;
	matrix = new double *[size];
	for (int i = 0; i < size; i++)
	{
		matrix[i] = new double[size];
		for (int j = 0; j < size; j++)
			matrix[i][j] = Matrix.matrix[i][j];
	}
}

int SquareMatrix::getSize()
{
	return size;
}

void SquareMatrix::ReadFromFile(std::ifstream &fin)
{
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
		{
			double temp;
			fin >> temp;
			matrix[i][j] = temp;
		}
}

void SquareMatrix::Print()
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
			std::cout << std::fixed << std::setprecision(3) << matrix[i][j] << ' ';
		std::cout << std::endl;
	}
}

void SquareMatrix::PrintTransposed()
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
			std::cout << std::fixed << std::setprecision(3) << matrix[j][i] << ' ';
		std::cout << std::endl;
	}
}

SquareMatrix SquareMatrix::operator*= (const double number)
{
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			matrix[i][j] *= number;
	return *this;
}

double &SquareMatrix::operator() (int i, int j)
{
	return matrix[i][j];
}

SquareMatrix::~SquareMatrix()
{
	std::cout << "destructor" << std::endl;
	for (int i = 0; i < size; i++)
		delete[] matrix[i];
	delete[] matrix;
}



int main(int argc, char *argv[])
{
	if (argc != 1)
	{
		std::cout << "invalid arguments format" << std::endl;
		return 1;
	}
	std::ifstream fin(/*argv[1]*/"matrix.txt", std::ios_base::in);

	if (!fin.is_open())
	{
		std::cout << "file can't be opened";
		return 2;
	}

	SquareMatrix initMatrix(SIZE);
	initMatrix.ReadFromFile(fin);

	initMatrix.Print();
	std::cout << std::endl;
	initMatrix *= 5.0;
	initMatrix.PrintTransposed();

	return 0;
}