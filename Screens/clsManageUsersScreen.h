#pragma once

#include <iostream>
#include "Base\clsScreen.h"
#include "Lib's\clsInputValidate.h"
#include <iomanip>
#include "Core\ManageUsers\clsListUsersScreen.h"
#include "Core\ManageUsers\clsAddNewUserScreen.h"
#include "Core\ManageUsers\clsDeleteUserScreen.h"
#include "Core\ManageUsers\clsUpdateUserScreen.h"
#include "Core\ManageUsers\clsFindUserScreen.h"
#include "Base\Global.h"

class clsManageUsersScreen : public clsScreen
{
    static short _ReadManageUsersChoose()
    {
        return clsInputValidate::ReadShortNumberBetween(1, 6, "Choos what do you want to do [1 to 6]: ",true, "Invalid choose, please try again.\n\n");
    }

    enum enManageUsersMenueOptions {
        eListUsers = 1, eAddNewUser = 2, eDeleteUser = 3,
        eUpdateUser = 4, eFindUser = 5, eMainMenue = 6
    };
    
    static void _GoBackToManageUsersMenue()
    {
        cout << "\n\nPress any key to go back to Manage Users Menue...";
        system("pause>0");

        ShowManageUsersMenue();
    }


    static void _ShowListUsersScreen()
    {
        clsListUsersScreen::ShowUsersList();
    }

    static void _ShowAddNewUserScreen()
    {
        clsAddNewUserScreen::ShowAddNewUserScreen();
    }

    static void _ShowDeleteUserScreen()
    {
        clsDeleteUserScreen::ShowDeleteUserScreen();
    }

    static void _ShowUpdateUserScreen()
    {
        clsUpdateUserScreen::ShowUpdateUserScreen();
    }

    static void _ShowFindUserScreen()
    {
		clsFindUserScreen::ShowFindUserScreen();
    }


    static void _PerformManageUsersMenueOption(enManageUsersMenueOptions ManageUsersMenueOption)
    {

        switch (ManageUsersMenueOption)
        {
        case enManageUsersMenueOptions::eListUsers:
        {
            system("cls");
            _ShowListUsersScreen();
            _GoBackToManageUsersMenue();
            break;
        }

        case enManageUsersMenueOptions::eAddNewUser:
        {
            system("cls");
            _ShowAddNewUserScreen();
            _GoBackToManageUsersMenue();
            break;
        }

        case enManageUsersMenueOptions::eDeleteUser:
        {
            system("cls");
            _ShowDeleteUserScreen();
            _GoBackToManageUsersMenue();
            break;
        }

        case enManageUsersMenueOptions::eUpdateUser:
        {
            system("cls");
            _ShowUpdateUserScreen();
            _GoBackToManageUsersMenue();
            break;
        }

        case enManageUsersMenueOptions::eFindUser:
        {
            system("cls");

            _ShowFindUserScreen();
            _GoBackToManageUsersMenue();
            break;
        }

        case enManageUsersMenueOptions::eMainMenue:
        {
            //do nothing here the main screen will handle it :-) ;
        }
        }

    }

public:

	static void ShowManageUsersMenue()
	{
        if (!CheckAccessRights(clsUser::enPermissions::pManageUsers))
        {
            return;// this will exit the function and it will not continue
        }


        system("cls");
        _DrawScreenHeader("Manage Users Screen");
        cout << "\t[1] List Users.\n";
        cout << "\t[2] Add New User.\n";
        cout << "\t[3] Delete User.\n";
        cout << "\t[4] Update User.\n";
        cout << "\t[5] Find User.\n";
        cout << "\t[6] Main Menue.\n";
        cout << "===========================================" << endl;
        _PerformManageUsersMenueOption((enManageUsersMenueOptions)_ReadManageUsersChoose());
	}

};

