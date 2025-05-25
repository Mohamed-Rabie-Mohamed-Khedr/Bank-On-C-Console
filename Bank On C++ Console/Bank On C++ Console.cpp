#include "user.h"
#include "client.h"

user currentUser;
void mainMenu();

void printMenuName(std::string name)
{
	std::cout << "..........................................\n";
	std::cout << "\t" << name << "\n";
	std::cout << "..........................................\n\n";
}
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
		client p("clients.txt");
		do
		{
			system("cls");
			printMenuName("Add Clients Menu");
			bool added = p.addClient();
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
		printMenuName("All Clients Menu");
		client p("clients.txt");
		std::vector<client> all = p.getClientsFromFile();
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
		printMenuName("Find Client");
		client p("clients.txt");
		std::cout << "Enter id client to find: ";
		std::string id;
		std::cin >> id;
		std::string temp = p.findClient(id);
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
		printMenuName("Delete Client");
		client p("clients.txt");
		std::cout << "Enter id client to delete: ";
		std::string id;
		std::cin >> id;

		std::string temp = p.findClient(id);
		if (temp != "")
		{
			std::cout << temp << "\n............\n";
			char choice = 'n';
			std::cout << "Do you want to delete this Client? (y/n): ";
			std::cin >> choice;
			if (choice == 'y' || choice == 'Y')
			{
				p.deleteClient(id);
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
		printMenuName("Update Client");
		client p("clients.txt");
		std::cout << "Enter id client to update: ";
		std::string id;
		std::cin >> id;

		bool isUpdated = p.updateClient(id);
		if (isUpdated) std::cout << "\nClient Updated!\n";
		else std::cout << "\nClient Not Found!\n";
		system("pause");
	}
}
void withdraw()
{
	system("cls");
	printMenuName("Withdraw Money");
	client p("clients.txt");
	std::cout << "Enter id client to withdraw: ";
	std::string id;
	std::cin >> id;
	std::string temp = p.findClient(id);
	if (temp != "")
	{
		std::cout << std::endl << temp << "\n\n";
		int amount;
		readNumber(amount, "Enter amount: ");
		bool isWithdrawed = p.withdraw(id, amount);
		if (isWithdrawed) std::cout << "\nWithdrawed Successfully!\n";
		else std::cout << "\nWithdrawed Failed!\n";
	}
	else std::cout << "\nClient Not Found!\n";
	system("pause");
}
void deposit()
{
	system("cls");
	printMenuName("Deposit Money");
	client p("clients.txt");
	std::cout << "Enter id client to deposit: ";
	std::string id;
	std::cin >> id;
	std::string temp = p.findClient(id);
	if (temp != "")
	{
		std::cout << std::endl << temp << "\n\n";
		int amount;
		readNumber(amount, "Enter amount: ");
		bool isDeposited = p.deposit(id, amount);
		if (isDeposited) std::cout << "\nDeposited Successfully!\n";
		else std::cout << "\nDeposited Failed!\n";
	}
	else std::cout << "\nClient Not Found!\n";
	system("pause");
}
void financialTransactions()
{
	if (currentUser.financialTransactions == 'n')
	{
		std::cout << "\nYou Don't Have Permission!\n";
		system("pause");
	}
	else
	{
		char choice = '0';
		do
		{
			system("cls");
			printMenuName("Financial Transactions Menu");
			std::cout << "1.Withdraw\n";
			std::cout << "2.Deposit\n";
			std::cout << "3.back to main menu\n";
			std::cout << "\nEnter Your Choice: ";
			std::cin >> choice;
			switch (choice)
			{
			case '1':
				withdraw();
				break;
			case '2':
				deposit();
				break;
			}
		} while (choice != '3');
	}
}
void addUser()
{
	char choice = '0';
	bool isAdded = false;
	do
	{
		system("cls");
		printMenuName("Add User");
		isAdded = user::addUser();
		if (isAdded) std::cout << "\nUser Added Successfully!\n";
		else std::cout << "\nUser Added Failed!\n";

		std::cout << "Do you want to add another User? (y/n): "; std::cin >> choice;
	} while (choice != 'n' && choice != 'N');
}
void showAllUsers()
{
	system("cls");
	printMenuName("All Users");
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
	printMenuName("Find User");
	std::string name = "", info = "";
	std::cout << "Enter User Name to find: ";
	std::cin >> name;
	info = user::findUser(name);
	if (info != "") std::cout << info << "\n\n";
	else std::cout << "\nUser Not Found!\n";
	system("pause");
}
void deleteUser()
{
	system("cls");
	printMenuName("Delete User");
	std::string name = "";
	std::cout << "Enter User Name to delete: ";
	std::cin >> name;

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
	printMenuName("Update User");
	std::string name = "";
	std::cout << "Enter User Name to update: ";
	std::cin >> name;
	bool isUpdated = user::updateUser(name);
	if (isUpdated) std::cout << "\nUser Updated Successfully!\n";
	else std::cout << "\nUser Updated Failed!\n";
	system("pause");
}
void usersControl()
{
	if (currentUser.usersControl == 'n')
	{
		std::cout << "\nYou Don't Have Permission!\n";
		system("pause");
	}
	else
	{
		char choice = '0';
		do
		{
			system("cls");
			printMenuName("Users Control Menu");
			std::cout << "1.Add User\n";
			std::cout << "2.Show All Users\n";
			std::cout << "3.Find User\n";
			std::cout << "4.Delete User\n";
			std::cout << "5.Update User\n";
			std::cout << "6.back to main menu\n";
			std::cout << "\nEnter Your Choice: ";
			std::cin >> choice;
			switch (choice)
			{
			case '1':
				addUser();
				break;
			case '2':
				showAllUsers();
				break;
			case '3':
				findUser();
				break;
			case '4':
				deleteUser();
				break;
			case '5':
				updateUser();
				break;
			}
		} while (choice != '6');
	}
}
void mainMenu()
{
	char choice = '0';
	do
	{
		system("cls");
		std::cout << "\t\t..................................\n";
		std::cout << "\t\t\tWelcome In Bank App!\n";
		std::cout << "\t\t..................................\n\n";
		std::cout << "1.Add Clients\n";
		std::cout << "2.Show All Clients\n";
		std::cout << "3.Find Client\n";
		std::cout << "4.Delete Client\n";
		std::cout << "5.Update Client\n";
		std::cout << "6.Financial Transactions\n";
		std::cout << "7.Users Control\n";
		std::cout << "8.Back To Login\n";
		std::cout << "........................\n";
		std::cout << "\nEnter Your Choice: ";
		std::cin >> choice;
		switch (choice)
		{
		case '1':
			addClient();
			break;
		case '2':
			showAllClients();
			break;
		case '3':
			findClient();
			break;
		case '4':
			deleteClient();
			break;
		case '5':
			updateClient();
			break;
		case '6':
			financialTransactions();
			break;
		case '7':
			usersControl();
			break;
		}
	} while (choice != '8');
}
void loginMenu()
{
	std::fstream file("users.txt", std::ios::in);
	if (!file.good())
	{
		std::ofstream file("users.txt");
		file << "admin,/,1234,/,yyyyyyy\n";
	}
	file.close();
	std::string name = "", password = "";
	bool isLogin = false;

	do
	{
		std::vector<user> all = user::getUsersFromFile();
		system("cls");
		printMenuName("Login");
		std::cout << "Enter Your Name: ";
		std::cin >> name;
		std::cout << "Enter Your Password: ";
		std::cin >> password;
		for (int i = 0; i < all.size(); i++)
		{
			if (all[i].name == name && all[i].password == password)
			{
				isLogin = true;
				currentUser = all[i];
				mainMenu();
				break;
			}
		}
		if (isLogin == false)
		{
			std::cout << "Login Failed!\n";
			system("pause");
		}
	} while (true);
}
int main()
{
	loginMenu();
	return 0;
}