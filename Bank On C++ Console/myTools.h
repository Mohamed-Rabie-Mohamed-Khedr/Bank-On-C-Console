#pragma once
#pragma warning(disable : 4996)
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
static std::string getToday(bool h = false)
{
	time_t now = time(0);
	tm* ltm = localtime(&now);
	std::string date = std::to_string(1900 + ltm->tm_year) + "/" + std::to_string(1 + ltm->tm_mon) + "/" + std::to_string(ltm->tm_mday);
	if (h)
		date += " " + std::to_string(ltm->tm_hour) + ":" + std::to_string(ltm->tm_min) + ":" + std::to_string(ltm->tm_sec);
	return date;
}
void readString(std::string& str, std::string message)
{
	std::cout << message;
	std::getline(std::cin >> std::ws, str);
}
void printMenuName(std::string menuName, std::string userName)
{
	std::cout << "..........................................\n";
	std::cout << "\t" << menuName << "\n";
	std::cout << "..........................................\n\n";
	std::cout << "\tuser: " << userName << "\n";
	std::cout << "\tdate: " << getToday() << "\n\n";
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
std::string stringToLower(std::string str)
{
	for (int i = 0; i < str.length(); ++i)
	{
		str[i] = tolower(str[i]);
	}
	return str;
}