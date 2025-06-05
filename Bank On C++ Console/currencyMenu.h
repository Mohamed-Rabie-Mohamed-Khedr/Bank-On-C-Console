#pragma once
#include "currency.h"
#include "currentUser.h"
void showCurrencies()
{
	system("cls");
	printMenuName("Show List of currencies", currentUser.name);
	std::vector<currency> currencies = currency::getCurrenciesFromFile();
	for (int i = 0; i < currencies.size(); ++i)
	{
		std::cout << currencies[i].getInfoToShow() << "\n.....................\n";
	}
	system("pause");
}
void currencyCalculator()
{
	char choice = 'Y';
	do
	{
		system("cls");
		printMenuName("Currency calculator", currentUser.name);
		float amount = 0;
		std::string code1 = "", code2 = "";
		B: readString(code1, "Enter first currency code: ");
		currency curr1 = currency::getCurrency(code1);
		if (curr1.getCode() == "")
		{
			std::cout << "Currency not found\n";
			goto B;
		}
		B2: readString(code2, "Enter second currency code: ");
		currency curr2 = currency::getCurrency(code2);
		if (curr2.getCode() == "")
		{
			std::cout << "Currency not found\n";
			goto B2;
		}
		std::cout << "..............\nCurrent info:\n" << curr1.getInfoToShow() << std::endl;
		std::cout << "..............\nCurrent info:\n" << curr2.getInfoToShow() << std::endl;
		readNumber(amount, "Enter amount: ");
		float result;
		if (curr2.getRate() == 1)
		{
			result = amount / curr1.getRate();
		}
		else
		{
			result = amount / curr1.getRate();
			result *= curr2.getRate();
		}
		std::cout << std::endl << "After conversion Amount: " << result << std::endl;
		std::cout << "Do you want to Perform another conversion (Y/N): ";
		std::cin >> choice;
	} while (choice == 'Y' || choice == 'y');
}
void updateCurrencyRate()
{
	system("cls");
	printMenuName("Update currency Rate", currentUser.name);
	float newRate = 0;
	std::string code = "";
	B: readString(code, "Enter rate code: ");
	currency curr = currency::getCurrency(code);
	if (curr.getCode() == "")
	{
		std::cout << "Currency not found\n";
		goto B;
	}
	std::cout << std::endl << "Current rate: " << curr.getRate() << std::endl;
	readNumber(newRate, "Enter new currency rate: ");
	curr.updateRate(newRate);
	std::cout << std::endl << "Currency rate updated successfully\n";
	system("pause");
}
void findCurrency()
{
	system("cls");
	printMenuName("Find currency", currentUser.name);
	std::cout << "1.Find currency by code\n2.Find currency by name" << std::endl;
	short choice = 0;
	readNumber(choice, "Enter your choice: ");
	if (choice == 1)
	{
		std::string code = "";
		BRS: readString(code, "Enter currency code: ");
		currency curr = currency::getCurrency(code);
		if (curr.getCode() == "")
		{
			std::cout << "Currency not found\n";
			goto BRS;
		}
		std::cout << std::endl << curr.getInfoToShow() << std::endl << std::endl;
	}
	else
	{
		std::string name = "", info = "";
		BRN: readString(name, "Enter currency name: ");
		info = currency::findByName(name);
		if (info == "")
		{
			std::cout << "Currency not found\n";
			goto BRN;
		}
		std::cout << std::endl << info << std::endl << std::endl;
	}
	system("pause");
}
void currencyMenu()
{
	short choice = 0;
	do
	{
		system("cls");
		printMenuName("Find User", currentUser.name);
		std::cout << "1.Show List of currencies" << std::endl;
		std::cout << "2.Currency Calculator" << std::endl;
		std::cout << "3.Update currency Rate" << std::endl;
		std::cout << "4.Find currency" << std::endl;
		std::cout << "5.Back to main menu" << std::endl;
		std::cout << "........................\n";
		readNumber(choice, "Enter your choice: ");
		switch (choice)
		{
		case 1:
			showCurrencies();
			break;
		case 2:
			currencyCalculator();
			break;
		case 3:
			updateCurrencyRate();
			break;
		case 4:
			findCurrency();
			break;
		}
	} while (choice != 5);
}