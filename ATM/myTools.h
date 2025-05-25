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