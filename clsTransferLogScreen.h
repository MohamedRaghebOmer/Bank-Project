#pragma once
#include "clsScreen.h"

class clsTransferLogScreen : public clsScreen
{
private:

    static void _printOneLineInTable(const clsBankClient::stTransferLogRecord& oneLineInFile)
    {
        cout << setw(8) << left << "" << "| " << setw(23) << left << oneLineInFile.DateAndTime;
        cout << "| " << setw(8) << left << oneLineInFile.SourceAccountNumber;
        cout << "| " << setw(8) << left << oneLineInFile.DestinationAccountNumber;
        cout << "| " << setw(8) << left << oneLineInFile.Amount;
        cout << "| " << setw(10) << left << oneLineInFile.SourceBalanceAfter;
        cout << "| " << setw(10) << left << oneLineInFile.DestinationBalanceAfter;
        cout << "| " << setw(8) << left << oneLineInFile.Username;
    }

public:

    static void ShowTranferLog()
    {
        vector <clsBankClient::stTransferLogRecord> vList = 
            clsBankClient::GetTransferLogList();

        string title = "Transfer Log", subtilte = "[" + 
            to_string(vList.size()) + "] Transfer Operation(s).";
        
        _DrawScreenHeader(title, subtilte, true);

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;
        cout << setw(8) << left << "" << "| " << left << setw(23) << "Date/Time";
        cout << "| " << left << setw(8) << "s.Acct";
        cout << "| " << left << setw(8) << "d.Acct";
        cout << "| " << left << setw(8) << "Amount";
        cout << "| " << left << setw(10) << "s.Balance";
        cout << "| " << left << setw(10) << "d.Balance";
        cout << "| " << left << setw(8) << "User";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;
        
        if (vList.size() == 0)
            cout << "\t\t\t\tThere is No transfer operations" << endl;
        else
        {
            for (clsBankClient::stTransferLogRecord& Record : vList)
            {
                _printOneLineInTable(Record);
                cout << endl;
            }
        }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

    }
};

