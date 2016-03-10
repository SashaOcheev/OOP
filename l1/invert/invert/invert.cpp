// lab3.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

typedef std::valarray <std::valarray <double> > MatrixOfDouble;

struct SquareMatrix
{
	MatrixOfDouble m_matrix;

	SquareMatrix(size_t size);
	size_t GetSize()const;
	void ReadFromFile(std::ifstream &inputFile);
	void Print()const;
	void Transpose();
	SquareMatrix operator*= (const double number);
	double &operator() (size_t i, size_t j);
	~SquareMatrix();
};

SquareMatrix Minor(SquareMatrix &matrix, const size_t x, const size_t y);
double Determinant(SquareMatrix &matrix);
SquareMatrix AdditionMatrix(SquareMatrix &matrix);
int IntSqrt(int number);
int CountUpItems(std::ifstream &fin);
int InputFilePreview(std::string fileName, size_t &size);


SquareMatrix::SquareMatrix(size_t size)
{
	m_matrix.resize(size);
	for (size_t i = 0; i < size; i++)
		m_matrix[i].resize(size);
}

size_t SquareMatrix::GetSize()const
{
	return m_matrix.size();
}

void SquareMatrix::ReadFromFile(std::ifstream &inputFile)
{
	for (size_t i = 0; i < m_matrix.size(); i++)
		for (size_t j = 0; j < m_matrix[i].size(); j++)
		{
			double temp;
			inputFile >> temp;
			m_matrix[i][j] = temp;
		}
}

void SquareMatrix::Print()const
{
	for (size_t i = 0; i < m_matrix.size(); i++)
	{
		for (size_t j = 0; j < m_matrix[i].size(); j++)
			std::cout << std::fixed << std::setprecision(3) << m_matrix[i][j] << ' ';
		std::cout << std::endl;
	}
}

void SquareMatrix::Transpose()
{
	SquareMatrix matrixCopy = *this;
	for (size_t i = 0; i < m_matrix.size(); i++)
		for (size_t j = 0; j < m_matrix[i].size(); j++)
			m_matrix[i][j] = matrixCopy(j, i);
}

SquareMatrix SquareMatrix::operator*= (const double number)
{
	for (size_t i = 0; i < m_matrix.size(); i++)
		for (size_t j = 0; j < m_matrix[i].size(); j++)
			m_matrix[i][j] *= number;
	return *this;
}

double &SquareMatrix::operator() (size_t i, size_t j)
{
	return m_matrix[i][j];
}

SquareMatrix::~SquareMatrix()
{

}

SquareMatrix Minor(SquareMatrix &matrix, const size_t x, const size_t y)
{
	size_t size = matrix.GetSize();
	SquareMatrix minor(size - 1);

	for (size_t i = 0, minorI = 0; i < size; i++)
		if (i != x)
		{
			for (size_t j = 0, minorJ = 0; j < size; j++)
				if (j != y)
				{
					minor(minorI, minorJ) = matrix(i, j);
					minorJ++;
				}
			minorI++;
		}
	return minor;
}

double Determinant(SquareMatrix &matrix)
{
	size_t size = matrix.GetSize();
	if (size == 1)
		return matrix(0, 0);
	double det = 0;
	for (size_t j = 0; j < size; j++)
	{
		double coef = (0 + j) % 2 == 0 ? 1.0 : -1.0;
		det += coef * matrix(0, j) * Determinant(Minor(matrix, 0, j));
	}
	return det;
}

SquareMatrix AdditionMatrix(SquareMatrix &matrix)
{
	size_t size = matrix.GetSize();
	SquareMatrix addMat(size);
	for (size_t i = 0; i < size; i++)
		for (size_t j = 0; j < size; j++)
			addMat(i, j) = Determinant(Minor(matrix, i, j));
	if (size == 1)
		addMat(0, 0) = 1;
	for (size_t i = 0; i < size; i++)
		for (size_t j = 0; j < size; j++)
			addMat(i, j) *= (i + j) % 2 == 0 ? 1.0 : -1.0;

	return addMat;
}

int IntSqrt(int number)
{
	for (int i = 0, iSqr = 0; iSqr <= number; i++, iSqr = i * i)
		if (iSqr == number)
			return i;
	return 0;
}

int CountUpItems(std::ifstream &fin)
{
	int count = 0;
	for (count; !fin.eof();)
	{
		double t;
		if (fin >> t)
			count++;
		else
			return count;
	}
	return count;
}

int InputFilePreview(std::string fileName, size_t &size)
{
	std::ifstream fin(fileName, std::ios_base::in);

	if (!fin.is_open())
	{
		std::cout << "file can't be opened" << std::endl;
		return 2;
	}

	int count = CountUpItems(fin);
	if (!count)
	{
		std::cout << "invalid file format" << std::endl;
		return 3;
	}

	size = size_t(IntSqrt(count));
	if (!size)
	{
		std::cout << "invaild matrix format" << std::endl;
		return 4;
	}

	return 0;
}


int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		std::cout << "invalid parameters format" << std::endl;
		std::cout << "enter <file name>" << std::endl;
		return 1;
	}

	size_t size = 0;
	int errorCode = InputFilePreview(argv[1], size);
	if (errorCode)
		return errorCode;

	std::ifstream inputFile(argv[1], std::ios_base::in);

	SquareMatrix initMatrix(size);
	initMatrix.ReadFromFile(inputFile);

	double det = Determinant(initMatrix);
	if (!det)
	{
		std::cout << "the determinant is 0" << std::endl;
		return 0;
	}

	SquareMatrix addMatrix = AdditionMatrix(initMatrix);
	addMatrix *= (1 / det);
	addMatrix.Transpose();
	addMatrix.Print();

	return 0;
}