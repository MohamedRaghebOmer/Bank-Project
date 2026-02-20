#pragma once
#include <iostream>
#include "D:\GitHub\Bank-Project\src\Base\clsScreen.h"
#include "D:\GitHub\Bank-Project\src\Base\clsCurrency.h"
#include "D:\GitHub\Bank-Project\src\Lib's\clsInputValidate.h"
#include "D:\GitHub\Bank-Project\src\Lib's\clsString.h"

class clsFindCurrencyScreen : public clsScreen 
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

    static void _ShowResults(clsCurrency& Currency) 
    {
        if (!Currency.isEmpty()) 
        {
            cout << "\nCurrency Found :-)\n";
            _PrintCurrency(Currency);
        }
        else {
            cout << "\nCurrency Was not Found :-(\n";
        }
    }

    static int _ReadChoice() 
    {
        while (true) 
        {
            string s = clsInputValidate::ReadString("\nFind By : [1] Code or [2] Country ? ");
            s = clsString::Trim(s);

            if (s == "1") return 1;
            if (s == "2") return 2;

            cout << "Invalid choice, please enter 1 or 2.\n";
        }
    }

public:
    static void ShowFindCurrencyScreen() 
    {
        clsScreen::_DrawScreenHeader("Find Currency Screen");

        short choice = _ReadChoice();

        if (choice == 1) 
        {
            string code = clsInputValidate::ReadString("\nPlease Enter Currency Code: ");

            code = clsString::Trim(code);
            code = clsString::UpperAllString(code); // normalize
            
            clsCurrency Currency = clsCurrency::findByCode(code);
            _ShowResults(Currency);
        }
        else 
        {
            string country = clsInputValidate::ReadString("\nPlease Enter Country Name: ");

            country = clsString::Trim(country);
            country = clsString::LowerAllString(country);
            country = clsString::UpperFirstLetterOfEachWord(country); // Title case to match file
            
            clsCurrency Currency = clsCurrency::findByCountry(country);
            _ShowResults(Currency);
        }
    }
};
