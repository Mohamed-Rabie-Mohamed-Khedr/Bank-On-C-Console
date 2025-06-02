#pragma once
#include "financialTransactionsMenu.h"
#include "mainMenu.h"
void usersRegister()
{
	std::fstream usersRegisterFile("usersRegister.txt", std::ios::app | std::ios::out);
	usersRegisterFile << encrypt(currentUser.name + ",/," + currentUser.password +
	",/," + getToday(true)) << "\n";
	usersRegisterFile.close();
}
void loginMenu()
{

	std::fstream file("users.txt", std::ios::in);
	if (!file.good())
	{
		std::ofstream file("users.txt");
		file << encrypt("admin,/,1234,/,yyyyyyyy") << "\n";
		file.close();
	}
	file.close();
	std::string name = "", password = "";
	bool isLogin = false;
	short loginTrys = 3;

	do
	{
		std::vector<user> all = user::getUsersFromFile();
		system("cls");
		printMenuName("Login", currentUser.name);
		readString(name, "Enter Your Name: ");
		readString(password, "Enter Your Password: ");
		for (int i = 0; i < all.size(); i++)
		{
			if (all[i].name == name && all[i].password == password)
			{
				isLogin = true;
				loginTrys = 3;
				currentUser = all[i];
				usersRegister();
				mainMenu();
				currentUser = user();
				break;
			}
		}
		if (isLogin == false)
		{
			loginTrys--;
			std::cout << "\nLogin Failed!, Yuou Have " << loginTrys << " Trys Left\n";
			system("pause");
		}
	} while (loginTrys > 0);
	std::cout << "You Have No Trys Left\n";
}