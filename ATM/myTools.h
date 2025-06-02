#pragma once
#include <iostream>
#include <string>
template <typename T>
void readNumber(T& num, std::string message)
{
	std::cout << message;
	std::cin >> num;
	while (std::cin.fail())
	{
		std::cout << message;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin >> num;
	}
}
std::string encrypt(std::string word, short key = 5)
{
	std::string wordCrypt = "";
	for (int i = 0; i < word.length(); ++i)
	{
		wordCrypt += word[i] - key;
	}
	return wordCrypt;
}
std::string decrypt(std::string word, short key = 5)
{
	std::string wordDecrypt = "";
	for (int i = 0; i < word.length(); ++i)
	{
		wordDecrypt += word[i] + key;
	}
	return wordDecrypt;
}