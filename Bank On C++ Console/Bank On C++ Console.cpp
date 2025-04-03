#include <iostream>
#include <string>
#include <fstream>
#include <vector>
void mainMenu();
template <typename T>
void readNumber(T& num, std::string message)
{
	std::cout << message;
	std::cin >> num;
	while (std::cin.fail())
	{
		std::cout << message;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin >> num;
	}
}

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
			if (all[i].id == id)
			{
				all[i].money += amount;
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
			if (all[i].id == id && all[i].money >= amount)
			{
				all[i].money -= amount;
				isDeposited = true;
			}
			file << all[i].getInfo() + "\n";
		}
		file.close();
		return isDeposited;
	}
};
void printMenuName(std::string name)
{
	std::cout << "..........................................\n";
	std::cout << "\t" << name << "\n";
	std::cout << "..........................................\n\n";
}
void addClient()
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
void showAllClients()
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
void findClient()
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
void deleteClient()
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
void updateClient()
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
void withdraw()
{
	system("cls");
	printMenuName("Withdraw Money");
	client p("clients.txt");
	std::cout << "Enter id client to withdraw: ";
	std::string id;
	std::cin >> id;
	int amount;
	readNumber(amount, "Enter amount: ");
	bool isWithdrawed = p.withdraw(id, amount);
	if (isWithdrawed) std::cout << "\nWithdrawed Successfully!\n";
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
	int amount;
	readNumber(amount, "Enter amount: ");
	bool isDeposited = p.deposit(id, amount);
	if (isDeposited) std::cout << "\nDeposited Successfully!\n";
	else std::cout << "\nClient Not Found!\n";
	system("pause");
}
void financialTransactions()
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
		std::cout << "7.Exit\n";
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
		}
	} while (choice != '7');
}

int main()
{
	mainMenu();
	return 0;
}