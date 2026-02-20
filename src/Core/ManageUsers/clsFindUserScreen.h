#pragma once
#include <iostream>
#include "D:\GitHub\Bank-Project\src\Base\clsScreen.h"
#include "D:\GitHub\Bank-Project\src\Base\clsPerson.h"
#include "D:\GitHub\Bank-Project\src\Base\clsUser.h"
#include "D:\GitHub\Bank-Project\src\Base\Global.h"
#include "D:\GitHub\Bank-Project\src\Lib's\clsInputValidate.h"
class clsFindUserScreen :protected clsScreen
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
        cout << "\nUserName    : " << User.UserName;
        cout << "\nPassword    : " << User.Password;
        cout << "\nPermissions : " << User.Permissions;
        cout << "\n___________________\n";

    }

public:

    static void ShowFindUserScreen()
    {

        _DrawScreenHeader("Find User Screen");

        string UserName = clsInputValidate::ReadString("Please Enter UserName: ");
        
        while (!clsUser::IsUserExist(UserName))
        {
            cout << "User is not found, please try again.\n\n";
            UserName = clsInputValidate::ReadString("Please Enter UserName: ");
        }

        clsUser User1 = clsUser::Find(UserName);

        if (!User1.IsEmpty())
        {
            cout << "\nUser Found :-)\n";
        }
        else
        {
            cout << "\nUser Was not Found :-(\n";
        }

        _PrintUser(User1);

    }

};

