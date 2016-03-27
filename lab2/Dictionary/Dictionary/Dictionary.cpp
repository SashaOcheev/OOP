// lab1.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <functional>

typedef std::map<std::string, std::string> StringStringMap;
typedef std::pair<std::string, std::string> StringStringPair;

const std::string EXIT_TAG = "...";

class CDictionary
{
public:
	CDictionary() = default;
	CDictionary(std::ifstream & file);
	void BringToStream(std::ostream &stream);

private:
	StringStringMap m_dictionary;
};

CDictionary::CDictionary(std::ifstream & file)
{
	if (!file.is_open())
		return;

	std::string key;
	std::string val;
	while (!file.eof())
	{
		std::getline(file, key);
		std::getline(file, val);
		m_dictionary[key] = val;
	}
}

void CDictionary::BringToStream(std::ostream &stream)
{
	for (StringStringMap::iterator it = m_dictionary.begin(); it != m_dictionary.end(); it++)
	{
		stream << it->first << std::endl;
		stream << it->second << std::endl;
	}
}


int main(int argc, char *argv[])
{
	setlocale(LC_ALL, "Russian");
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	if (argc != 2)
	{
		std::cout << "invalid input format" << std::endl;
		std::cout << "enter <dictionary file>" << std::endl;
		return 1;
	}

	std::ifstream dictionaryFile(argv[1], std::ios_base::in);
	auto dictionary = ReadDictionaryFromFile(dictionaryFile);
	dictionaryFile.close();

	if (WasChanges(dictionary))
	{
		std::cout << "Would you save the changes? (y/n)" << std::endl;
		std::string flag;
		std::cin >> flag;
		std::cout << std::endl;
		if (flag == "y")
		{
			std::ofstream dictionaryFile(argv[1], std::ios_base::out | std::ios_base::trunc);
			WriteDictionaryToFile(dictionaryFile, dictionary);
			if (!dictionaryFile.flush())
			{
				std::cout << "an error occurred when writing outputFile" << std::endl;
				return 2;
			}
		}
	}

	return 0;
}

