#pragma once
#include "usersControlMenu.h"

void addClient()
{
	if (currentUser.addClient == 'n')
	{
		std::cout << "\nYou Don't Have Permission!\n";
		system("pause");
	}
	else
	{
		char choice = 'y';
		do
		{
			system("cls");
			printMenuName("Add Clients Menu", currentUser.name);
			bool added = client::addClient();
			if (!added)
				std::cout << "\nI am sorry, ID Client Already Exists!\n";
			else std::cout << "\nClient Added Successfully!\n";

			std::cout << "Do you want to add another Client? (y/n): ";
			std::cin >> choice;
		} while (choice != 'n' && choice != 'N');
	}
}
void showAllClients()
{
	if (currentUser.showAllClients == 'n')
	{
		std::cout << "\nYou Don't Have Permission!\n";
		system("pause");
	}
	else
	{
		system("cls");
		printMenuName("All Clients Menu", currentUser.name);
		std::vector<client> all = client::getClientsFromFile();
		for (size_t i = 0; i < all.size(); ++i)
		{
			std::cout << all[i].getInfoToShow() << "\n..........\n";
		}
		system("pause");
	}
}
void findClient()
{
	if (currentUser.findClient == 'n')
	{
		std::cout << "\nYou Don't Have Permission!\n";
		system("pause");
	}
	else
	{
		system("cls");
		printMenuName("Find Client", currentUser.name);
		std::string id;
		readString(id, "Enter id client to find: ");
		std::string temp = client::findClient(id);
		if (temp != "") std::cout << temp << "\n\n";
		else std::cout << "\nClient Not Found!\n";
		system("pause");
	}
}
void deleteClient()
{
	if (currentUser.deleteClient == 'n')
	{
		std::cout << "\nYou Don't Have Permission!\n";
		system("pause");
	}
	else
	{
		system("cls");
		printMenuName("Delete Client", currentUser.name);
		std::string id;
		readString(id, "Enter id client to delete: ");

		std::string temp = client::findClient(id);
		if (temp != "")
		{
			std::cout << temp << "\n............\n";
			char choice = 'n';
			std::cout << "Do you want to delete this Client? (y/n): ";
			std::cin >> choice;
			if (choice == 'y' || choice == 'Y')
			{
				client::deleteClient(id);
				std::cout << "Client Deleted!\n\n";
			}
		}
		else std::cout << "\nClient Not Found!\n";
		system("pause");
	}
}
void updateClient()
{
	if (currentUser.updateClient == 'n')
	{
		std::cout << "\nYou Don't Have Permission!\n";
		system("pause");
	}
	else
	{
		system("cls");
		printMenuName("Update Client", currentUser.name);
		std::string id;
		readString(id, "Enter id client to update: ");
		bool isUpdated = client::updateClient(id);
		if (isUpdated) std::cout << "\nClient Updated!\n";
		else std::cout << "\nClient Not Found!\n";
		system("pause");
	}
}
void showUsersRegister()
{
	if (currentUser.showUsersRegister == 'n')
	{
		std::cout << "\nYou Don't Have Permission!\n";
		system("pause");
	}
	else
	{
		system("cls");
		printMenuName("Users Register", currentUser.name);
		std::fstream file("usersRegister.txt", std::ios::in);
		std::string line;
		size_t pos;
		while (getline(file, line))
		{
			line = decrypt(line);
			pos = line.find(",/,");
			std::cout << "Name: " << line.substr(0, pos) << "\n";
			line.erase(0, pos + 3);

			pos = line.find(",/,");
			std::cout << "Password: " << line.substr(0, pos) << "\n";
			line.erase(0, pos + 3);

			std::cout << "Login Time Date: " << line << "\n..............\n";
		}
		system("pause");
	}
}
void mainMenu()
{
	short choice = 0;
	do
	{
		system("cls");
		printMenuName("Welcome To Bank On C++ Console", currentUser.name);
		std::cout << "1.Add Clients\n";
		std::cout << "2.Show All Clients\n";
		std::cout << "3.Find Client\n";
		std::cout << "4.Delete Client\n";
		std::cout << "5.Update Client\n";
		std::cout << "6.Financial Transactions\n";
		std::cout << "7.Users Control\n";
		std::cout << "8.Show Users Register\n";
		std::cout << "9.Back To Login\n";
		std::cout << "........................\n";
		std::cout << "\nEnter Your Choice: ";
		std::cin >> choice;
		switch (choice)
		{
		case 1:
			addClient();
			break;
		case 2:
			showAllClients();
			break;
		case 3:
			findClient();
			break;
		case 4:
			deleteClient();
			break;
		case 5:
			updateClient();
			break;
		case 6:
			financialTransactionsMenu();
			break;
		case 7:
			usersControlMenu();
			break;
		case 8:
			showUsersRegister();
			break;
		}
	} while (choice != 9);
}