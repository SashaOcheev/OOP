// lab3.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

static const int SIZE = 3;

void ReadMatrix(double **matrix, std::ifstream &fin, const int size)
{
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
		{
			double temp;
			fin >> temp;
			matrix[i][j] = temp;
		}
}

void PrintMatrix(double **matrix, const int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
			std::cout << std::fixed << std::setprecision(3) << matrix[i][j] << ' ';
		std::cout << std::endl;
	}
}

void DestroyMat(const int size, double **matrix)
{
	for (int i = 0; i < size; i++)
		delete[] matrix[i];
	delete[] matrix;
}

double **MatMinor(const int size, double **matrix, const int x, const int y)
{
	double **minor = new double *[size - 1];
	for (int i = 0; i < size - 1; i++)
		minor[i] = new double[size - 1];
	
	int minorI = 0;
	for (int i = 0; i < size; i++)
	{
		int minorJ = 0;
		if (i != x)
		{
			for (int j = 0; j < size; j++)
				if (j != y)
				{
					minor[minorI][minorJ] = matrix[i][j];
					minorJ++;
				}
			minorI++;
		}
	}
	return minor;
}

double MatDet(const int size, double **matrix)
{
	if (size == 1)
		return matrix[0][0];
	double det = 0;
	double norm = 1.f;
	for (int i = 0; i < size; i++)
	{
		double **minor = MatMinor(size, matrix, 0, i);
		det += norm * matrix[0][i] * MatDet(size - 1, minor);
		DestroyMat(size - 1, minor);
		norm = -norm;
	}
	return det;
}

double **AdditionMat(const int size, double **matrix)
{
	double **additionMat = new double *[size];
	for (int i = 0; i < size; i++)
		additionMat[i] = new double[size];

	double coef = -1.0;
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
		{
			coef = -coef;
			double **minor = MatMinor(size, matrix, i, j);
			additionMat[i][j] = coef * MatDet(size - 1, minor);
			DestroyMat(size - 1, minor);
		}
	
	return additionMat;
}

void PrintTransposedMat(const int size, double **matrix)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
			std::cout << std::fixed << std::setprecision(3) << matrix[j][i] << ' ';
		std::cout << std::endl;
	}
}

void MultOnConst(const int size, double **matrix, const double number)
{
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			matrix[i][j] *= number;
}

int main(int argc, char *argv[])
{
	if (argc != 1)
	{
		std::cout << "invalid input format" << std::endl;
		return 1;
	}
	std::ifstream fin(/*argv[1]*/"matrix.txt", std::ios_base::in);

	if (!fin.is_open())
	{
		std::cout << "file can't be opened";
		return 2;
	}

	double **initMatrix = new double *[SIZE];
	for (int i = 0; i < SIZE; i++)
		initMatrix[i] = new double[SIZE];

	ReadMatrix(initMatrix, fin, SIZE);

	double det = MatDet(SIZE, initMatrix);
	if (!det)
	{
		std::cout << "the determinant of the matrix equils 0" << std::endl;
		DestroyMat(SIZE, initMatrix);
		return 0;
	}

	double **addMatrix = AdditionMat(SIZE, initMatrix);
	MultOnConst(SIZE, addMatrix, 1 / abs(det));

	PrintMatrix(initMatrix, SIZE);
	std::cout << std::endl;
	PrintTransposedMat(SIZE, addMatrix);

	DestroyMat(SIZE, initMatrix);
	DestroyMat(SIZE, addMatrix);

    return 0;
}