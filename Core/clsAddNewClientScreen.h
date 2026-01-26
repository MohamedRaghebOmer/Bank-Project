#pragma once

#include <iostream>
#include "Base\clsScreen.h"
#include "Base\clsBankClient.h"
#include "Lib's\clsInputValidate.h"
#include <iomanip>
#include "Base\Global.h"

class clsAddNewClientScreen : public clsScreen
{
private:
    static void _ReadClientInfo(clsBankClient& Client)
    {
        Client.FirstName = clsInputValidate::ReadString("Enter FirstName: ");

        Client.LastName = clsInputValidate::ReadString("Enter LastName: ");

        Client.Email = clsInputValidate::ReadString("Enter Email: ");

        Client.Phone = clsInputValidate::ReadString("Enter Phone: ");

        Client.PinCode = clsInputValidate::ReadString("Enter PinCode: ");

        Client.AccountBalance = clsInputValidate::ReadPositiveFloat(true, "Enter Account Balance: ", "Invalid Balance, you have to enter a positive number\n\n");
    }

    static void _PrintClient(clsBankClient Client)
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << Client.FirstName;
        cout << "\nLastName    : " << Client.LastName;
        cout << "\nFull Name   : " << Client.FullName();
        cout << "\nEmail       : " << Client.Email;
        cout << "\nPhone       : " << Client.Phone;
        cout << "\nAcc. Number : " << Client.AccountNumber();
        cout << "\nPassword    : " << Client.PinCode;
        cout << "\nBalance     : " << Client.AccountBalance;
        cout << "\n___________________\n";

    }

public:

    static void ShowAddNewClientScreen()
    {
        if (!CheckAccessRights(clsUser::enPermissions::pAddNewClient))
        {
            return;// this will exit the function and it will not continue
        }

        _DrawScreenHeader("Add New Client Screen");

        string AccountNumber = clsInputValidate::ReadString("Please Enter Account Number : ");

        while (clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "Account Number Is Already Used, Choose another one." << endl;
            AccountNumber = clsInputValidate::ReadString("\nPlease Enter Account Number: ");
        }

        clsBankClient NewClient = clsBankClient::GetAddNewClientObject(AccountNumber);


        _ReadClientInfo(NewClient);

        clsBankClient::enSaveResults SaveResult;

        SaveResult = NewClient.Save();

        switch (SaveResult)
        {
        case  clsBankClient::enSaveResults::svSucceeded:
        {
            cout << "\nAccount Addeded Successfully :-)\n";
            _PrintClient(NewClient);
            break;
        }
        case clsBankClient::enSaveResults::svFaildEmptyObject:
        {
            cout << "\nError account was not saved because it's Empty";
            break;

        }
        case clsBankClient::enSaveResults::svFaildAccountNumberExists:
        {
            cout << "\nError account was not saved because account number is used!\n";
            break;

        }
        }
    }



};

