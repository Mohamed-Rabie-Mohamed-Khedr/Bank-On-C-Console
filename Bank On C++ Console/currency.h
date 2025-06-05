#pragma once
#include <vector>
#include <fstream>
#include "myTools.h"
class currency
{
	std::string name = "", code = "", rateName = "";
	float rate = 0;
	currency() {}
public:
	currency(std::string name, std::string code, std::string rateName, float rate)
	{
		this->name = stringToLower(name);
		this->code = stringToLower(code);
		this->rateName = stringToLower(rateName);
		this->rate = rate;
	}
	std::string getInfo()
	{
		return name + "#//#" + code + "#//#" + rateName + "#//#" + std::to_string(rate);
	}
	std::string getInfoToShow()
	{
		return "Name: " + name + "\nCode: " + code + "\nRate Name: " + rateName + "\nRate: " + std::to_string(rate);
	}
	static std::string findByCode(std::string code)
	{
		code = stringToLower(code);
		std::vector<currency> currencies = getCurrenciesFromFile();
		for (int i = 0; i < currencies.size(); ++i)
		{
			if (currencies[i].code == code)
			{
				return currencies[i].getInfoToShow();
			}
		}
		return "";
	}
	static std::string findByName(std::string name)
	{
		name = stringToLower(name);
		std::vector<currency> currencies = getCurrenciesFromFile();
		for (int i = 0; i < currencies.size(); ++i)
		{
			if (currencies[i].name == name)
			{
				return currencies[i].getInfoToShow();
			}
		}
		return "";
	}
	static currency getCurrency(std::string code)
	{
		code = stringToLower(code);
		std::vector<currency> currencies = getCurrenciesFromFile();
		for (int i = 0; i < currencies.size(); ++i)
		{
			if (currencies[i].code == code)
			{
				return currencies[i];
			}
		}
		return currency();
	}
	bool isCurrencyExist(std::string rateCode)
	{
		rateCode = stringToLower(rateCode);
		std::vector<currency> currencies = getCurrenciesFromFile();
		for (int i = 0; i < currencies.size(); ++i)
		{
			if (currencies[i].code == rateCode)
			{
				return true;
			}
		}
		return false;
	}
	static std::vector<currency> getCurrenciesFromFile()
	{
		std::vector<currency> currencies;
		std::fstream file("Currencies.txt", std::ios::in);
		std::string line;
		while (getline(file, line))
		{
			std::string name = line.substr(0, line.find("#//#"));
			line.erase(0, line.find("#//#") + 4);
			std::string code = line.substr(0, line.find("#//#"));
			line.erase(0, line.find("#//#") + 4);
			std::string rateName = line.substr(0, line.find("#//#"));
			line.erase(0, line.find("#//#") + 4);
			float rate = std::stof(line);
			currencies.push_back(currency(name, code, rateName, rate));
		}
		file.close();
		return currencies;
	}
	void updateRate(float rate)
	{
		this->rate = rate;
		std::vector<currency> currencies = getCurrenciesFromFile();
		std::ofstream file("Currencies.txt", std::ios::out);
		for (int i = 0; i < currencies.size(); ++i)
		{
			if (currencies[i].getCode() == code)
				file << getInfo() << "\n";
			else file << currencies[i].getInfo() << "\n";
		}
		file.close();
	}
	std::string getCurrencyName() { return name; };
	std::string getCode() { return code; };
	std::string getRateName() { return rateName; };
	float getRate() { return rate; };
};