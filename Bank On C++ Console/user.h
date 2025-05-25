#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
struct user
{
	std::string name, password;
	char addClient, showAllClients, findClient, deleteClient, updateClient, financialTransactions, usersControl;

	bool readData()
	{
		std::fstream file("users.txt", std::ios::oct | std::ios::app);
		std::string line;
		std::cout << "Enter user name: ";
		std::getline(std::cin >> std::ws, name);
		std::cout << "Enter user password: ";
		std::getline(std::cin >> std::ws, password);
		size_t pos = 0;
		while (getline(file, line))
		{
			pos = line.find(",/,");
			if (line.substr(0, pos) == name && line.substr(pos + 3, line.find(",/,", pos + 3)) == password)
			{
				return false;
			}
		}
		std::cout << "\nUser permissions: \n";
		char choice = '0';

		std::cout << "Allow addition Client? (y/n): "; std::cin >> choice;
		addClient = (choice == 'y' || choice == 'Y') ? 'y' : 'n';

		std::cout << "Allow showing all Clients? (y/n): "; std::cin >> choice;
		showAllClients = (choice == 'y' || choice == 'Y') ? 'y' : 'n';

		std::cout << "Allow finding Client? (y/n): "; std::cin >> choice;
		findClient = (choice == 'y' || choice == 'Y') ? 'y' : 'n';

		std::cout << "Allow deleting Client? (y/n): "; std::cin >> choice;
		deleteClient = (choice == 'y' || choice == 'Y') ? 'y' : 'n';

		std::cout << "Allow updating Client? (y/n): "; std::cin >> choice;
		updateClient = (choice == 'y' || choice == 'Y') ? 'y' : 'n';

		std::cout << "Allow financial transactions? (y/n): "; std::cin >> choice;
		financialTransactions = (choice == 'y' || choice == 'Y') ? 'y' : 'n';

		std::cout << "Allow users control? (y/n): "; std::cin >> choice;
		usersControl = (choice == 'y' || choice == 'Y') ? 'y' : 'n';
	}
	std::string getInfo()
	{
		return name + ",/," + password + ",/," + addClient + showAllClients + findClient
		+ deleteClient + updateClient + financialTransactions + usersControl;
	}
	static bool addUser()
	{
		std::fstream file("users.txt", std::ios::out | std::ios::app);
		user u;
		bool added = u.readData();
		if (added) file << u.getInfo() + "\n";
		file.close();
		return added;
	}
	std::string getInfoToShow()
	{
		return "Name: " + name + "\nPassword: " + password +
			"\nAllow addition Client " + addClient + "\nAllow showing all Clients " + showAllClients +
			"\nAllow finding Client " + findClient + "\nAllow deleting Client " + deleteClient +
			"\nAllow updating Client " + updateClient + "\nAllow financial transactions " +
			financialTransactions + "\nAllow users control " + usersControl;
	}
	static std::vector<user> getUsersFromFile()
	{
		std::vector<user> all;
		std::fstream file("users.txt", std::ios::in);
		std::string line;
		size_t pos = 0;
		while (getline(file, line))
		{
			user u;
			pos = line.find(",/,");
			u.name = line.substr(0, pos);
			pos += 3;
			u.password = line.substr(pos, line.find(",/,", pos) - pos);

			pos += u.password.length() + 3;
			u.addClient = line[pos++];
			u.showAllClients = line[pos++];
			u.findClient = line[pos++];
			u.deleteClient = line[pos++];
			u.updateClient = line[pos++];
			u.financialTransactions = line[pos++];
			u.usersControl = line[pos];
			all.push_back(u);
		}
		file.close();
		return all;
	}
	static std::string findUser(std::string name)
	{
		std::vector<user> all = getUsersFromFile();
		for (size_t i = 0; i < all.size(); ++i)
		{
			if (all[i].name == name) return all[i].getInfoToShow();
		}
		return "";
	}
	static bool deleteUser(std::string name)
	{
		bool isDeleted = false;
		std::vector<user> all = getUsersFromFile();
		std::fstream file("users.txt", std::ios::out);
		for (size_t i = 0; i < all.size(); ++i)
		{
			if (all[i].name != name) file << all[i].getInfo() + "\n";
			else isDeleted = true;
		}
		file.close();
		return isDeleted;
	}
	static bool updateUser(std::string name)
	{
		bool isUpdated = false;
		std::vector<user> all = getUsersFromFile();
		std::fstream file("users.txt", std::ios::out);
		for (size_t i = 0; i < all.size(); ++i)
		{
			if (all[i].name == name)
			{
				user u;
				u.readData();
				all[i] = u;
				isUpdated = true;
			}
			file << all[i].getInfo() + "\n";
		}
		file.close();
		return isUpdated;
	}
};