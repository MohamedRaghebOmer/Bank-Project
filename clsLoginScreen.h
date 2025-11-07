#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include <iomanip>
#include "clsMainMenueScreen.h"
#include "Global.h"
class clsLoginScreen :protected clsScreen
{

private:

    static  void _Login()
    {
        bool LoginFaild = false;

        string Username, Password;
        do
        {

            if (LoginFaild)
            {
                cout << "Invlaid Username/Password!\n\n";
            }

            cout << "Enter Username: ";
            cin >> Username;

            cout << "Enter Password: ";
            cin >> Password;

            CurrentUser = clsUser::Find(Username, Password);

            LoginFaild = CurrentUser.IsEmpty();

        } while (LoginFaild);

        clsMainMenueScreen::ShowMainMenueScreen();
    }

public:

    static void ShowLoginScreen()
    {
        system("cls");
        _DrawScreenHeader("Login Screen");
        _Login();
    }

};

