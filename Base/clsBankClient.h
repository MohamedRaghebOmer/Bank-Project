#pragma once
#include <iostream>
#include <string>
#include "Base\clsPerson.h"
#include "Lib's\clsString.h"
#include <vector>
#include <fstream>
#include "Base\Global.h"

class clsBankClient : public clsPerson
{
private:

    enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
    enMode _Mode;


    string _AccountNumber;
    string _PinCode;
    float _AccountBalance;
    bool _MarkedForDelete = false;



    static clsBankClient _ConvertLinetoClientObject(const string& Line, const string& Seperator = "#//#")
    {
        vector<string> vClientData = clsString::Split(Line, Seperator);

        return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2],
            vClientData[3], vClientData[4], vClientData[5], stod(vClientData[6]));

    }

    static string _ConverClientObjectToLine(clsBankClient Client, const string& Seperator = "#//#")
    {

        string stClientRecord = "";

        stClientRecord += Client.FirstName + Seperator;
        stClientRecord += Client.LastName + Seperator;
        stClientRecord += Client.Email + Seperator;
        stClientRecord += Client.Phone + Seperator;
        stClientRecord += Client.AccountNumber() + Seperator;
        stClientRecord += Client.PinCode + Seperator;
        stClientRecord += to_string(Client.AccountBalance);

        return stClientRecord;

    }

    static  vector <clsBankClient> _LoadClientsDataFromFile()
    {

        vector <clsBankClient> vClients;

        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {

            string Line = "";

            while (getline(MyFile, Line))
            {

                clsBankClient Client = _ConvertLinetoClientObject(Line);

                vClients.push_back(Client);
            }

            MyFile.close();

        }

        return vClients;

    }

    static void _SaveCleintsDataToFile(vector <clsBankClient>& vClients)
    {

        fstream MyFile;
        MyFile.open("Clients.txt", ios::out);//overwrite

        string DataLine = "";

        if (MyFile.is_open())
        {

            for (clsBankClient& C : vClients)
            {
                if (C.MarkedForDeleted() == false)
                {
                    //we only write records that are not marked for delete.  
                    DataLine = _ConverClientObjectToLine(C);
                    MyFile << DataLine << endl;

                }

            }

            MyFile.close();

        }

    }

    void _Update()
    {
        vector <clsBankClient> _vClients = _LoadClientsDataFromFile();

        for (clsBankClient& C : _vClients)
        {
            if (C.AccountNumber() == AccountNumber())
            {
                C = *this;
                break;
            }

        }

        _SaveCleintsDataToFile(_vClients);

    }

    void _AddNew()
    {
        _AddDataLineToFile(_ConverClientObjectToLine(*this));
    }

    void _AddDataLineToFile(const string& stDataLine)
    {
        fstream MyFile;
        MyFile.open("Clients.txt", ios::out | ios::app);

        if (MyFile.is_open())
        {

            MyFile << stDataLine << endl;

            MyFile.close();
        }

    }

    static clsBankClient _GetEmptyClientObject()
    {
        return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
    }

    string _prepareTransferLine(clsBankClient& TransferTo, float amount, const string& Seprator = "#//#")
    {
        return clsDate::GetSystemDateAndTime() + Seprator + AccountNumber() +
            Seprator + TransferTo.AccountNumber() + Seprator + to_string(amount) +
            Seprator + to_string(AccountBalance) + Seprator +
            to_string(TransferTo.AccountBalance) + Seprator + CurrentUser.UserName;

    }

    void _registerTransfer(clsBankClient& TransferTo, float amount)
    {
        fstream myFile;
        myFile.open("transfer_log.txt", ios::out | ios::app);

        if (myFile.is_open())
        {
            string registerLine = _prepareTransferLine(TransferTo, amount);

            myFile << registerLine << endl;

            myFile.close();
        }

    }

    struct stTransferLogRecord;
    static stTransferLogRecord _lineToTransferLogRecord(const string& line, const string& Dilem = "#//#")
    {
        stTransferLogRecord Recored;
        vector <string> vList = clsString::Split(line, Dilem);

        if (vList.size() == 7)
        {
            Recored.DateAndTime = vList[0];
            Recored.SourceAccountNumber = vList[1];
            Recored.DestinationAccountNumber = vList[2];
            Recored.Amount = stod(vList[3]);
            Recored.SourceBalanceAfter = stod(vList[4]);
            Recored.DestinationBalanceAfter = stod(vList[5]);
            Recored.Username = vList[6];
        }

        return Recored;

    }

public:

    struct stTransferLogRecord
    {
        string DateAndTime;
        string SourceAccountNumber;
        string DestinationAccountNumber;
        float Amount;
        float SourceBalanceAfter;
        float DestinationBalanceAfter;
        string Username;
    };

    clsBankClient(enMode Mode, const string& FirstName, const string& LastName,
        string Email, const string& Phone, const string& AccountNumber, const string& PinCode,
        float AccountBalance) :
        clsPerson(FirstName, LastName, Email, Phone)

    {
        _Mode = Mode;
        _AccountNumber = AccountNumber;
        _PinCode = PinCode;
        _AccountBalance = AccountBalance;

    }

    bool IsEmpty()
    {
        return (_Mode == enMode::EmptyMode);
    }

    bool MarkedForDeleted()
    {
        return _MarkedForDelete;
    }

    string AccountNumber()
    {
        return _AccountNumber;
    }

    void SetPinCode(const string& PinCode)
    {
        _PinCode = PinCode;
    }

    string GetPinCode()
    {
        return _PinCode;
    }
    __declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;

    void SetAccountBalance(float AccountBalance)
    {
        _AccountBalance = AccountBalance;
    }

    float GetAccountBalance()
    {
        return _AccountBalance;
    }
    __declspec(property(get = GetAccountBalance, put = SetAccountBalance)) float AccountBalance;

    /*
    * No UI related inside object
    void Print()
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << FirstName;
        cout << "\nLastName    : " << LastName;
        cout << "\nFull Name   : " << FullName();
        cout << "\nEmail       : " << Email;
        cout << "\nPhone       : " << Phone;
        cout << "\nAcc. Number : " << _AccountNumber;
        cout << "\nPassword    : " << _PinCode;
        cout << "\nBalance     : " << _AccountBalance;
        cout << "\n___________________\n";

    }*/

    static clsBankClient Find(const string& AccountNumber)
    {
        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line = "";

            while (getline(MyFile, Line))
            {
                clsBankClient Client = _ConvertLinetoClientObject(Line);
                if (Client.AccountNumber() == AccountNumber)
                {
                    MyFile.close();
                    return Client;
                }

            }

            MyFile.close();

        }

        return _GetEmptyClientObject();
    }

    static clsBankClient Find(const string& AccountNumber, const string& PinCode)
    {
        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line = "";

            while (getline(MyFile, Line))
            {
                clsBankClient Client = _ConvertLinetoClientObject(Line);
                if (Client.AccountNumber() == AccountNumber && Client.PinCode == PinCode)
                {
                    MyFile.close();
                    return Client;
                }

            }

            MyFile.close();

        }
        return _GetEmptyClientObject();
    }


    enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildAccountNumberExists = 2 };
    
    enSaveResults Save()
    {
        switch (_Mode)
        {
        case enMode::EmptyMode:
        {
            if (IsEmpty())
            {
                return enSaveResults::svFaildEmptyObject;
            }
        }

        case enMode::UpdateMode:
        {
            _Update();
            return enSaveResults::svSucceeded;
        }

        case enMode::AddNewMode:
        {
            //This will add new record to file or database
            if (clsBankClient::IsClientExist(_AccountNumber))
            {
                return enSaveResults::svFaildAccountNumberExists;
            }
            else
            {
                _AddNew();

                //We need to set the mode to update after add new
                _Mode = enMode::UpdateMode;
                return enSaveResults::svSucceeded;
            }
        }
        }
    }

    static bool IsClientExist(const string& AccountNumber)
    {
        clsBankClient Client1 = clsBankClient::Find(AccountNumber);
        return (!Client1.IsEmpty());
    }

    bool Delete()
    {
        vector <clsBankClient> _vClients = _LoadClientsDataFromFile();

        for (clsBankClient& C : _vClients)
        {
            if (C.AccountNumber() == _AccountNumber)
            {
                C._MarkedForDelete = true;
                break;
            }

        }

        _SaveCleintsDataToFile(_vClients);

        *this = _GetEmptyClientObject();

        return true;

    }

    static clsBankClient GetAddNewClientObject(const string& AccountNumber)
    {
        return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
    }

    static vector <clsBankClient> GetClientsList()
    {
        return _LoadClientsDataFromFile();
    }

    static float GetTotalBalances()
    {
        vector <clsBankClient> vClients = clsBankClient::GetClientsList();

        double TotalBalances = 0;

        for (clsBankClient& Client : vClients)
        {

            TotalBalances += Client.AccountBalance;
        }

        return TotalBalances;

    }

    void Deposit(double Amount)
    {
        _AccountBalance += Amount;
        Save();
    }

    bool Withdraw(double Amount)
    {
        if (Amount > _AccountBalance)
        {
            return false;
        }
        else
        {
            _AccountBalance -= Amount;
            Save();
            return true;
        }

    }

    bool transfer(clsBankClient& DestinationClient, float amount)
    {
        if (DestinationClient.AccountNumber() == AccountNumber() || amount > AccountBalance)
        {
            return false;
        }
        else
        {
            DestinationClient.Deposit(amount);
            Withdraw(amount);
            _registerTransfer(DestinationClient, amount);
            return true;
        }

    }

    static vector <stTransferLogRecord> GetTransferLogList()
    {
        fstream myFile;
        myFile.open("transfer_log.txt", ios::in);

        vector <stTransferLogRecord> vList;

        if (myFile.is_open())
        {
            string lineInFile = "";
            
            while (getline(myFile, lineInFile))
            {
                vList.push_back(_lineToTransferLogRecord(lineInFile));
                lineInFile = "";
            }

            myFile.close();
        }

        return vList;
    }
};

