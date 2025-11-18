#include <iostream>
#include<fstream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

const string ClientsFileName = "Clients.txt";

void ShowMainMenueScreen();

struct stClient
{
    string AccountNumber;
    string PINCode;
    string Name;
    string Phone;
    double AccountBalance;
    bool MarkForDelete = false;
};

vector <string> SplitString(string Sentence, string Delim = " ")
{
    vector <string> vWord;

    size_t Pos = 0; // The position of Delim
    string Word = ""; // Empty string

    while ((Pos = Sentence.find(Delim)) != string::npos)
    {
        Word = Sentence.substr(0, Pos); // Stor word

        if (Word != "")
            vWord.push_back(Word);

        Sentence.erase(0, Pos + Delim.length()); // Delet printed word from string
    }

    if (Sentence != "")
        vWord.push_back(Sentence);

    return vWord;
}

stClient ConvertLineToRecord(string Line, string Seperator = "#//#")
{
    stClient C;
    vector <string> vClientData = SplitString(Line, Seperator);

    C.AccountNumber = vClientData[0];
    C.PINCode = vClientData[1];
    C.Name = vClientData[2];
    C.Phone = vClientData[3];
    C.AccountBalance = stod(vClientData[4]);

    return C;
}

string ConvertRecordToLine(stClient& C, string Seperator = "#//#")
{
    string ClientRecord = "";

    ClientRecord = C.AccountNumber + Seperator;
    ClientRecord += C.PINCode + Seperator;
    ClientRecord += C.Name + Seperator;
    ClientRecord += C.Phone + Seperator;
    ClientRecord += to_string(C.AccountBalance);

    return ClientRecord;
}

vector <stClient> LoadClientsDataFromFile(string FileName)
{
    vector <stClient> vClient;
    fstream MyFile;

    MyFile.open(FileName, ios::in);

    if (MyFile.is_open())
    {
        string Line = "";

        while (getline(MyFile, Line))
        {
            stClient C = ConvertLineToRecord(Line);
            vClient.push_back(C);
        }

        MyFile.close();
    }

    return vClient;
}

string ReadClientAccountNumber()
{
    string AccountNumber = "";

    cout << "\nPlease enter account number: ";
    cin >> AccountNumber;

    return AccountNumber;
}

bool IsAccountNumberExisted(string AccountNumber, vector <stClient>& vClient)
{
    for (stClient& C : vClient)
    {
        if (C.AccountNumber == AccountNumber)
            return true;
    }
    return false;
}

stClient ReadNewClient(vector <stClient>& vClient)
{
    stClient C;
    string AccountNumber = "";
    short Counter = 0;

    do
    {
        if (Counter > 0)
            cout << "Account Number [" << AccountNumber << "] is not avaliable, please try again.\n" << endl;

        cout << "Enter Account Number: ";
        getline(cin >> ws, AccountNumber);

        Counter++;

    } while (IsAccountNumberExisted(AccountNumber, vClient));

    C.AccountNumber = AccountNumber;

    cout << "Enter PIN Code: ";
    getline(cin, C.PINCode);

    cout << "Enter Name: ";
    getline(cin, C.Name);

    cout << "Enter Phone: ";
    getline(cin, C.Phone);

    cout << "Enter Account Balance: ";
    cin >> C.AccountBalance;
    cin.ignore();

    return C;
}

void SaveLineToFile(string ClientsFileName, string LineToAdd)
{
    fstream MyFile;
    MyFile.open(ClientsFileName, ios::out | ios::app);

    if (MyFile.is_open())
    {
        MyFile << LineToAdd << endl;

        MyFile.close();
    }
}

void AddNewClient()
{
    vector <stClient> vClient = LoadClientsDataFromFile(ClientsFileName);
    stClient C = ReadNewClient(vClient);

    SaveLineToFile(ClientsFileName, ConvertRecordToLine(C));
}

void AddNewClients()
{
    char AddMore = 'Y';

    do
    {
        cout << "\nAdd New Client:\n" << endl;
        AddNewClient();

        cout << "\nClient Added Successfully, Do you want to add more clients? [Y/N]" << endl;
        cin >> AddMore;

    } while (toupper(AddMore) == 'Y');
}

void ShowAddNewClientScreen()
{
    cout << "______________________________________" << endl;
    cout << "\n\tAdd New Client Screen" << endl;
    cout << "______________________________________" << endl;

    AddNewClients();
}

void PrintClientRecord(stClient C)
{
    cout << "|" << setw(15) << left << C.AccountNumber;
    cout << "|" << setw(10) << left << C.PINCode;
    cout << "|" << setw(30) << left << C.Name;
    cout << "|" << setw(17) << left << C.Phone;
    cout << "|" << setw(10) << left << C.AccountBalance;
}

void PrintClientCard(stClient Client)
{
    cout << "\nThe following is the extracted client record:" << endl;
    cout << "\nAccount Number : " << Client.AccountNumber << endl;
    cout << "PIN Code       : " << Client.PINCode << endl;
    cout << "Name           : " << Client.Name << endl;
    cout << "Phone          : " << Client.Phone << endl;
    cout << "Account Balance: " << Client.AccountBalance << endl;
}

void ShowClientsList()
{
    vector <stClient> vClient = LoadClientsDataFromFile(ClientsFileName);

    cout << "\n\t\t\t\tClient List (" << vClient.size() << ") Client(s)." << endl;
    cout << "_____________________________________________________________________________________" << endl;
    cout << "\n|" << setw(15) << left << "Account Number";
    cout << "|" << setw(10) << left << "PIN Code";
    cout << "|" << setw(30) << left << "Client Name";
    cout << "|" << setw(17) << left << "Phone";
    cout << "|" << setw(10) << left << "Balance ";
    cout << "\n_____________________________________________________________________________________\n" << endl;

    for (stClient& C : vClient)
    {
        PrintClientRecord(C);
        cout << endl;
    }

    cout << "_____________________________________________________________________________________" << endl;
}

bool FindClientByAccountNumber(string AccountNumber, vector <stClient>& vClient, stClient& Client)
{
    for (stClient& C : vClient)
    {
        if (C.AccountNumber == AccountNumber)
        {
            Client = C;
            return true;
        }
    }
    return false;
}

void ShowFindClientScreen()
{
    cout << "______________________________________" << endl;
    cout << "\n\tFind Client Screen" << endl;
    cout << "______________________________________" << endl;

    string AccountNumber = ReadClientAccountNumber();
    vector <stClient> vClient = LoadClientsDataFromFile(ClientsFileName);
    stClient Client;

    if ((FindClientByAccountNumber(AccountNumber, vClient, Client)))
    {
        PrintClientCard(Client);
    }
    else
    {
        cout << "\nClient with Account Number[" << AccountNumber << "] is not found!";
    }
}

bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector <stClient>& vClient)
{
    for (stClient& c : vClient)
    {
        if (AccountNumber == c.AccountNumber)
        {
            c.MarkForDelete = true;
            return true;
        }
    }

    return false;
}

bool SaveClientDataToFile(string FileName, vector <stClient>& vClient)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out);

    if (MyFile.is_open())
    {
        for (stClient& C : vClient)
        {
            if (C.MarkForDelete == false)
            {
                string Line = ConvertRecordToLine(C);
                MyFile << Line << endl;
            }
        }

        MyFile.close();
        return true;
    }

    return false;
}

stClient ChangeClientRecord(string AccountNumber)
{
    stClient C;

    C.AccountNumber = AccountNumber;

    cout << "\nEnter PIN Code: ";
    getline(cin >> ws, C.PINCode);

    cout << "Enter Name: ";
    getline(cin, C.Name);

    cout << "Enter Phone: ";
    getline(cin, C.Phone);

    cout << "Enter Account Balance: ";
    cin >> C.AccountBalance;
    cin.ignore();

    return C;
}

bool DeleteClientByAccountNumber(string AccountNumber, vector <stClient> &vClient)
{
    stClient Client;
    char Sure = 'n';
    short Counter = 0;

    while (!FindClientByAccountNumber(AccountNumber, vClient, Client))
    {
        cout << "Account Number [" << AccountNumber << "] is not existed." << endl;
        cout << "\nplease try again: ";
        cin >> AccountNumber;
    }

    PrintClientCard(Client); // Client stored here by 'FindClientByAccountNumber' function in line 335

    cout << "\nAre you sure you want to delete this client? [Y|N]" << endl;
    cin >> Sure;

    if (toupper(Sure) == 'Y')
    {
        MarkClientForDeleteByAccountNumber(AccountNumber, vClient);
        SaveClientDataToFile(ClientsFileName, vClient);

        cout << "\nClient deleted Successfully." << endl;

        return true;
    }
    else
    {
        return false;
    }
}

void ShowDeleteClientScreen()
{
    cout << "______________________________________" << endl;
    cout << "\n\tDelete Client Screen" << endl;
    cout << "______________________________________" << endl;

    vector <stClient> vClient = LoadClientsDataFromFile(ClientsFileName);
    string AccounNumber = ReadClientAccountNumber();

    DeleteClientByAccountNumber(AccounNumber, vClient);
}

bool UpdateClientByAccountNumber(string AccountNumber, vector <stClient> &vClient)
{
    stClient Client;
    char Sure = 'n';

    if (FindClientByAccountNumber(AccountNumber, vClient, Client))
    {
        PrintClientCard(Client);

        cout << "\nAre you sure you want to update this client? [Y|N]" << endl;
        cin >> Sure;

        if (toupper(Sure) == 'Y')
        {
            for (stClient& C : vClient)
            {
                if (C.AccountNumber == AccountNumber)
                {
                    C = ChangeClientRecord(AccountNumber);
                    break;
                }
            }

            SaveClientDataToFile(ClientsFileName, vClient);

            cout << "\nChanges applied successfully." << endl;
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        cout << "Client with account number \'" << AccountNumber << "\' is not found." << endl;
        return false;
    }
}

void ShowUpdateClientInfoScreen()
{
    cout << "______________________________________" << endl;
    cout << "\n\tUpdate Client Info Screen" << endl;
    cout << "______________________________________" << endl;

    vector <stClient> vClient = LoadClientsDataFromFile(ClientsFileName);
    string AccounNumber = ReadClientAccountNumber();

    UpdateClientByAccountNumber(AccounNumber, vClient);
}

void ShowEndScreen()
{
    cout << "______________________________________" << endl;
    cout << "\n\tProgram Ended :-)" << endl;
    cout << "______________________________________" << endl;
}

enum enMainMenueOptions
{
    eShowClientLest = 1,
    eAddNewClient = 2,
    eDeleteClient = 3,
    eUpdateClientInfo = 4,
    eFindClient = 5,
    eExit = 6
};

void GoBackToMainMenue()
{
    cout << "\n\nPress any key to go to main menue.....";
    system("pause>0");
    system("cls");
    ShowMainMenueScreen();
}

short ReadMainMenueChoose()
{
    short UserChoose = 0;
    short Counter = 1;

    do
    {
        if (Counter == 1)
        {
            cout << "Choose what do you want to do [1 To 6]: ";
            cin >> UserChoose;
        }
        else
        {
            cout << "Invalid choose, please try again: ";
            cin >> UserChoose;
        }
        

    } while (UserChoose < 1 || UserChoose > 6);

    return UserChoose;
}

void PerfromMainMenueChoose(enMainMenueOptions MainMenueOptions)
{
    switch (MainMenueOptions)
    {
    case enMainMenueOptions::eShowClientLest: 
    {
        system("cls");
        ShowClientsList();
        GoBackToMainMenue();
        break;
    }
    case enMainMenueOptions::eAddNewClient:
    {
        system("cls");
        ShowAddNewClientScreen();
        GoBackToMainMenue();
        break;
    }
    case enMainMenueOptions::eDeleteClient:
    {
        system("cls");
        ShowDeleteClientScreen();
        GoBackToMainMenue();
        break;
    }
    case enMainMenueOptions::eUpdateClientInfo:
    {
        system("cls");
        ShowUpdateClientInfoScreen();
        GoBackToMainMenue();
        break;
    }
    case enMainMenueOptions::eFindClient:
    {
        system("cls");
        ShowFindClientScreen();
        GoBackToMainMenue();
        break;
    }
    case enMainMenueOptions::eExit:
    {
        system("cls");
        ShowEndScreen();
        break;
    }
    }
}

void ShowMainMenueScreen()
{
    cout << "======================================================" << endl;
    cout << "\t\tMain Menue Screen" << endl;
    cout << "======================================================" << endl;
    cout << "[1] Show Client List." << endl;
    cout << "[2] Add New Client." << endl;
    cout << "[3] Delete Client." << endl;
    cout << "[4] Update Client Info." << endl;
    cout << "[5] Find Client." << endl;
    cout << "[6] Exit." << endl;
    cout << "======================================================" << endl;
    PerfromMainMenueChoose((enMainMenueOptions)ReadMainMenueChoose());
}

int main()
{
    ShowMainMenueScreen();
    system("pause>0");

    return 0;
}