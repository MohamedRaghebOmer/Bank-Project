#pragma once
#include <iostream>
#include "Base\clsScreen.h"
#include "Base\clsPerson.h"
#include "Base\clsBankClient.h"
#include "Lib's\clsInputValidate.h"
#include "Base\Global.h"

class clsFindClientScreen :protected clsScreen
{

private:
    static void _PrintClient(clsBankClient Client)
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << Client.FirstName;
        cout << "\nLastName    : " << Client.LastName;
        cout << "\nFull Name   : " << Client.FullName();
        cout << "\nEmail       : " << Client.Email;
        cout << "\nPhone       : " << Client.Phone;
        cout << "\nAcc.Number  : " << Client.AccountNumber();
        cout << "\nPassword    : " << Client.PinCode;
        cout << "\nBalance     : " << Client.AccountBalance;
        cout << "\n___________________\n";

    }

public:

    static void ShowFindClientScreen()
    {
        if (!CheckAccessRights(clsUser::enPermissions::pFindClient))
        {
            return;// this will exit the function and it will not continue
        }


        _DrawScreenHeader("Find Client Screen");

        string AccountNumber = clsInputValidate::ReadString("Please Enter Account Number: ");
        
        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "Account number is not found, please try again.\n" << endl;
            AccountNumber = clsInputValidate::ReadString("Please Enter Account Number: ");
        }

        clsBankClient Client1 = clsBankClient::Find(AccountNumber);

        if (!Client1.IsEmpty())
        {
            cout << "\nClient Found :-)\n";
        }
        else
        {
            cout << "\nClient Was not Found :-(\n";
        }

        _PrintClient(Client1);

    }

};

