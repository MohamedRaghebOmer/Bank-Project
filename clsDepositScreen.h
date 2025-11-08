#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "Global.h"
class clsDepositScreen : protected clsScreen
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

    static void ShowDepositScreen()
    {
        _DrawScreenHeader("Deposit Screen");

        string AccountNumber = clsInputValidate::ReadString("Please enter account number: ");

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "Client with [" << AccountNumber << "] does not exist, please try again.\n\n";
            AccountNumber = clsInputValidate::ReadString("Please enter account number: ");
        }

        clsBankClient Client1 = clsBankClient::Find(AccountNumber);
        _PrintClient(Client1);

        double Amount = clsInputValidate::ReadPositiveFloat(false, "Please enter deposit amount: ", "Invalid amount, please enter a positive number.\n\n");

        cout << "\nAre you sure you want to perform this transaction? [Y|N]: ";
        char Answer = 'n';
        cin >> Answer;

        if (Answer == 'Y' || Answer == 'y')
        {
            Client1.Deposit(Amount);
            cout << "\nAmount Deposited Successfully." << endl;
            cout << "\nNew Balance Is: " << Client1.AccountBalance << endl;

        }
        else
        {
            cout << "\nOperation was cancelled.\n";
        }

    }

};

