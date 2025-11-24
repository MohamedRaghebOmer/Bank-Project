#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsDepositScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTotalBalancesScreen.h"
#include "clsTransferScreen.h"
#include "clsTransferLogScreen.h"
#include <iomanip>
#include "Global.h"

class clsTransactionsScreen :protected clsScreen
{
private:
    enum enTransactionsMenueOptions 
    {
        eDeposit = 1, eWithdraw = 2,
        eShowTotalBalance = 3, eShowTransferScreen = 4,
        eShowTransferLog = 5 , eShowMainMenue = 6
    };

    static short ReadTransactionsMenueOption()
    {
        return clsInputValidate::ReadShortNumberBetween(1, 6, "Choose what do you want to do [1 to 6]: ", true, "Invalid choose, please try again.\n\n");
    }

    static void _ShowDepositScreen()
    {
        clsDepositScreen::ShowDepositScreen();
    }

    static void _ShowWithdrawScreen()
    {
        clsWithdrawScreen::ShowWithdrawScreen();
    }

    static void _ShowTotalBalancesScreen()
    {
        clsTotalBalancesScreen::ShowTotalBalances();
    }

    static void _GoBackToTransactionsMenue()
    {
        cout << "\n\nPress any key to go back to Transactions Menue...";
        system("pause>0");

        ShowTransactionsMenue();
    }

    static void _ShowTransferScreen()
    {
        clsTransferScreen::ShowTransferScreen();
    }

    static void _ShowTransferLogScreen()
    {
        clsTransferLogScreen::ShowTranferLog();
    }

    static void _PerformTransactionsMenueOption(enTransactionsMenueOptions TransactionsMenueOption)
    {
        switch (TransactionsMenueOption)
        {
        case enTransactionsMenueOptions::eDeposit:
        {
            system("cls");
            _ShowDepositScreen();
            _GoBackToTransactionsMenue();
            break;
        }

        case enTransactionsMenueOptions::eWithdraw:
        {
            system("cls");
            _ShowWithdrawScreen();
            _GoBackToTransactionsMenue();
            break;
        }

        case enTransactionsMenueOptions::eShowTotalBalance:
        {
            system("cls");
            _ShowTotalBalancesScreen();
            _GoBackToTransactionsMenue();
            break;
        }

        case enTransactionsMenueOptions::eShowTransferScreen:
        {
            system("cls");
            _ShowTransferScreen();
            _GoBackToTransactionsMenue();
            break;
        }
        
        case enTransactionsMenueOptions::eShowTransferLog:
        {
            system("cls");
            _ShowTransferLogScreen();
            _GoBackToTransactionsMenue();
            break;
        }
        case enTransactionsMenueOptions::eShowMainMenue:
        {
            //do nothing here the main screen will handle it :-)
            // it will swith outomactly to main menue
        }
        }

    }

public:
    static void ShowTransactionsMenue()
    {
        if (!CheckAccessRights(clsUser::enPermissions::pTranactions))
        {
            return;// this will exit the function and it will not continue
        }

        system("cls");
        _DrawScreenHeader("Transactions Screen");
        cout << "\t[1] Deposit." << endl;
        cout << "\t[2] Withdraw." << endl;
        cout << "\t[3] Total Balances." << endl;
        cout << "\t[4] Transfer." << endl;
        cout << "\t[5] Transfer Log." << endl;
        cout << "\t[6] Main Menue." << endl;
        cout << "===========================================" << endl;
        _PerformTransactionsMenueOption((enTransactionsMenueOptions)ReadTransactionsMenueOption());
    }

};

