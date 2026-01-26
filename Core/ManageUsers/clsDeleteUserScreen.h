#pragma once
#include <iostream>
#include "Base\clsScreen.h"
#include "Base\clsPerson.h"
#include "Base\clsUser.h"
#include "Base\Global.h"
#include "Lib's\clsInputValidate.h"
class clsDeleteUserScreen :protected clsScreen
{

private:

    static void _PrintUser(clsUser& User)
    {
        cout << "\nUser Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << User.FirstName;
        cout << "\nLastName    : " << User.LastName;
        cout << "\nFull Name   : " << User.FullName();
        cout << "\nEmail       : " << User.Email;
        cout << "\nPhone       : " << User.Phone;
        cout << "\nUser Name   : " << User.UserName;
        cout << "\nPassword    : " << User.Password;
        cout << "\nPermissions : " << User.Permissions;
        cout << "\n___________________\n";

    }

public:

    static void ShowDeleteUserScreen()
    {

        _DrawScreenHeader("Delete User Screen");

        string UserName = clsInputValidate::ReadString("Please Enter UserName: ");
        
        while (!clsUser::IsUserExist(UserName))
        {
            cout << "UserName is NOT found, please try again.\n\n";
            UserName = clsInputValidate::ReadString("\nPlease Enter UserName: ");
        }

        clsUser User1 = clsUser::Find(UserName);
        _PrintUser(User1);

        cout << "\nAre you sure you want to delete this User [Y|N]: ";

        char Answer = 'n';
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {

            if (User1.Delete())
            {
                cout << "\nUser Deleted Successfully :-)\n";
                _PrintUser(User1);
            }
            else
            {
                cout << "\nError User Was not Deleted\n";
            }
        }
    }

};

