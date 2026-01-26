#pragma once
#include <iostream>
#include "Base\clsScreen.h"
#include "Base\clsPerson.h"
#include "Base\clsBankClient.h"
#include "Lib's\clsInputValidate.h"
#include "Base\Global.h"

class clsUpdateClientScreen : protected clsScreen

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

    static void _ReadClientInfo(clsBankClient& Client)
    {
        Client.FirstName = clsInputValidate::ReadString("Enter FirstName: ");

        Client.LastName = clsInputValidate::ReadString("Enter LastName: ");

        Client.Email = clsInputValidate::ReadString("Enter Email: ");

        Client.Phone = clsInputValidate::ReadString("Enter Phone: ");

        Client.PinCode = clsInputValidate::ReadString("Enter PinCode: ");

        Client.AccountBalance = clsInputValidate::ReadPositiveFloat(true, "Enter Account Balance: ", "Invalid Balance, you have to enter a positive number\n\n");
    }

public:

    static void ShowUpdateClientScreen()
    {
        if (!CheckAccessRights(clsUser::enPermissions::pUpdateClients))
        {
            return;// this will exit the function and it will not continue
        }

        _DrawScreenHeader("Update Client Screen");

        string AccountNumber = clsInputValidate::ReadString("Please Enter client Account Number: ");

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "Account number is not found, please try again.\n\n";
            AccountNumber = clsInputValidate::ReadString("Please Enter client Account Number: ");
        }

        clsBankClient Client1 = clsBankClient::Find(AccountNumber);

        _PrintClient(Client1);

        cout << "\nAre you sure you want to update this client [Y|N]: ";

        char Answer = 'n';
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {

            cout << "\n\nUpdate Client Info:";
            cout << "\n____________________\n";


            _ReadClientInfo(Client1);

            clsBankClient::enSaveResults SaveResult;

            SaveResult = Client1.Save();

            switch (SaveResult)
            {
            case  clsBankClient::enSaveResults::svSucceeded:
            {
                cout << "\nAccount Updated Successfully :-)\n";

                _PrintClient(Client1);
                break;
            }
            case clsBankClient::enSaveResults::svFaildEmptyObject:
            {
                cout << "\nError account was not saved because it's Empty";
                break;

            }

            }

        }

    }
};

