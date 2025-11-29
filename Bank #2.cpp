#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

const string ClientsFileName = "Clients.txt";
const string UsersFileName = "Users.txt";

void ShowMainMenueScreen();
void ShowTransactionsMenueScreen();
void ShowManageUserScreen();
void ShowLoginScreen();

string GlobalUsername = "";

const short gShowClientList = 1 << 0;
const short gAddNewClient = 1 << 1;
const short gDeleteClient = 1 << 2;
const short gUpdateClient = 1 << 3;
const short gFindClient = 1 << 4;
const short gTransactions = 1 << 5;
const short gManageUsers = 1 << 6;

struct stClient
{
    string AccountNumber;
    string PINCode;
    string Name;
    string Phone;
    double AccountBalance;
    bool MarkForDelete = false;
};

enum enMainMenueOptions
{
    eShowClientList = 1,
    eAddNewClient = 2,
    eDeleteClient = 3,
    eUpdateClientInfo = 4,
    eFindClient = 5,
    eTransactions = 6,
    eManageUsers = 7,
    eLogout = 8
};

enum enTransactionsMenueOptions
{
    eDeposit = 1,
    eWithdraw = 2,
    eTotalBalance = 3,
    eMainMenue = 4
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

string ConvertClientRecordToLine(stClient& C, string Seperator = "#//#")
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
                string Line = ConvertClientRecordToLine(C);
                MyFile << Line << endl;
            }
        }

        MyFile.close();
        return true;
    }

    return false;
}

void SaveLineToFile(string fileName, string LineToAdd)
{
    fstream MyFile;
    MyFile.open(fileName, ios::out | ios::app);

    if (MyFile.is_open())
    {
        MyFile << LineToAdd << endl;

        MyFile.close();
    }
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

void AddNewClient()
{
    vector <stClient> vClient = LoadClientsDataFromFile(ClientsFileName);
    stClient C = ReadNewClient(vClient);

    SaveLineToFile(ClientsFileName, ConvertClientRecordToLine(C));
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

void PrintClientCard(stClient Client)
{
    cout << "\nThe following is the extracted client record:" << endl;
    cout << "\nAccount Number : " << Client.AccountNumber << endl;
    cout << "PIN Code       : " << Client.PINCode << endl;
    cout << "Name           : " << Client.Name << endl;
    cout << "Phone          : " << Client.Phone << endl;
    cout << "Account Balance: " << Client.AccountBalance << endl;
}

void ShowFindClientScreen()
{
    cout << "______________________________________" << endl;
    cout << "\n\tFind Client Screen" << endl;
    cout << "______________________________________" << endl;

    string AccountNumber = ReadClientAccountNumber();
    vector <stClient> vClient = LoadClientsDataFromFile(ClientsFileName);
    stClient Client;

    while (!FindClientByAccountNumber(AccountNumber, vClient, Client))
    {
        cout << "Account Number [" << AccountNumber << "] is not existed." << endl;
        cout << "\nplease try again: ";
        cin >> AccountNumber;
    }

    PrintClientCard(Client);
}

void PrintClientRecord(stClient Client)
{
    cout << "|" << setw(15) << left << Client.AccountNumber;
    cout << "|" << setw(10) << left << Client.PINCode;
    cout << "|" << setw(30) << left << Client.Name;
    cout << "|" << setw(17) << left << Client.Phone;
    cout << "|" << setw(10) << left << Client.AccountBalance;
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

bool UpdateClientByAccountNumber(string AccountNumber, vector <stClient>& vClient)
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

void ShowUpdateClientInfoScreen()
{
    cout << "______________________________________" << endl;
    cout << "\n\tUpdate Client Info Screen" << endl;
    cout << "______________________________________" << endl;

    vector <stClient> vClient = LoadClientsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();

    UpdateClientByAccountNumber(AccountNumber, vClient);
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

bool DeleteClientByAccountNumber(string AccountNumber, vector <stClient>& vClient)
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
    string AccountNumber = ReadClientAccountNumber();

    DeleteClientByAccountNumber(AccountNumber, vClient);
}

double CalculateTotalBalances(vector <stClient>& vClient)
{
    double TotalBalances = 0;

    for (stClient& C : vClient)
    {
        TotalBalances += C.AccountBalance;
    }

    return TotalBalances;
}

void PrintClientBalance(stClient Client)
{
    cout << "|" << setw(15) << left << Client.AccountNumber;
    cout << "|" << setw(30) << left << Client.Name;
    cout << "|" << setw(10) << left << Client.AccountBalance;
}

void PrintBalancesTable()
{
    vector <stClient> vClient = LoadClientsDataFromFile(ClientsFileName);

    cout << "\t\t\t\tBalances List (" << vClient.size() << ") Client(s)" << endl;
    cout << "_____________________________________________________________________________________" << endl;
    cout << "\n|" << setw(15) << left << "Account Number";
    cout << "|" << setw(30) << left << "Client Name";
    cout << "|" << setw(10) << left << "Balance ";
    cout << "\n_____________________________________________________________________________________\n" << endl;

    for (stClient& Client : vClient)
    {
        PrintClientBalance(Client);
        cout << endl;
    }

    cout << "_____________________________________________________________________________________" << endl;
}

void ShowTotalBalancesScreen()
{
    vector <stClient> vClient = LoadClientsDataFromFile(ClientsFileName);

    PrintBalancesTable();
    cout << "\n\t\t\t\tTotal Balances = " << CalculateTotalBalances(vClient) << endl;
}

double ReadWithdrawAmount(stClient& Client)
{
    double Amount = 0;

    while (true)
    {
        cout << "\nEnter Withdraw Amount: ";
        cin >> Amount;

        if (Amount < 1)
        {
            cout << "Amount must be greater than 0, please try again.\n";
        }
        else if (Amount > Client.AccountBalance)
        {
            cout << "No enough balance, please try again.\n";
        }
        else
        {
            break;
        }
    }

    return Amount;
}

bool WithdrawToClientByNumberAccount(string AccountNumber)
{
    vector <stClient> vClient = LoadClientsDataFromFile(ClientsFileName);
    double WithdrawAmount = 0;
    char Sure = 'n';

    while (!IsAccountNumberExisted(AccountNumber, vClient))
    {
        cout << "Account Number [" << AccountNumber << "] is not existed." << endl;
        cout << "\nplease try again: ";
        cin >> AccountNumber;
    }

    for (stClient& Client : vClient)
    {
        if (Client.AccountNumber == AccountNumber)
        {

            PrintClientCard(Client);
            WithdrawAmount = ReadWithdrawAmount(Client);

            cout << "\nAre you sure you want to perform this transaction? [Y|N]" << endl;
            cin >> Sure;

            if (toupper(Sure) == 'Y')
            {
                Client.AccountBalance -= WithdrawAmount;
                SaveClientDataToFile(ClientsFileName, vClient);

                cout << "\nWithdraw done Successfully." << endl;
                cout << "Account balance is: " << Client.AccountBalance << endl;

                return true;
            }
            else
                return false;
        }
    }

    return false;
}

void ShowWithdrawScreen()
{
    cout << "______________________________________" << endl;
    cout << "\n\tWithdraw Screen" << endl;
    cout << "______________________________________" << endl;

    string AccountNumber = ReadClientAccountNumber();
    WithdrawToClientByNumberAccount(AccountNumber);
}

double ReadDepositAmount()
{
    double Amount = 0;

    cout << "Enter Deposit Amount: ";
    cin >> Amount;

    while (Amount < 1)
    {
        cout << "Amount must be greater than 0, please try again: ";
        cin >> Amount;
    }

    return Amount;
}

bool DepositToClientByNumberAccount(string AccountNumber)
{
    vector <stClient> vClient = LoadClientsDataFromFile(ClientsFileName);
    double DepositAmount = 0;
    char Sure = 'n';

    while (!IsAccountNumberExisted(AccountNumber, vClient))
    {
        cout << "Account Number [" << AccountNumber << "] is not existed." << endl;
        cout << "\nplease try again: ";
        cin >> AccountNumber;
    }

    for (stClient& Client : vClient)
    {
        if (Client.AccountNumber == AccountNumber)
        {
            PrintClientCard(Client);
            cout << endl;
            DepositAmount = ReadDepositAmount();

            cout << "\nAre you sure you want to perform this transaction? [Y|N]" << endl;
            cin >> Sure;

            if (toupper(Sure) == 'Y')
            {
                Client.AccountBalance += DepositAmount;
                SaveClientDataToFile(ClientsFileName, vClient);

                cout << "\nDiposit done Successfully." << endl;
                cout << "Account balance is: " << Client.AccountBalance << endl;

                return true;
            }
            else
                return false;
        }
    }

    return false;
}

void ShowDepositScreen()
{
    cout << "______________________________________" << endl;
    cout << "\n\tDeposit Screen" << endl;
    cout << "______________________________________" << endl;

    string AccountNumber = ReadClientAccountNumber();
    DepositToClientByNumberAccount(AccountNumber);
}

void GoBackToTransactionsMenue()
{
    cout << "\n\nPress any key to go to main menue.....";
    system("pause>0");
    system("cls");
    ShowTransactionsMenueScreen();
}

short ReadTransactionsMenueChoose()
{
    short UserChoose = 0;

    cout << "Choose what do you want to do [1 To 4]: ";
    cin >> UserChoose;

    while (UserChoose < 1 || UserChoose > 4)
    {
        cout << "Invalid choose, please try again: ";
        cin >> UserChoose;
    } ;

    return UserChoose;
}

void PerformTransactionsMenueChoose(enTransactionsMenueOptions TransactionsMenueOptions)
{
    switch (TransactionsMenueOptions)
    {
    case enTransactionsMenueOptions::eDeposit:
    {
        system("cls");
        ShowDepositScreen();
        GoBackToTransactionsMenue();
        break;
    }
    case enTransactionsMenueOptions::eWithdraw:
    {
        system("cls");
        ShowWithdrawScreen();
        GoBackToTransactionsMenue();
        break;
    }
    case enTransactionsMenueOptions::eTotalBalance:
    {
        system("cls");
        ShowTotalBalancesScreen();
        GoBackToTransactionsMenue();
        break;
    }
    case enTransactionsMenueOptions::eMainMenue:
    {
        system("cls");
        ShowMainMenueScreen();
        break;

    }
    default:
    {
        cout << "We are sorry an error occoured." << endl;
    }
    }
}

void ShowTransactionsMenueScreen()
{
    cout << "==================================================" << endl;
    cout << "\tTransaction Meneu Screen :-)" << endl;
    cout << "==================================================" << endl;
    cout << "[1] Deposit." << endl;
    cout << "[2] Withdraw." << endl;
    cout << "[3] Total Balances." << endl;
    cout << "[4] Main Menue." << endl;
    cout << "==================================================" << endl;
    PerformTransactionsMenueChoose((enTransactionsMenueOptions)ReadTransactionsMenueChoose());
}

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

    cout << "Choose what do you want to do [1 To 8]: ";
    cin >> UserChoose;

    while (UserChoose < 1 || UserChoose > 8)
    {
        cout << "\nInvalid choose, please try again: ";
        cin >> UserChoose;
    }

    return UserChoose;
}

void ShowEndScreen()
{
    cout << "______________________________________" << endl;
    cout << "\n\tProgram Ended :-)" << endl;
    cout << "______________________________________" << endl;
}

void PerformMainMenueChoose(enMainMenueOptions MainMenueOptions)
{
    switch (MainMenueOptions)
    {
    case enMainMenueOptions::eShowClientList:
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
    case enMainMenueOptions::eTransactions:
    {
        system("cls");
        ShowTransactionsMenueScreen();
        GoBackToMainMenue();
        break;
    }
    case enMainMenueOptions::eManageUsers:
    {
        system("cls");
        ShowManageUserScreen();
        break;
    }
    case enMainMenueOptions::eLogout:
    {
        system("cls");
        ShowLoginScreen();
        break;
    }
    default:
    {
        cout << "We are sorry an error occoured." << endl;
    }
    }
}


struct stUser
{
    string Username;
    string Password;
    short Permissions;
    bool MarkForDelete = false;
};

string ReadUsername()
{
    string Username = "";

    cout << "Please enter the username: ";
    getline(cin >> ws, Username);

    return Username;
}

string ReadPassword()
{
    string Password = "";

    cout << "Please enter password: ";
    cin >> Password;

    return Password;
}

stUser ConvertLineToRecordFromUsersFile(string Line, string Seperator = "#//#")
{
    stUser User;
    vector <string> vUserData = SplitString(Line, Seperator);

    User.Username = vUserData[0];
    User.Password = vUserData[1];
    User.Permissions = stoi(vUserData[2]);

    return User;
}

vector <stUser> LoadUsersDataFromFile(string FileName)
{
    vector <stUser> vUsers;
    fstream MyFile;

    MyFile.open(FileName, ios::in);

    if (MyFile.is_open())
    {
        string Line = "";

        while (getline(MyFile, Line))
        {
            stUser User = ConvertLineToRecordFromUsersFile(Line);
            vUsers.push_back(User);
        }

        MyFile.close();
    }

    return vUsers;
}

bool IsUsernameExisted(string Username)
{
    vector <stUser> Users = LoadUsersDataFromFile(UsersFileName);

    for (stUser& U : Users)
    {
        if (U.Username == Username)
            return true;
    }

    return false;
}

bool IsCorrectPassword(string Password, string Username)
{
    vector <stUser> vUsers = LoadUsersDataFromFile(UsersFileName);

    for (stUser& User : vUsers)
    {
        if (User.Username == Username)
        {
            if (User.Password == Password)
                return true;

        }

    }

    return false;
}

short ReadManageUserChoose()
{
    short UserChoose = 0;

    cout << "Choose what do you want to do [1 To 6]: ";
    cin >> UserChoose;

    while (UserChoose < 1 || UserChoose > 6)
    {
        cout << "\nInvalid choose, please try again: ";
        cin >> UserChoose;
    }

    return UserChoose;
}

void GoToBackToManageUsersScreen()
{
    cout << "\n\nPress any key to go to main menue.....";
    system("pause>0");
    system("cls");
    ShowManageUserScreen();
}

void PrintUserRecord(stUser User)
{
    cout << "|" << setw(20) << left << User.Username;
    cout << "|" << setw(10) << left << User.Password;
    cout << "|" << setw(5) << left << User.Permissions;
}

void ShowUsersList()
{
    vector <stUser> vUser = LoadUsersDataFromFile(UsersFileName);

    cout << "\n\t\t\t\tUsers List (" << vUser.size() << ") User(s)." << endl;
    cout << "_____________________________________________________________________________________" << endl;
    cout << "\n|" << setw(20) << left << "Username";
    cout << "|" << setw(10) << left << "Password";
    cout << "|" << setw(5) << left << "Permissions";
    cout << "\n_____________________________________________________________________________________\n" << endl;

    for (stUser& User : vUser)
    {
        PrintUserRecord(User);
        cout << endl;
    }

    cout << "_____________________________________________________________________________________" << endl;
}

stUser ReadNewUser()
{
    stUser User;
    string Username = "";
    short Counter = 0;

    do
    {
        if (Counter > 0)
            cout << "User Name [" << Username << "] is not avaliable, please try again.\n" << endl;

        cout << "Enter User Name: ";
        getline(cin >> ws, Username);

        Counter++;

    } while (IsUsernameExisted(Username));

    User.Username = Username;

    cout << "Enter Password: ";
    getline(cin >> ws, User.Password);

    char FullAccess = 'N';
    cout << "\nDo you want to give \'" << Username << "\' Full access? [Y|N]" << endl;
    cin >> FullAccess;

    if (toupper(FullAccess) == 'Y')
    {
        User.Permissions = -1;
    }
    else
    {
        char Access = 'N';
        cout << "\nChoose what do you want to give " << Username << " access on:\n";

        cout << "Show client list? [Y|N]: ";
        cin >> Access;
        if (toupper(Access) == 'Y')
            User.Permissions = gShowClientList;

        cout << "Add new client? [Y|N]: ";
        cin >> Access;
        if (toupper(Access) == 'Y')
            User.Permissions |= gAddNewClient;

        cout << "Delete client? [Y|N]: ";
        cin >> Access;
        if (toupper(Access) == 'Y')
            User.Permissions |= gDeleteClient;

        cout << "Update client? [Y|N]: ";
        cin >> Access;
        if (toupper(Access) == 'Y')
            User.Permissions |= gUpdateClient;

        cout << "Find client? [Y|N]: ";
        cin >> Access;
        if (toupper(Access) == 'Y')
            User.Permissions |= gFindClient;

        cout << "Transactions? [Y|N]: ";
        cin >> Access;
        if (toupper(Access) == 'Y')
            User.Permissions |= gTransactions;

        cout << "Manage users? [Y|N]: ";
        cin >> Access;
        if (toupper(Access) == 'Y')
            User.Permissions |= gManageUsers;
    }

    return User;
}

string ConvertUserRecordToLine(stUser& User, string Seperator = "#//#")
{
    string UserRecord = "";

    UserRecord = User.Username + Seperator;
    UserRecord += User.Password + Seperator;
    UserRecord += to_string(User.Permissions);

    return UserRecord;
}

void AddNewUser()
{
    stUser User = ReadNewUser();
    SaveLineToFile(UsersFileName, ConvertUserRecordToLine(User));
}

void AddNewUsers()
{
    char AddMore = 'y';

    do
    {
        cout << "\nAdd New User:\n" << endl;
        AddNewUser();

        cout << "\nUser Added Successfully, Do you want to add more users? [Y/N]" << endl;
        cin >> AddMore;

    } while (toupper(AddMore) == 'Y');
}

void ShowAddNewUsersScreen()
{
    cout << "______________________________________" << endl;
    cout << "\n\tAdd User Screen" << endl;
    cout << "______________________________________" << endl;

    AddNewUsers();
}

void PrintUserCard(stUser User)
{
    cout << "\nThe following is the extracted User record:" << endl;
    cout << "\nUsername             : " << User.Username << endl;
    cout << "Password             : " << User.Password << endl;
    cout << "Permission           : " << User.Permissions << endl;
}

bool MarkUserForDeleteByUsername(string Username, vector <stUser>& vUser)
{
    for (stUser& User : vUser)
    {
        if (User.Username == Username)
        {
            User.MarkForDelete = true;
            return true;
        }
    }

    return false;
}

bool SaveUserDataToFile(string FileName, vector <stUser>& vUser)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out);

    if (MyFile.is_open())
    {
        for (stUser& User : vUser)
        {
            if (User.MarkForDelete == false)
            {
                string Line = ConvertUserRecordToLine(User);
                MyFile << Line << endl;
            }
        }

        MyFile.close();
        return true;
    }

    return false;
}

bool DeleteUserByUsername(string Username, vector <stUser>& vUsers)
{
    stUser User;
    char Sure = 'n';
    short Counter = 0;

    while (!IsUsernameExisted(Username))
    {
        cout << "Username [" << Username << "] is not existed." << endl;
        cout << "\nplease try again: ";
        cin >> Username;
    }

    for (stUser& U : vUsers)
    {
        if (U.Username == Username)
        {
            PrintUserCard(U);
        }
    }
    
    cout << "\nAre you sure you want to delete this client? [Y|N]" << endl;
    cin >> Sure;

    if (toupper(Sure) == 'Y')
    {
        MarkUserForDeleteByUsername(Username, vUsers);
        SaveUserDataToFile(UsersFileName, vUsers);

        cout << "\nClient deleted Successfully." << endl;

        return true;
    }
    else
    {
        return false;
    }
}

void ShowDeleteUserScreen()
{
    cout << "______________________________________" << endl;
    cout << "\n\tDelete User Screen" << endl;
    cout << "______________________________________" << endl;

    vector <stUser> vUser = LoadUsersDataFromFile(UsersFileName);
    string Username = ReadUsername();

    DeleteUserByUsername(Username, vUser);
}

stUser ChangeUserRecord(string Username)
{
    stUser User;

    User.Username = Username;

    cout << "\nEnter Password: ";
    getline(cin >> ws, User.Password);

    char FullAccess = 'N';
    cout << "Do you want to give \'" << Username << "\' Full access? [Y|N]" << endl;
    cin >> FullAccess;

    if (toupper(FullAccess) == 'Y')
    {
        User.Permissions = -1;
    }
    else
    {
        char Access = 'N';
        cout << "\nChoose what do you want to give " << Username << " access on:\n";

        cout << "Show client list? [Y|N]: ";
        cin >> Access;
        if (Access == 'Y')
            User.Permissions = gShowClientList;

        cout << "Add new client? [Y|N]: ";
        cin >> Access;
        if (Access == 'Y')
            User.Permissions |= gAddNewClient;

        cout << "Delete client? [Y|N]: ";
        cin >> Access;
        if (Access == 'Y')
            User.Permissions |= gDeleteClient;

        cout << "Update client? [Y|N]: ";
        cin >> Access;
        if (Access == 'Y')
            User.Permissions |= gUpdateClient;

        cout << "Find client? [Y|N]: ";
        cin >> Access;
        if (Access == 'Y')
            User.Permissions |= gFindClient;

        cout << "Transactions? [Y|N]: ";
        cin >> Access;
        if (Access == 'Y')
            User.Permissions |= gTransactions;

        cout << "Manage users? [Y|N]: ";
        cin >> Access;
        if (Access == 'Y')
            User.Permissions |= gManageUsers;
    }

    return User;
}

bool UpdateUserByUsername(string Username, vector <stUser>& vUsers)
{
    stUser User;
    char Sure = 'n';
    short Counter = 0;

    while (!IsUsernameExisted(Username))
    {
        cout << "Username \'" << Username << "\' is not existed." << endl;
        cout << "\nplease try again: ";
        cin >> Username;
    }

    for (stUser& U : vUsers)
    {
        if (U.Username == Username)
        {
            PrintUserCard(User);
        }
    }

    cout << "\nAre you sure you want to update this User? [Y|N]" << endl;
    cin >> Sure;

    if (toupper(Sure) == 'Y')
    {
        for (stUser& U : vUsers)
        {
            if (U.Username == Username)
            {
                U = ChangeUserRecord(Username);
                break;
            }
        }

        SaveUserDataToFile(UsersFileName, vUsers);

        cout << "\nChanges applied successfully." << endl;
        return true;
    }
    else
    {
        return false;
    }
}

void ShowUpdateUserScreen()
{
    cout << "______________________________________" << endl;
    cout << "\n\tUpdate User Screen" << endl;
    cout << "______________________________________" << endl;

    vector <stUser> vUser = LoadUsersDataFromFile(UsersFileName);
    string Username = ReadUsername();

    UpdateUserByUsername(Username, vUser);
}

void ShowFindUserScreen()
{
    cout << "______________________________________" << endl;
    cout << "\n\tFind User Screen" << endl;
    cout << "______________________________________" << endl;

    vector <stUser> vUsers = LoadUsersDataFromFile(UsersFileName);
    stUser User;
    string Username = ReadUsername();

    while (!IsUsernameExisted(Username))
    {
        cout << "Username \'" << Username << "\' is not existed." << endl;
        cout << "\nplease try again: ";
        cin >> Username;
    }

    for (stUser& U : vUsers)
    {
        if (U.Username == Username)
        {
            PrintUserCard(U);
        }
    }
}

enum enManageUserOptions
{
    eListUsers = 1,
    eAddNewUser = 2,
    eDeleteUser = 3,
    eUpdateUser = 4,
    eFindUser = 5,
    eMainMenueScreen = 6
};

bool IsUserHavePermission(string Username, short PermissionFlag)
{
    vector <stUser> vUsers = LoadUsersDataFromFile(UsersFileName);

    for (stUser& User : vUsers)
    {
        if (User.Username == Username)
        {
            if (User.Permissions == -1)
            {
                return true;
            }
            else if (User.Permissions & PermissionFlag)
            {
                return true;
            }
            else
                return false;
        }
    }

    return false;
}

void PerformManageUsersScreen(enManageUserOptions ManageUserOptions)
{
    switch (ManageUserOptions)
    {
    case enManageUserOptions::eListUsers:
    {
        system("cls");
        ShowUsersList();
        GoToBackToManageUsersScreen();
        break;
    }
    case enManageUserOptions::eAddNewUser:
    {
        system("cls");
        ShowAddNewUsersScreen();
        GoToBackToManageUsersScreen();
        break;
    }
    case enManageUserOptions::eDeleteUser:
    {
        system("cls");
        ShowDeleteUserScreen();
        GoToBackToManageUsersScreen();
        break;
    }
    case enManageUserOptions::eUpdateUser:
    {
        system("cls");
        ShowUpdateUserScreen();
        GoToBackToManageUsersScreen();
        break;
    }
    case enManageUserOptions::eFindUser:
    {
        system("cls");
        ShowFindUserScreen();
        GoToBackToManageUsersScreen();
        break;
    }
    case enManageUserOptions::eMainMenueScreen:
    {
        system("cls");
        ShowMainMenueScreen();
        break;
    }
    default:
    {
        cout << "We are sorry an error occoured." << endl;
    }
    }
}

void ShowRefuseScreen()
{
    cout << "______________________________________" << endl;
    cout << "\n\tAccess Refused :-(" << endl;
    cout << "______________________________________" << endl;
    cout << "\nYou are not allowed to access this page, ";
    cout << "Please contact your admin." << endl;
}

void ShowManageUserScreen()
{
    cout << "______________________________________" << endl;
    cout << "\n\tManage User Screen :-)" << endl;
    cout << "______________________________________" << endl;
    cout << "[1] List Users." << endl;
    cout << "[2] Add New User." << endl;
    cout << "[3] Delete User." << endl;
    cout << "[4] Update User." << endl;
    cout << "[5] Find User." << endl;
    cout << "[6] Main Menue Screen." << endl;
    cout << "==================================================" << endl;
    PerformManageUsersScreen((enManageUserOptions)ReadManageUserChoose());
}

short MapMainMenueChoiceToPermissionFlag(short menuChoice)
{
    switch (menuChoice)
    {
    case 1:
    {
        return gShowClientList;
    }
    case 2:
    {
        return gAddNewClient;
    }
    case 3:
    {
        return gDeleteClient;
    }
    case 4:
    {
        return gUpdateClient;
    }
    case 5:
    {
        return gFindClient;
    }
    case 6:
    {
        return gTransactions;
    }
    case 7:
    {
        return gManageUsers;
    }
    default:
    {
        return 0;
    }
    }
}

void ShowMainMenueScreen()
{
    system("cls");
    cout << "======================================================" << endl;
    cout << "\t\tMain Menue Screen" << endl;
    cout << "======================================================" << endl;
    cout << "[1] Show Client List." << endl;
    cout << "[2] Add New Client." << endl;
    cout << "[3] Delete Client." << endl;
    cout << "[4] Update Client Info." << endl;
    cout << "[5] Find Client." << endl;
    cout << "[6] Transactions." << endl;
    cout << "[7] Manage Users Screen." << endl;
    cout << "[8] Logout." << endl;
    cout << "======================================================" << endl;
    short UserChoose = ReadMainMenueChoose();
    short PermissionFlag = MapMainMenueChoiceToPermissionFlag(UserChoose);

    if (UserChoose == 8) // Loagout
    {
        PerformMainMenueChoose((enMainMenueOptions)UserChoose);
    }
    else if (IsUserHavePermission(GlobalUsername, PermissionFlag))
    {
        PerformMainMenueChoose((enMainMenueOptions)UserChoose);
    }
    else
    {
        system("cls");
        ShowRefuseScreen();
        GoBackToMainMenue();
    }
}

void ShowLoginScreen()
{
    system("cls");
    cout << "======================================================" << endl;
    cout << "\t\tLogin Screen" << endl;
    cout << "======================================================" << endl;
    
    GlobalUsername = ReadUsername();
    string Password = ReadPassword();

    while (!IsUsernameExisted(GlobalUsername) ||
        !IsCorrectPassword(Password, GlobalUsername))
    {
        cout << "\nUsername or Password is NOT correct, Please try again." << endl;
        GlobalUsername = ReadUsername();
        Password = ReadPassword();
    }
    
    ShowMainMenueScreen();
}

int main()
{
    ShowLoginScreen();
    system("pause>0");

    return 0;
}
