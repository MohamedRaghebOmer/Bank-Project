#pragma once

#include <iostream>
#include <iomanip>
#include <fstream>
#include "D:\GitHub\Bank-Project\src\Base\clsScreen.h"
#include "D:\GitHub\Bank-Project\src\Base\clsUser.h"
#include "D:\GitHub\Bank-Project\src\Screens\clsMainMenueScreen.h"
#include "D:\GitHub\Bank-Project\src\Base\Global.h"
#include "D:\GitHub\Bank-Project\src\Lib's\clsDate.h"
#include "D:\GitHub\Bank-Project\src\Lib's\clsInputValidate.h"

class clsLoginScreen :protected clsScreen
{

private:

    static bool _Login()
    {
        bool LoginFaild = false;
        short AttemptsCounter = 3;

        string Username = "", Password = "";

        do
        {

            if (LoginFaild)
            {
			    AttemptsCounter--;
                cout << "Invlaid Username/Password!" << endl;

                if (AttemptsCounter == 1)
					cout << "\nYou have " << AttemptsCounter << " try to login.\n\n";
                else if (AttemptsCounter != 0)
				    cout << "\nYou have " << AttemptsCounter << " more tries to login.\n\n";
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

        CurrentUser.RegisterLogin();
        clsMainMenueScreen::ShowMainMenueScreen();
        
        return true;
    }

public:

    static bool ShowLoginScreen()
    {
        system("cls");
        _DrawScreenHeader("Login Screen");
        return _Login();
    }
};

