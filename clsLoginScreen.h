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

    static bool _Login()
    {
        bool LoginFaild = false;
        short AttemptCounter = 3;

        string Username = "", Password = "";

        do
        {

            if (LoginFaild)
            {
			    AttemptCounter--;
                cout << "Invlaid Username/Password!" << endl;

                if (AttemptCounter == 1)
					cout << "\nYou have " << AttemptCounter << " try to login.\n\n";
                else if (AttemptCounter != 0)
				    cout << "\nYou have " << AttemptCounter << " more tries to login.\n\n";
                else
                {
					cout << "\nYou have no more tries to login, Exiting the system.....\n";
                    return false;
                }
            }

			// Read Username and Password
			Username = clsInputValidate::ReadString("Enter Your Username: ");
            Password = clsInputValidate::ReadString("Enter Your Password: ");

            CurrentUser = clsUser::Find(Username, Password);

            LoginFaild = CurrentUser.IsEmpty();

        } while (LoginFaild);

        clsMainMenueScreen::ShowMainMenueScreen();
    }

public:

    static bool ShowLoginScreen()
    {
        system("cls");
        _DrawScreenHeader("Login Screen");
        return _Login();
    }

};

