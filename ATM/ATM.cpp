#include "client.h"

client currentClient;
void printMenuName(std::string name)
{
	std::cout << "..........................................\n";
	std::cout << "\t" << name << "\n";
	std::cout << "..........................................\n\n";
}
void withdraw(int amount)
{
	client p;
	bool isWithdrawed = p.withdraw(currentClient.getId(), amount);
	if (isWithdrawed)
	{
		currentClient.setMoney(currentClient.getMoney() - amount);
		std::cout << "\n\nWithdrawed Successfully!, Your Money " << currentClient.getMoney() << "\n";
	}
	else std::cout << "\n\nWithdrawed Failed!";
	system("pause");
}
void withdraw()
{
	system("cls");
	printMenuName("Withdraw Money");
	client p;
	int amount;
	readNumber(amount, "Enter amount: ");
	bool isWithdrawed = p.withdraw(currentClient.getId(), amount);
	if (isWithdrawed)
	{
		currentClient.setMoney(currentClient.getMoney() - amount);
		std::cout << "\nWithdrawed Successfully!, Your Money " << currentClient.getMoney() << "\n";
	}
	else std::cout << "\nWithdrawed Failed!\n";
	system("pause");
}
void deposit()
{
	system("cls");
	printMenuName("Deposit Money");
	client p;
	int amount;
	readNumber(amount, "Enter amount: ");
	bool isDeposited = p.deposit(currentClient.getId(), amount);
	if (isDeposited)
	{
		currentClient.setMoney(currentClient.getMoney() + amount);
		std::cout << "\nDeposited Successfully!, Your Money " << currentClient.getMoney() << "\n";
	}
	else std::cout << "\nDeposited Failed!\n";
	system("pause");
}
void showBalance()
{
	system("cls");
	printMenuName("Show Balance");
	std::cout << "Your Money: " << currentClient.getMoney() << "\n";
	system("pause");
}
void quickWithdrawMenu()
{
	char choice = '0';
	system("cls");
	printMenuName("Quick Withdraw");
	std::cout << "1 100\n";
	std::cout << "2 500\n";
	std::cout << "3 1000\n";
	std::cout << "4 2000\n";
	std::cout << "5 5000\n";
	std::cout << "6 10000\n";
	std::cout << "7 20000\n";
	std::cout << "8 50000\n";
	std::cout << "9 100000\n";
	std::cout << "\nEnter Your Choice: ";
	std::cin >> choice;
	switch (choice)
	{
	case '1':withdraw(100); break;
	case '2':withdraw(500); break;
	case '3':withdraw(1000); break;
	case '4':withdraw(2000); break;
	case '5':withdraw(5000); break;
	case '6':withdraw(10000); break;
	case '7':withdraw(20000); break;
	case '8':withdraw(50000); break;
	case '9':withdraw(100000); break;
	}
}
void mainMenu()
{
	char choice = '0';
	do
	{
		system("cls");
		printMenuName("Main Menu");
		std::cout << "1 quick withdraw\n";
		std::cout << "2 normal withdraw\n";
		std::cout << "3 deposit\n";
		std::cout << "4 balance\n";
		std::cout << "5 back to login\n";
		std::cout << "Enter Your Choice: ";
		std::cin >> choice;
		switch (choice)
		{
		case '1':quickWithdrawMenu(); break;
		case '2':withdraw(); break;
		case '3':deposit(); break;
		case '4':showBalance(); break;
		}
	} while (choice != '5');
}
void loginMenu()
{
	std::fstream file("..\\Bank On C++ Console\\clients.txt", std::ios::in);
	if (!file.good())
	{
		file.close();
		std::cout << "cients not found!\n";
		return;
	}
	file.close();
	std::string name = "", id = "";
	bool isLogin = false;

	do
	{
		client p;
		std::vector<client> all = p.getClientsFromFile();
		system("cls");
		printMenuName("Login");
		std::cout << "Enter Your Name: ";
		std::cin >> name;
		std::cout << "Enter Your ID: ";
		std::cin >> id;
		for (int i = 0; i < all.size(); i++)
		{
			if (all[i].getName() == name && all[i].getId() == id)
			{
				currentClient = all[i];
				isLogin = true;
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