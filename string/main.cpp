#include <iostream>
#include <windows.h>
#include <string>
#include <limits>
#include <cctype>

bool IsOnlySpaces(std::string input);

void StartWordsWithUpperCase(std::string& input);

void PutDot(std::string& input);

bool FindWord(std::string input, std::string word);

bool IsCoincidenceSeparateWord(std::string input, std::string word, size_t position);

int main()
{
	SetConsoleCP(65001);
	SetConsoleOutputCP(65001);
	std::string input;
	std::string word;
	std::cout << "Введите предложение: ";
	std::getline(std::cin, input);

	while (input.empty() || IsOnlySpaces(input))
	{
		std::cout << "Пустая строка. Повторите ввод.\n";
		std::cout << "Введите предложение: ";
		std::getline(std::cin, input);
	}

	StartWordsWithUpperCase(input);
	PutDot(input);

	std::cout << "Результат: " << input << "\n";
	std::cout << "Введите слово для поиска: ";

	std::getline(std::cin, word);

	if (FindWord(input, word))
	{
		std::cout << "Слово найдено в предложении.\n";
	}
	else
	{
		std::cout << "Слово не найдено в предложении.\n";
	}

	return 0;
}

bool IsOnlySpaces(std::string input)
{
	for (int i = 0; i < input.length(); i++)
	{
		if (!std::isspace(static_cast<unsigned char>(input[i])))
			return false;
	}

	return true;
}

void StartWordsWithUpperCase(std::string& input)
{
	bool isSpace = true;

	for (int i = 0; i < input.length(); i++)
	{
		if (std::isspace(static_cast<unsigned char>(input[i])))
		{
			isSpace = true;
			continue;
		}

		if (isSpace)
		{
			input[i] = std::toupper(static_cast<unsigned char>(input[i]));
			isSpace = false;
		}
		else
		{
			input[i] = std::tolower(static_cast<unsigned char>(input[i]));
		}
	}
}

void PutDot(std::string& input)
{
	if (input.empty() || IsOnlySpaces(input))
		return;

	if (input.back() != '.')
	{
		input += '.';
	}
}

bool FindWord(std::string input, std::string word)
{
	if (input.empty() || IsOnlySpaces(input))
		return false;
	if (word.empty() || IsOnlySpaces(word))
		return false;

	for (int i = 0; i < input.length(); i++)
	{
		input[i] = std::tolower(static_cast<unsigned char>(input[i]));
	}

	for (int i = 0; i < word.length(); i++)
	{
		word[i] = std::tolower(static_cast<unsigned char>(word[i]));
	}

	size_t foundI = input.find(word);

	while (foundI != std::string::npos)
	{
		if (IsCoincidenceSeparateWord(input, word, foundI))
			return true;

		foundI = input.find(word, foundI + 1);
	}

	return false;
}

bool IsCoincidenceSeparateWord(std::string input, std::string word, size_t position)
{
	bool isStart = position == 0;
	bool isEnd = position + word.length() == input.length();
	bool isStartCorrect = isStart;
	bool isEndCorrect = isEnd;
	size_t startIndex = 0;
	size_t endIndex = position + word.length();

	if (!isStart)
		startIndex = position - 1;

	if (!isStart)
	{
		isStartCorrect = std::isspace(static_cast<unsigned char>(input[startIndex]))
			|| std::ispunct(static_cast<unsigned char>(input[startIndex]));
	}

	if (!isEnd)
	{
		isEndCorrect = std::isspace(static_cast<unsigned char>(input[endIndex]))
			||std::ispunct(static_cast<unsigned char>(input[endIndex]));
	}

	return isStartCorrect && isEndCorrect;
}