// fill.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"

const int MAX_SIZE = 100;

typedef std::vector<std::string> matrix;

struct Coor
{
	size_t m_x;
	size_t m_y;

	Coor()
	{

	}
	
	Coor(size_t x, size_t y)
	{
		m_x = x;
		m_y = y;
	}

	size_t x()
	{
		return m_x;
	}

	size_t y()
	{
		return m_y;
	}

	Coor operator+(Coor cell)
	{
		return { cell.x() + m_x, cell.y() + m_y };
	}

	bool IsInBound(Coor leftUpBound, Coor rightDownBound)
	{
		return m_x >= leftUpBound.x() && m_y >= leftUpBound.y() && m_x < rightDownBound.x() && m_y < rightDownBound.y();
	}
};

struct Field
{
	matrix m_matrix;
	size_t m_maxSize;
	int m_errorCode;
	std::queue <Coor> m_queue;

	Field(size_t maxSize)
	{
		m_errorCode = 0;
		m_maxSize = maxSize;
	}

	void ReadFromFile(std::string fileName)
	{
		std::ifstream inputFile(fileName, std::ios_base::in);
		if (!inputFile.is_open())
		{
			m_errorCode = 1;
			return;
		}

		std::string str;
		for (size_t i = 0; i < m_maxSize && std::getline(inputFile, str); i++)
		{
			if (str.size() > m_maxSize)
				str.erase(m_maxSize);
			m_matrix.push_back(str);
			for (size_t i = 0; i < str.size(); i++)
				if (str[i] == 'O')
					m_queue.push({ m_matrix.size() - 1, i });
		}
	}

	void AddCoorToQueue(Coor cell)
	{
		if (cell.IsInBound({ 0, 0 }, { m_matrix.size(), m_matrix[cell.x()].size()}) && m_matrix[cell.x()][cell.y()] == ' ')
			m_queue.push(cell);
	}

	void FillMatrix()
	{
		while (!m_queue.empty())
		{
			Coor cell = m_queue.front();
			m_queue.pop();
			if (m_matrix[cell.x()][cell.y()] != 'O')
				m_matrix[cell.x()][cell.y()] = '.';
			AddCoorToQueue(cell + Coor(-1, 0));
			AddCoorToQueue(cell + Coor(1, 0));
			AddCoorToQueue(cell + Coor(0, 1));
			AddCoorToQueue(cell + Coor(0, -1));
		}
	}

	void WriteToFile(std::string fileName)
	{
		std::ofstream outputFile(fileName, std::ios_base::out | std::ios_base::trunc);
		for (std::string str : m_matrix)
		{
			outputFile << str << std::endl;
		}
		if (!outputFile.flush())
			m_errorCode = 2;
	}

	int ReadFillWrite(std::string inputFileName, std::string outputFileName)
	{
		ReadFromFile(inputFileName);
		if (m_errorCode)
			return m_errorCode;
		FillMatrix();
		WriteToFile(outputFileName);
		return m_errorCode;
	}
};

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		std::cout << "invalid arguments format" << std::endl;
		std::cout << "enter <input name> <output file>";
		return 1;
	}

	Field field(MAX_SIZE);
	int errorCode = field.ReadFillWrite(argv[1], argv[2]);
	
	if (errorCode == 1)
	{
		std::cout << "file can't be opened" << std::endl;
		return 2;
	}
	else if (errorCode == 2)
	{
		std::cout << "an error occurred when writing outputFile" << std::endl;
		return 3;
	}

    return 0;
}

