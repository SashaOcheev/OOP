// lab1.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

typedef std::map<std::string, std::string> StringStringMap;
typedef std::pair<std::string, std::string> StringStringPair;

const std::string EXIT_TAG = "...";
const std::string BEGIN_TAG = "<begin>";
const std::string END_TAG = "<end>";

/*class Dictionary
{
public:
	StringStringMap::iterator Begin();
	StringStringMap::iterator End();

	bool IsIncluded(std::string key);
	StringStringMap::iterator Find();
	void Add(StringStringPair);

private:
	StringStringMap m_dictionary;
};

StringStringMap::iterator Dictionary::Begin()
{
	return m_dictionary.begin();
}

StringStringMap::iterator Dictionary::End()
{
	return m_dictionary.end();
}

bool Dictionary::IsIncluded(std::string key)
{
	return m_dictionary.find(key) != End();
}

void Dictionary::Add(StringStringPair pair)
{
	m_dictionary.insert(pair);
}*/

bool IsEnglishString(std::string const& str)
{
	return std::all_of(str.cbegin(), str.cend(),
		[](const char ch) { return ch == ' ' || ch >= 'A' && ch <= 'Z' || ch >= 'a' && ch <= 'z'; });
}

bool IsRussianString(std::string const& str)
{
	return std::all_of(str.cbegin(), str.cend(),
		[](const char ch) { return ch == ' ' || ch > 'А' && ch <= 'Я' || ch >= 'а' && ch <= 'я'; });
}

StringStringMap ReadDictionaryFromFile(std::ifstream &file)
{
	StringStringMap dictionary;
	if (!file.is_open())
		return dictionary;

	std::string key;
	std::string val;
	while (!file.eof())
	{
		while (key != BEGIN_TAG)
			std::getline(file, key);
		std::getline(file, key);
		if (key != BEGIN_TAG && key != END_TAG)
		{
			std::getline(file, val);
			if (val == BEGIN_TAG)
				key = BEGIN_TAG;
			else if (val != END_TAG)
				dictionary[key] = val;
		}
	}
	return dictionary;
}

bool ProcessRequest(StringStringMap &dictionary, bool &wasChanges)
{
	std::string key;
	std::string val;
	StringStringMap::iterator finded;

	std::cout << "enter finded word" << std::endl;
	std::cin >> key;
	if (key == EXIT_TAG)
		return false;
	if (!key.empty() && IsEnglishString(key))
	{
		finded = dictionary.find(key);
		if (finded != dictionary.end())
			std::cout << finded->second << std::endl;
		else
		{
			std::cout << "enter translation or empty string to refuse" << std::endl;
			std::cin >> val;
			if (val == EXIT_TAG)
				return false;
			if (!val.empty())
			{
				if (IsRussianString(val))
				{
					dictionary[key] = val;
					wasChanges = true;
				}
				else
				{
					std::cout << "finded word must be russian or empty" << std::endl;
				}
			}
		}
	}
	else
	{
		std::cout << "finded word must be english and not empty" << std::endl;
	}
	return true;
}

bool WasChanges(StringStringMap &dictionary)
{
	bool wasChanges = false;
	std::string key;
	std::string val;
	while (ProcessRequest(dictionary, wasChanges))
		;
	return wasChanges;
}

void WriteDictionaryToFile(std::ofstream &file, StringStringMap const& dictionary)
{
	for (StringStringMap::const_iterator it = dictionary.begin(); it != dictionary.end(); it++)
	{
		file << BEGIN_TAG << std::endl;
		file << it->first << std::endl;
		file << it->second << std::endl;
		file << END_TAG << std::endl;
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

