#pragma once
#include "currencyMenu.h"
#include "client.h"
void addUser()
{
	char choice = '0';
	bool isAdded = false;
	do
	{
		system("cls");
		printMenuName("Add User", currentUser.name);
		isAdded = user::addUser();
		if (isAdded) std::cout << "\nUser Added Successfully!\n";
		else std::cout << "\nUser Added Failed!\n";

		std::cout << "Do you want to add another User? (y/n): "; std::cin >> choice;
	} while (choice != 'n' && choice != 'N');
}
void showAllUsers()
{
	system("cls");
	printMenuName("All Users", currentUser.name);
	std::vector<user> all = user::getUsersFromFile();
	for (size_t i = 0; i < all.size(); ++i)
	{
		std::cout << all[i].getInfoToShow() << "\n..........\n";
	}
	system("pause");
}
void findUser()
{
	system("cls");
	printMenuName("Find User", currentUser.name);
	std::string name = "", info = "";
	readString(name, "Enter User Name to find: ");
	info = user::findUser(name);
	if (info != "") std::cout << info << "\n\n";
	else std::cout << "\nUser Not Found!\n";
	system("pause");
}
void deleteUser()
{
	system("cls");
	printMenuName("Delete User", currentUser.name);
	std::string name = "";
	readString(name, "Enter User Name to delete: ");

	char choice = 'n';
	std::cout << "Do you want to delete this User? (y/n): ";
	std::cin >> choice;

	if (choice == 'y' || choice == 'Y')
	{
		bool isDeleted = user::deleteUser(name);
		if (isDeleted) std::cout << "\nUser Deleted Successfully!\n";
		else std::cout << "\nUser Deleted Failed!\n";
	}
	system("pause");
}
void updateUser()
{
	system("cls");
	printMenuName("Update User", currentUser.name);
	std::string name = "";
	readString(name, "Enter User Name to update: ");
	bool isUpdated = user::updateUser(name);
	if (isUpdated) std::cout << "\nUser Updated Successfully!\n";
	else std::cout << "\nUser Updated Failed!\n";
	system("pause");
}
void usersControlMenu()
{
	if (currentUser.usersControl == 'n')
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
			printMenuName("Users Control Menu", currentUser.name);
			std::cout << "1.Add User\n";
			std::cout << "2.Show All Users\n";
			std::cout << "3.Find User\n";
			std::cout << "4.Delete User\n";
			std::cout << "5.Update User\n";
			std::cout << "6.back to main menu\n";
			readNumber(choice, "Enter Your Choice: ");
			switch (choice)
			{
			case 1:
				addUser();
				break;
			case 2:
				showAllUsers();
				break;
			case 3:
				findUser();
				break;
			case 4:
				deleteUser();
				break;
			case 5:
				updateUser();
				break;
			}
		} while (choice != 6);
	}
}