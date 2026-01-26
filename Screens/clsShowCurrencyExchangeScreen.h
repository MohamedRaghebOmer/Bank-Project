#pragma once

#include "Base\clsScreen.h"
#include "Core\CurrencyExchange\clsListCurrenciesScreen.h"
#include "Core\CurrencyExchange\clsFindCurrencyScreen.h"
#include "Core\CurrencyExchange\clsUpdateCurrencyRateScreen.h"
#include "Core\CurrencyExchange\clsCurrencyCalculatorScreen.h"

class clsShowCurrencyExchangeScreen : public clsScreen
{
private:

    static short _ReadCurrencyExchangeMenueChoose()
    {
        return clsInputValidate::ReadShortNumberBetween(1, 5, "Choose what do you want to do from [1 To 5]: ", "Invalid Choose, please try again.\n\n");
    }

    enum _enCurrencyExchangeMenueOptions
    {
        eListCurrencies = 1, eFindCurrency = 2, eUpdateRate = 3,
        eCurrencyCalculator = 4, eMainMenue = 5
    };

    static void _GoToCurrencyExchangeMenueScreen()
    {
        cout << "Press any key to go to Currency Exchange Menue Screen...";
        system("pause>0");
        system("cls");
        ShowCurrencyExchangeMenueScreen();
    }

    static void _ShowListCurrenciesScreen()
    {
        clsListCurrenciesScreen::ShowListCurrenciesScreen();
    }

    static void _ShowFindCurrencyScreen()
    {
        clsFindCurrencyScreen::ShowFindCurrencyScreen();
    }

    static void _ShowUpdateRateScreen()
    {
        clsUpdateCurrencyRateScreen::ShowUpdateCurrencyRateScreen();
    }

    static void _ShowCurrencyCalculatorScreen()
    {
        clsCurrencyCalculatorScreen::ShowCurrencyCalculatorScreen();
    }

    static void _PerformCurrencyExchangeMenueChoose(_enCurrencyExchangeMenueOptions Choose)
    {
        switch (Choose)
        {
        case eListCurrencies:
        {
            system("cls");
            _ShowListCurrenciesScreen();
            _GoToCurrencyExchangeMenueScreen();
            break;
        }
        case eFindCurrency:
        {
            system("cls");
            _ShowFindCurrencyScreen();
            _GoToCurrencyExchangeMenueScreen();
            break;
        }
        case eUpdateRate:
        {
            system("cls");
            _ShowUpdateRateScreen();
            _GoToCurrencyExchangeMenueScreen();
            break;
        }
        case eCurrencyCalculator:
        {
            system("cls");
            _ShowCurrencyCalculatorScreen();
            _GoToCurrencyExchangeMenueScreen();
            break;
        }
        case eMainMenue:
        {
            // do nothing, it will work as expected...
            break;
        }
        default:
        {
            system("cls");
            cout << "We are sorry, an expected error oqoured." << endl;
            // after that it will go to main menue screen
        }
        
        }
    }

public:

	static void ShowCurrencyExchangeMenueScreen()
	{
        clsScreen::_DrawScreenHeader("Currency Exchange Screen");
        cout << "\t[1] List Currencies.\n";
        cout << "\t[2] Find Currency.\n";
        cout << "\t[3] Update Rate.\n";
        cout << "\t[4] Currency Calculator.\n";
        cout << "\t[5] Main Menue.\n";
        cout << "===========================================\n";
        _PerformCurrencyExchangeMenueChoose((_enCurrencyExchangeMenueOptions)_ReadCurrencyExchangeMenueChoose());
	}
};

