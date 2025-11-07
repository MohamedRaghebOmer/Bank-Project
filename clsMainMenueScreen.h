#pragma once

#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsClientListScreen.h"
#include "clsAddNewClientScreen.h"
#include "clsDeleteClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsFindClientScreen.h"
#include "clsTransactionsScreen.h"
#include "clsManageUsersScreen.h"
#include "Global.h"

class clsMainMenueScreen : public clsScreen
{
private:

    static short _ReadMainMenueChoose()
    {
        return clsInputValidate::ReadShortNumberBetween(1, 8, "Choose what do you want to do [1 to 8]: ");
    }

    enum enMainMenueOptions
    {
        eClientsList = 1, eAddNewClient = 2, eDeleteClient = 3,
        eUpdateClient = 4, eFindClient = 5, eShowTransactionsMenue = 6,
        eManageUsers = 7, eExit = 8
    };

    static void _GoToBackToMainMenue()
    {
        cout << "\n\nPress any key to go to Main Menue Screen.....";
        system("pause>0");
        ShowMainMenueScreen();
    }

    static void _ShowClientsList()
    {
        clsClientListScreen::ShowClientsList();
    }

    static void _ShowAddNewClientScreen()
    {
        clsAddNewClientScreen::ShowAddNewClientScreen();
    }

    static void _ShowDeleteClientScreen()
    {
        clsDeleteClientScreen::ShowDeleteClientScreen();
    }

    static void _ShowUpdateClientScreen()
    {
        clsUpdateClientScreen::ShowUpdateClientScreen();
    }

    static void _ShowFindClientScreen()
    {
        clsFindClientScreen::ShowFindClientScreen();
    }

    static void _ShowTransactionsMenue()
    {
        clsTransactionsScreen::ShowTransactionsMenue();
    }

    static void _ShowManageUsersMenue()
    {
        clsManageUsersScreen::ShowManageUsersMenue();
    }

    /*static void _ShowEndScreen()
    {
        cout << "End Screen Will be here...\n";

    }*/

    static void _Logout()
    {
        CurrentUser = clsUser::Find("", "");
        //then it will go back to main function.
    }

    static void _PerformMainMenueChoose(enMainMenueOptions Choose)
    {
        switch (Choose)
        {
        case eClientsList:
        {
            system("cls");
            _ShowClientsList();
            _GoToBackToMainMenue();
            break;
        }
        case eAddNewClient:
        {
            system("cls");
            _ShowAddNewClientScreen();
            _GoToBackToMainMenue();
            break;
        }
        case eDeleteClient:
        {
            system("cls");
            _ShowDeleteClientScreen();
            _GoToBackToMainMenue();
            break;
        }
        case eUpdateClient:
        {
            system("cls");
            _ShowUpdateClientScreen();
            _GoToBackToMainMenue();
            break;
        }
        case eFindClient:
        {
            system("cls");
            _ShowFindClientScreen();
            _GoToBackToMainMenue();
            break;
        }
        case eShowTransactionsMenue:
        {
            system("cls");
            _ShowTransactionsMenue();
            _GoToBackToMainMenue();
            break;
        }
        case eManageUsers:
        {
            system("cls");
            _ShowManageUsersMenue();
            _GoToBackToMainMenue();
            break;
        }
        case eExit:
        {
            system("cls");
            _Logout();
            break;
        }
        default:
        {
            cout << "\n\nSorry an error oqoured, invalid choose value in Perform main menue screen method" << endl;
        }

        }
    }

public:

    static void ShowMainMenueScreen()
    {
        system("cls");
        clsScreen::_DrawScreenHeader("Manin Menue");
        cout << "\t[1] Show Client List." << endl;
        cout << "\t[2] Add New Client." << endl;
        cout << "\t[3] Delete Client." << endl;
        cout << "\t[4] Update Client Info." << endl;
        cout << "\t[5] Find Client." << endl;
        cout << "\t[6] Transactions." << endl;
        cout << "\t[7] Manage Users." << endl;
        cout << "\t[8] Logout." << endl;
        cout << "===========================================" << endl;
        _PerformMainMenueChoose((enMainMenueOptions)_ReadMainMenueChoose());
    }
};

