#pragma once

#include "Base\clsScreen.h"

class clsUpdateCurrencyRateScreen : public clsScreen
{
private:
	static void _PrintCurrency(clsCurrency& Currency)
	{
		cout << "\nCurrency Card:\n";
		cout << "-----------------------------\n";
		cout << "Country : " << Currency.Country() << endl;
		cout << "Code    : " << Currency.CurrencyCode() << endl;
		cout << "Name    : " << Currency.CurrencyName() << endl;
		cout << "Rate(1$): " << Currency.Rate() << endl;
		cout << "-----------------------------\n\n";
	}

public:
	static void ShowUpdateCurrencyRateScreen()
	{
		clsScreen::_DrawScreenHeader("Update Currency Rate Screen");

		string code = clsInputValidate::ReadString("\nPlease Enter Currency Code: ");
		code = clsString::Trim(code);
		code = clsString::UpperAllString(code); // normalize

		clsCurrency Currency = clsCurrency::findByCode(code);
		
		if (Currency.isEmpty())
		{
			cout << "Currency was not found :-(\n\n";
			return;
		}
		else
		{
			_PrintCurrency(Currency);
		}

		char answer = 'n';
		cout << "Are you sure you want to update the rate of this country? [Y|N]: ";
		cin >> answer;

		if (answer == 'Y' || answer == 'y')
		{		
			Currency.UpdateRate(clsInputValidate::ReadPositiveFloat(false, "Enter new rate: "));
			
			cout << "\nCurrency rate updated successfully.\n";
			_PrintCurrency(Currency);
		}

	}
};

