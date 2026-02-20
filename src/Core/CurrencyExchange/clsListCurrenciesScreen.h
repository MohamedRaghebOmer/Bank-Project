#pragma once

#include "D:\GitHub\Bank-Project\src\Base\clsScreen.h"
#include "D:\GitHub\Bank-Project\src\Base\clsCurrency.h"

class clsListCurrenciesScreen : public clsScreen
{
private:

	static void _PrintOneCurrency(clsCurrency& Currency)
	{
		cout << setw(8) << left << "" << "| " << setw(30) << left << Currency.Country();
		cout << "| " << setw(8) << left << Currency.CurrencyCode();
		cout << "| " << setw(45) << left << Currency.CurrencyName();
		cout << "| " << setw(10) << left << Currency.Rate();
	}

public:

	static void ShowListCurrenciesScreen()
	{
		vector <clsCurrency> vAllCurrencies = clsCurrency::GetCurrenciesList();
		
		string tilte = "\tList Currencies Screen", subtitle = "\t[" + to_string(vAllCurrencies.size()) + "] Currencies.";
		clsScreen::_DrawScreenHeader(tilte, subtitle, true);

		// Draw table header
		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_______________________________________________\n" << endl;

		cout << setw(8) << left << "" << "| " << left << setw(30) << "Country";
		cout << "| " << left << setw(8) << "Code";
		cout << "| " << left << setw(45) << "Name";
		cout << "| " << left << setw(10) << "Rate/(1$)";
		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_______________________________________________\n" << endl;

		if (vAllCurrencies.size() == 0)
			cout << "\t\t\t\tNo currencies avalible in the system." << endl;
		else
		{
			for (clsCurrency& Currency : vAllCurrencies)
			{
				_PrintOneCurrency(Currency);
				cout << endl;
			}
		}

		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_______________________________________________\n" << endl;

	}
};

