#pragma once

#include <iostream>
#include "Base\clsScreen.h"
#include "Base\clsUser.h"
#include "Lib's\clsInputValidate.h"
#include <iomanip>
#include "Base\Global.h"

class clsAddNewUserScreen : protected clsScreen
{
private:

    static void _ReadUserInfo(clsUser& User)
    {
        User.FirstName = clsInputValidate::ReadString("Enter FirstName: ");

        User.LastName = clsInputValidate::ReadString("Enter LastName: ");

        User.Email = clsInputValidate::ReadString("Enter Email: ");

        User.Phone = clsInputValidate::ReadString("Enter Phone: ");

        User.Password = clsInputValidate::ReadString("Enter Password: ");

        cout << "\n\nEnter Permission: " << endl;
        User.Permissions = _ReadPermissionsToSet();
    }

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

    static short _ReadPermissionsToSet()
    {
        short Permissions = 0;
        char Answer = 'n';

        cout << "\nDo you want to give full access? [Y|N]: ";
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {
            return -1;
        }

        cout << "\nDo you want to give access to:" << endl;

        cout << "\nShow Client List? [Y|N]: ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pListClients;
        }

        cout << "\nAdd New Client? [Y|N]: ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pAddNewClient;
        }

        cout << "\nDelete Client? [Y|N]:  ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pDeleteClient;
        }

        cout << "\nUpdate Client? [Y|N]:  ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pUpdateClients;
        }

        cout << "\nFind Client? [Y|N]:  ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pFindClient;
        }

        cout << "\nTransactions? [Y|N]:  ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pTranactions;
        }

        cout << "\nManage Users? [Y|N]:  ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pManageUsers;
        }

        cout << "\nLogin Register? [Y|N]:  ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pLoginRegister;
        }

        return Permissions;
    }

public:

    static void ShowAddNewUserScreen()
    {

        _DrawScreenHeader("Add New User Screen");

        string UserName = clsInputValidate::ReadString("\nPlease Enter UserName: ");
        
        while (clsUser::IsUserExist(UserName))
        {
            cout << "UserName Is Already Used, try another one.\n\n";
            UserName = clsInputValidate::ReadString("\nPlease Enter UserName: ");
        }

        clsUser NewUser = clsUser::GetAddNewUserObject(UserName);

        _ReadUserInfo(NewUser);

        clsUser::enSaveResults SaveResult;

        SaveResult = NewUser.Save();

        switch (SaveResult)
        {
        case  clsUser::enSaveResults::svSucceeded:
        {
            cout << "\nUser Addeded Successfully :-)\n";
            _PrintUser(NewUser);
            break;
        }
        case clsUser::enSaveResults::svFaildEmptyObject:
        {
            cout << "\nError User was not saved because it's Empty";
            break;

        }
        case clsUser::enSaveResults::svFaildUserExists:
        {
            cout << "\nError User was not saved because UserName is used!\n";
            break;

        }
        }
    }
    
};

