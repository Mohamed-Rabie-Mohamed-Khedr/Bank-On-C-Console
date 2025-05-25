#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "myTools.h"

struct client
{
private:
	short age;
	unsigned int money;
	std::string name, path = "..\\Bank On C++ Console\\clients.txt", phone, id;
	
public:
	std::string getInfo()
	{
		return id + ",/," + name + ",/," + std::to_string(money) + ",/," + std::to_string(age) + ",/," + phone;
	}
	std::string getInfoToShow()
	{
		return "ID: " + id + "\nName: " + name + "\nMoney: " + std::to_string(money) + "\nAge: " + std::to_string(age) + "\nPhone: " + phone;
	}
	std::vector<client> getClientsFromFile()
	{
		std::vector<client> all;
		std::fstream file(path, std::ios::in);
		std::string line;
		size_t pos = 0;
		while (getline(file, line))
		{
			client p;
			pos = line.find(",/,");
			p.id = line.substr(0, pos);
			line.erase(0, pos + 3);

			pos = line.find(",/,");
			p.name = line.substr(0, pos);
			line.erase(0, pos + 3);

			pos = line.find(",/,");
			p.money = atoi(line.substr(0, pos).c_str());
			line.erase(0, pos + 3);

			pos = line.find(",/,");
			p.age = atoi(line.substr(0, pos).c_str());
			line.erase(0, pos + 3);

			pos = line.find(",/,");
			p.phone = line.substr(0, pos);
			all.push_back(p);
		}
		file.close();
		return all;
	}
	bool withdraw(std::string id, int amount)
	{
		bool isWithdrawed = false;
		client p;
		std::vector<client> all = p.getClientsFromFile();
		std::fstream file(path, std::ios::out);
		for (size_t i = 0; i < all.size(); ++i)
		{
			if (all[i].id == id && all[i].money >= amount)
			{
				all[i].money -= amount;
				isWithdrawed = true;
			}
			file << all[i].getInfo() + "\n";
		}
		file.close();
		return isWithdrawed;
	}
	bool deposit(std::string id, int amount)
	{
		bool isDeposited = false;
		client p;
		std::vector<client> all = p.getClientsFromFile();
		std::fstream file(path, std::ios::out);
		for (size_t i = 0; i < all.size(); ++i)
		{
			if (all[i].id == id)
			{
				all[i].money += amount;
				isDeposited = true;
			}
			file << all[i].getInfo() + "\n";
		}
		file.close();
		return isDeposited;
	}
	std::string getName() { return name; }
	std::string getId() { return id; }
	unsigned int getMoney() { return money; }
	void setMoney(unsigned int m) { money = m; }
};