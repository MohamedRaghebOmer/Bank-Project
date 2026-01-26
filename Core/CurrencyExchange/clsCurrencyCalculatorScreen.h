#pragma once

#include <iostream>
#include "Base\clsScreen.h"
#include "Base\clsCurrency.h"
#include "Lib's\clsInputValidate.h"

class clsCurrencyCalculatorScreen : public clsScreen
{
private:

    static clsCurrency _GetCurrency(const string& Message)
    {
        string CurrencyCode = clsInputValidate::ReadString(Message);

        while (!clsCurrency::isCurrencyExist(CurrencyCode))
        {
            cout << "\nCurrency is not found, please try again.\n\n";
            CurrencyCode = clsInputValidate::ReadString(Message);
        }

        return clsCurrency::findByCode(CurrencyCode);
    }


    static  void _PrintCurrencyCard(clsCurrency& Currency, const string& Title = "Currency Card:")
    {
        cout << "\n" << Title << "\n";
        cout << "_____________________________\n";
        cout << "\nCountry       : " << Currency.Country();
        cout << "\nCode          : " << Currency.CurrencyCode();
        cout << "\nName          : " << Currency.CurrencyName();
        cout << "\nRate(1$) =    : " << Currency.Rate();
        cout << "\n_____________________________\n\n";
    }

    static void _PrintCalculationsResults(float Amount, clsCurrency& Currency1, clsCurrency& Currency2)
    {

        _PrintCurrencyCard(Currency1, "Convert From:");

        float AmountInUSD = Currency1.ConvertToUSD(Amount);

        cout << Amount << " " << Currency1.CurrencyCode()
            << " = " << AmountInUSD << " USD\n";

        if (Currency2.CurrencyCode() == "USD") 
            return;

        cout << "\nConverting from USD to:\n";
        _PrintCurrencyCard(Currency2, "To:");

        float AmountInCurrrency2 = Currency1.ConvertToOtherCurrency(Amount, Currency2);

        cout << Amount << " " << Currency1.CurrencyCode()
            << " = " << AmountInCurrrency2 << " " << Currency2.CurrencyCode();

    }


public:

    static void ShowCurrencyCalculatorScreen()
    {
        char Continue = 'y';

        while (Continue == 'y' || Continue == 'Y')
        {
            system("cls");
            _DrawScreenHeader("Calculator Currency Screen");

            clsCurrency CurrencyFrom = _GetCurrency("\nPlease Enter Currency1 Code: "),
            CurrencyTo = _GetCurrency("\nPlease Enter Currency2 Code: ");
           
            float Amount = clsInputValidate::ReadPositiveFloat(false, 
            "\nEnter Amount to Exchange: ", 
            "Invalid amount, please try again.\n\n");

            _PrintCalculationsResults(Amount, CurrencyFrom, CurrencyTo);

            cout << "\n\nDo you want to perform another calculation? [Y|N]: ";
            cin >> Continue;

        }

        cout << endl;
    }
};

