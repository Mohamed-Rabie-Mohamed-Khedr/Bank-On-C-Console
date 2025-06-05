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
	std::string name, phone, id;
	bool readData()
	{
		std::fstream file("clients.txt", std::ios::in);
		std::string line;
		readString(id, "Enter Client ID: ");
		while (getline(file, line))
		{
			if (line.substr(0, line.find(",/,")) == id)
			{
				return false;
			}
		}
		file.close();

		readString(name, "Enter Client name: ");
		readNumber(age, "Enter Client age: ");
		readNumber(money, "Enter Client money: ");
		readString(phone, "Enter Client phone: ");
		return true;
	}
public:
	client()
	{
		age = 0;
		money = 0;
		name = "";
		phone = "";
		id = "";
	}
	std::string getInfo()
	{
		return encrypt(id + ",/," + name + ",/," + std::to_string(money) + ",/," + std::to_string(age) + ",/," + phone);
	}
	static bool addClient()
	{
		std::fstream file("clients.txt", std::ios::out | std::ios::app);
		client p;
		bool added = p.readData();
		if (added) file << p.getInfo() << "\n";
		file.close();
		return added;
	}
	std::string getInfoToShow()
	{
		return "ID: " + id + "\nName: " + name + "\nMoney: " + std::to_string(money) + "\nAge: " + std::to_string(age) + "\nPhone: " + phone;
	}
	static std::vector<client> getClientsFromFile()
	{
		std::vector<client> all;
		std::fstream file("clients.txt", std::ios::in);
		std::string line;
		size_t pos = 0;
		while (getline(file, line))
		{
			line = decrypt(line);
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
	static std::string findClient(std::string id)
	{
		std::vector<client> all = getClientsFromFile();
		for (size_t i = 0; i < all.size(); ++i)
		{
			if (all[i].id == id) return all[i].getInfoToShow();
		}
		return "";
	}
	static void findClient(std::string id, client& c)
	{
		std::vector<client> all = getClientsFromFile();
		for (size_t i = 0; i < all.size(); ++i)
		{
			if (all[i].id == id)
			{
				c = all[i];
				return;
			}
		}
	}
	static bool deleteClient(std::string id)
	{
		bool isDeleted = false;
		std::vector<client> all = getClientsFromFile();
		std::fstream file("clients.txt", std::ios::out);
		for (size_t i = 0; i < all.size(); ++i)
		{
			if (all[i].id != id) file << all[i].getInfo() + "\n";
			else isDeleted = true;
		}
		file.close();
		return isDeleted;
	}
	static bool updateClient(std::string id)
	{
		bool isUpdated = false;
		std::vector<client> all = getClientsFromFile();
		std::fstream file("clients.txt", std::ios::out);
		for (size_t i = 0; i < all.size(); ++i)
		{
			if (all[i].id == id)
			{
				client p;
				p.readData();
				all[i] = p;
				isUpdated = true;
			}
			file << all[i].getInfo() + "\n";
		}
		file.close();
		return isUpdated;
	}
	bool withdraw(int amount)
	{
		bool isWithdrawed = false;
		std::vector<client> all = client::getClientsFromFile();
		std::fstream file("clients.txt", std::ios::out);
		for (size_t i = 0; i < all.size(); ++i)
		{
			if (all[i].id == id && all[i].money >= amount)
			{
				money -= amount;
				file << getInfo() + "\n";
				isWithdrawed = true;
			}
			else file << all[i].getInfo() + "\n";
		}
		file.close();
		return isWithdrawed;
	}
	bool deposit(int amount)
	{
		bool isDeposited = false;
		std::vector<client> all = client::getClientsFromFile();
		std::fstream file("clients.txt", std::ios::out);
		for (size_t i = 0; i < all.size(); ++i)
		{
			if (all[i].id == id)
			{
				money += amount;
				file << getInfo() + "\n";
				isDeposited = true;
			}
			else file << all[i].getInfo() + "\n";
		}
		file.close();
		return isDeposited;
	}
	std::string getName() { return name; }
	unsigned int getMoney() { return money; }
};