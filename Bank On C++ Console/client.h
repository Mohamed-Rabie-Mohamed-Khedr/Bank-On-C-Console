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
	std::string name, path, phone, id;
	bool readData()
	{
		std::fstream file(path, std::ios::in);
		std::string line;
		std::cout << "Enter id Client: ";
		std::cin >> id;
		while (getline(file, line))
		{
			if (line.substr(0, line.find(",/,")) == id)
			{
				return false;
			}
		}
		file.close();

		std::cout << "Enter Client name: ";
		std::getline(std::cin >> std::ws, name);
		readNumber(age, "Enter Client age: ");
		readNumber(money, "Enter Client money: ");
		std::cout << "Enter Client phone: ";
		std::cin >> phone;

	return true;
	}
public:
	client(std::string p)
	{
		path = p;
	}
	std::string getInfo()
	{
		return id + ",/," + name + ",/," + std::to_string(money) + ",/," + std::to_string(age) + ",/," + phone;
	}
	bool addClient()
	{
		std::fstream file(path, std::ios::out | std::ios::app);
		client p(path);
		bool added = p.readData();
		if (added) file << p.getInfo() + "\n";
		file.close();
		return added;
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
			client p(path);
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
	std::string findClient(std::string id)
	{
		std::vector<client> all = getClientsFromFile();
		for (size_t i = 0; i < all.size(); ++i)
		{
			if (all[i].id == id) return all[i].getInfoToShow();
		}
		return "";
	}
	bool deleteClient(std::string id)
	{
		bool isDeleted = false;
		std::vector<client> all = getClientsFromFile();
		std::fstream file(path, std::ios::out);
		for (size_t i = 0; i < all.size(); ++i)
		{
			if (all[i].id != id) file << all[i].getInfo() + "\n";
			else isDeleted = true;
		}
		file.close();
		return isDeleted;
	}
	bool updateClient(std::string id)
	{
		bool isUpdated = false;
		std::vector<client> all = getClientsFromFile();
		std::fstream file(path, std::ios::out);
		for (size_t i = 0; i < all.size(); ++i)
		{
			if (all[i].id == id)
			{
				client p(path);
				p.readData();
				all[i] = p;
				isUpdated = true;
			}
			file << all[i].getInfo() + "\n";
		}
		file.close();
		return isUpdated;
	}
	bool withdraw(std::string id, int amount)
	{
		bool isWithdrawed = false;
		client p(path);
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
		client p(path);
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
};