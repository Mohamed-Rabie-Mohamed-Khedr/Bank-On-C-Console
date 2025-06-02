#pragma once
#include "currentUser.h"
#include "client.h"
void withdraw()
{
	system("cls");
	printMenuName("Withdraw Money", currentUser.name);
	std::string id;
	client c;
	readString(id, "Enter id client to withdraw: ");
	client::findClient(id, c);
	if (c.getName() != "")
	{
		std::cout << std::endl << c.getInfoToShow() << "\n\n";
		int amount;
		readNumber(amount, "Enter amount: ");
		bool isWithdrawed = c.withdraw(amount);
		if (isWithdrawed) std::cout << "\nWithdrawed Successfully!\n";
		else std::cout << "\nWithdrawed Failed!\n";
	}
	else std::cout << "\nClient Not Found!\n";
	system("pause");
}
void deposit()
{
	system("cls");
	printMenuName("Deposit Money", currentUser.name);
	std::string id;
	client c;
	readString(id, "Enter id client to deposit: ");
	client::findClient(id, c);
	if (c.getName() != "")
	{
		std::cout << std::endl << c.getInfoToShow() << "\n\n";
		int amount;
		readNumber(amount, "Enter amount: ");
		bool isDeposited = c.deposit(amount);
		if (isDeposited) std::cout << "\nDeposited Successfully!\n";
		else std::cout << "\nDeposited Failed!\n";
	}
	else std::cout << "\nClient Not Found!\n";
	system("pause");
}
void transferRegister(client& c1, client& c2, int amount)
{
	std::fstream usersRegisterFile("transferRegister.txt", std::ios::app | std::ios::out);
	usersRegisterFile << encrypt(std::to_string(amount) + ",/," + std::to_string(c1.getMoney())
	+ ",/," + std::to_string(c2.getMoney()) + ",/," + c1.getName() + ",/," + c2.getName()
	+ ",/," + getToday(true)) << "\n";
	usersRegisterFile.close();
}
void transfer()
{
	B: system("cls");
	printMenuName("Transfer Money", currentUser.name);
	bool isTransfered = false;
	std::string client1ID, client2ID;
	client c1, c2;
	readString(client1ID, "Enter id client from: ");
	readString(client2ID, "Enter id client to: ");
	client::findClient(client1ID, c1);
	client::findClient(client2ID, c2);
	if (c2.getName() != "" && c1.getName() != "")
	{
		std::cout << std::endl << c1.getInfoToShow() << "\n............\n";
		std::cout << std::endl << c2.getInfoToShow() << "\n............\n";
		int amount;
		readNumber(amount, "\nEnter amount: ");
		bool isWithdrawed = c1.withdraw(amount);
		if (isWithdrawed)
		{
			bool isDeposited = c2.deposit(amount);
			if (isDeposited)
			{
				isTransfered = true;
				transferRegister(c1, c2, amount);
				std::cout << "\nTransfered Successfully!\n";
			}
			else
			{
				c2.deposit(amount);
				std::cout << "\nTransfered Failed!\n";
			}
		}
		else std::cout << "\nTransfered Failed!\n";
	}
	else std::cout << "\nClient Not Found!\n";
	if (!isTransfered)
	{
		system("pause");
		goto B;
	}
	else system("pause");
}
void showTransferRegister()
{
	system("cls");
	printMenuName("Show Transfer Register", currentUser.name);
	std::fstream file("transferRegister.txt", std::ios::in);
	std::string line;
	size_t pos;
	while (getline(file, line))
	{
		line = decrypt(line);
		pos = line.find(",/,");
		std::cout << "Amount: " << line.substr(0, pos) << "\n";
		line.erase(0, pos + 3);

		pos = line.find(",/,");
		std::cout << "Client 1 Money: " << line.substr(0, pos) << "\n";
		line.erase(0, pos + 3);

		pos = line.find(",/,");
		std::cout << "Client 2 Money: " << line.substr(0, pos) << "\n";
		line.erase(0, pos + 3);

		pos = line.find(",/,");
		std::cout << "Client 1 Name: " << line.substr(0, pos) << "\n";
		line.erase(0, pos + 3);

		pos = line.find(",/,");
		std::cout << "Client 2 Name: " << line.substr(0, pos) << "\n";
		line.erase(0, pos + 3);

		std::cout << "Transfer Time Date: " << line << "\n..............\n";
	}
	system("pause");

}
void financialTransactionsMenu()
{
	if (currentUser.financialTransactions == 'n')
	{
		std::cout << "\nYou Don't Have Permission!\n";
		system("pause");
	}
	else
	{
		short choice = 0;
		do
		{
			system("cls");
			printMenuName("Financial Transactions Menu", currentUser.name);
			std::cout << "1.Withdraw\n";
			std::cout << "2.Deposit\n";
			std::cout << "3.Transfer\n";
			std::cout << "4.Show Transfer Register\n";
			std::cout << "5.back to main menu\n";
			std::cout << "\nEnter Your Choice: ";
			std::cin >> choice;
			switch (choice)
			{
			case 1:
				withdraw();
				break;
			case 2:
				deposit();
				break;
			case 3:
				transfer();
				break;
			case 4:
				showTransferRegister();
				break;
			}
		} while (choice != 5);
	}
}