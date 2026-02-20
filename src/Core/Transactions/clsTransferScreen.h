#pragma once
#include "D:\GitHub\Bank-Project\src\Base\clsScreen.h"

class clsTransferScreen : public clsScreen
{
private:

	static string _ReadAccountNumber(string Message = "Please enter account number to transfer from: ")
	{
		string AccountNumber = clsInputValidate::ReadString(Message);
		
		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "Account number you entered doesn't exist, please try again.\n\n";
			AccountNumber = clsInputValidate::ReadString(Message);
		}

		return AccountNumber;
	}

	static void _PrintClient(clsBankClient& Client)
	{

		cout << "\nClient Card:";
		cout << "\n___________________";
		cout << "\nFull Name   : " << Client.FullName();
		cout << "\nAcc.Number  : " << Client.AccountNumber();
		cout << "\nBalance     : " << Client.AccountBalance;
		cout << "\n___________________\n";

	}

public:

	static void ShowTransferScreen()
	{
		clsScreen::_DrawScreenHeader("Transfer Screen");

		clsBankClient TransferFrom = clsBankClient::Find(_ReadAccountNumber("Please enter account number to transfer from: "));
		_PrintClient(TransferFrom);

		cout << endl;
		
		clsBankClient TransferTo = clsBankClient::Find(_ReadAccountNumber("Please enter account number to transfer to: "));

		while (TransferTo.AccountNumber() == TransferFrom.AccountNumber())
		{
			cout << "Can't transfer to the same account number.\n\n";
			TransferTo = clsBankClient::Find(_ReadAccountNumber("Please enter account number to transfer to: "));
		}

		_PrintClient(TransferTo);

		// Read valid transfer amount
		float TransferAmount = clsInputValidate::ReadFloatNumberBetween
		(1, TransferFrom.AccountBalance, "\nEnter transfer amount: ", 
			true, "Amount must be greater than Zero, please try again\n\n");


		char sure = 'n';
		cout << "Are you sure, do you want to perform this operation? [Y|N]: ";
		cin >> sure;

		if (sure == 'y' || sure == 'Y')
		{
			TransferFrom.transfer(TransferTo, TransferAmount);
			
			cout << "\nTransfer Done Successfly." << endl;

			cout << "\nSender card after transfering:" << endl;
			_PrintClient(TransferFrom);

			cout << "Receiver card after transfering:" << endl;
			_PrintClient(TransferTo);

		}
	
	}


};

