#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

const string ClientsFileName = "Clients.txt";

// Structure du client
struct sClient
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance = 0;
    bool MarkForDelete = false;
};

enum enMainMenueOptions
{
    eQuickWithdraw = 1, eNormalWithdraw = 2, eDeposits = 3, eCheckBalance = 4, eLogout = 5
};

sClient CurrentClient;

// Déclarations de fonctions
void ShowMainMenue();
void GoBackToMainMenue();
void ShowQuickWithdrawScreen();
void ShowNormalWithdrawScreen();
void Login();


// Fonction pour lire un numero de compte depuis l'utilisateur
string ReadClientAccountNumber()
{
    string AccountNumber = "";

    cout << "\nSaisir un nombre de compte? ";
    cin >> AccountNumber;
    return AccountNumber;
}

// Fonction pour découper une chaîne en utilisant un délimiteur
vector<string> DecouperString(string S1, string Delim)
{
    vector<string> vString;
    short pos = 0;
    string sWord;

    while ((pos = S1.find(Delim)) != string::npos)
    {
        sWord = S1.substr(0, pos);
        if (sWord != "")
        {
            vString.push_back(sWord);
        }
        S1.erase(0, pos + Delim.length());
    }
    if (S1 != "")
    {
        vString.push_back(S1);
    }
    return vString;
}

// Convertir une ligne du fichier en structure client
sClient ConvertLinetoRecord(string Line, string Seperator = "#//#")
{
    sClient Client;
    vector<string> vClientData = DecouperString(Line, Seperator);

    if (vClientData.size() >= 5)
    {
        Client.AccountNumber = vClientData[0];
        Client.PinCode = vClientData[1];
        Client.Name = vClientData[2];
        Client.Phone = vClientData[3];
        Client.AccountBalance = stod(vClientData[4]);
    }
    return Client;
}

// Convertir un client en ligne pour le fichier
string ConvertRecordClientToLine(sClient Client, string Seperator = "#//#")
{
    string stClientRecord = "";
    stClientRecord += Client.AccountNumber + Seperator;
    stClientRecord += Client.PinCode + Seperator;
    stClientRecord += Client.Name + Seperator;
    stClientRecord += Client.Phone + Seperator;
    stClientRecord += to_string(Client.AccountBalance);
    return stClientRecord;
}



// Fonctions de navigation
void GoBackToMainMenue()
{
    cout << "\n\nAppuyer sur une touche pour retourner au Menu Principal...";
    system("pause>0");
    ShowMainMenue();
}

vector<sClient> LoadCleintsDataFromFile(string FileName)
{
    vector<sClient> vClients;
    ifstream MyFile(FileName);

    if (MyFile.is_open())
    {
        string Line;
        while (getline(MyFile, Line))
        {
            sClient Client = ConvertLinetoRecord(Line);
            vClients.push_back(Client);
        }
        MyFile.close();
    }
    return vClients;
}


void SaveCleintsDataToFile(string FileName, vector<sClient> vClients)
{
    ofstream MyFile(FileName);
    if (MyFile.is_open())
    {
        for (sClient C : vClients)
        {
            if (C.MarkForDelete == false)
            {
                MyFile << ConvertRecordClientToLine(C) << endl;
            }
        }
        MyFile.close();
    }
}

void AddDataLineToFile(string FileName, string stDataLine)
{
    ofstream MyFile(FileName, ios::app);
    if (MyFile.is_open())
    {
        MyFile << stDataLine << endl;
        MyFile.close();
    }
}

bool DepositBalanceToClientByAccountNumber(string AccountNumber, double Amount, vector<sClient>& vClients)
{

    char Reponse = 'n';

    cout << "\n\nTu es sure pour faire cette operation? o/n ? ";
    cin >> Reponse;

    if (Reponse == 'o' || Reponse == 'O')
    {
        for (sClient& C : vClients)
        {
            if (C.AccountNumber == AccountNumber)
            {
                C.AccountBalance += Amount;
                SaveCleintsDataToFile(ClientsFileName, vClients);
                cout << "\n\nOperation effectuee avec succes. Le nouveau solde est: " << C.AccountBalance;
                return true;
            }
        }
    }
    return false;
}

void ShowSoldeScreen()
{

    cout << "\n-----------------------------------\n";
    cout << "\tLe solde est: " << CurrentClient.AccountBalance << endl;
    cout << "\n-----------------------------------\n";

}
void PerfromDepositOption()
{

    double Montant = 0;
    cout << "Saisir le montant a deposer: ";
    cin >> Montant;

    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    DepositBalanceToClientByAccountNumber(CurrentClient.AccountNumber, Montant, vClients);
    CurrentClient.AccountBalance -= Montant;

}

void ShowDeposerScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tEcran de Depot";
    cout << "\n-----------------------------------\n";

    PerfromDepositOption();

}
short ReadMainQuickWithdrawOption()
{
    short Choice = 0;
    do {
        cout << "Choisir ce que vous voulez [1 a 8]? ";
        cin >> Choice;
    } while (Choice < 1 || Choice > 8);

    return Choice;
}

short getQuickWithDrawAmount(short Choice)
{
    switch (Choice)
    {
    case 1:
        return 20;
    case 2:
        return 50;
    case 3:
        return 100;
    case 4:
        return 200;
    case 5:
        return 400;
    case 6:
        return 600;
    case 7:
        return 800;
    case 8:
        return 1000;
    default:
        return 0;
    }

}
short PerfromQuickWithdrawOption(short Choice)
{
    if (Choice == 9) //Sortir
        return 0;

    short withDrawBalance = getQuickWithDrawAmount(Choice);
    while (withDrawBalance > CurrentClient.AccountBalance)
    {
        cout << "Solde insuffisant" << endl;
        system("pause>0");
        ShowQuickWithdrawScreen();
        return 0;
    }
    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    DepositBalanceToClientByAccountNumber(CurrentClient.AccountNumber, withDrawBalance * -1, vClients);
    CurrentClient.AccountBalance -= withDrawBalance;

}
void ShowQuickWithdrawScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tEcran de Retrait Rapide";
    cout << "\n-----------------------------------\n";

    cout << "\n";
    cout << "\n-----------------------------------\n";
    cout << "\t[1]20\t\t[2]50";
    cout << "\n";
    cout << "\t[3]100\t\t[4]200";
    cout << "\n";
    cout << "\t[5]400\t\t[6]600";
    cout << "\n";
    cout << "\t[7]800\t\t[8]1000";
    cout << "\n-----------------------------------\n";
    cout << "\n";

    PerfromQuickWithdrawOption(ReadMainQuickWithdrawOption());


}
int ReadWithDrawAmont()
{
    int Amount;
    cout << "\nEntrez un montant de multiple de 50 ? ";

    cin >> Amount;

    while (Amount % 5 != 0)
    {
        cout << "\nEntrez un montant de multiple de 50 ? ";
        cin >> Amount;
    }
    return Amount;
}
void PerfromNormalWithdrawOption()
{
    int WithDrawBalance = ReadWithDrawAmont();

    if (WithDrawBalance > CurrentClient.AccountBalance)
    {
        cout << "\Solde insufisant, s'il vous plaits saisire un autre montant.\n";
        cout << "Clique un boutton pour continue...";
        system("pause>0");
        ShowNormalWithdrawScreen();
        return;
    }


    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    DepositBalanceToClientByAccountNumber(CurrentClient.AccountNumber, WithDrawBalance * -1, vClients);
    CurrentClient.AccountBalance -= WithDrawBalance;


}
void ShowNormalWithdrawScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tEcran de Retrait";
    cout << "\n-----------------------------------\n";
    PerfromNormalWithdrawOption();
}

short ReadMainMenueOption()
{

    short Choice = 0;

    do {

        cout << "Choisir ce que vous voulez [1 a 5]? ";
        cin >> Choice;

    } while (Choice < 1 || Choice > 5);

    return Choice;
}


void PerfromMainMenueOption(enMainMenueOptions MainMenueOption)
{
    switch (MainMenueOption)
    {
    case enMainMenueOptions::eQuickWithdraw:
        system("cls");
        ShowQuickWithdrawScreen();
        GoBackToMainMenue();
        break;
    case enMainMenueOptions::eNormalWithdraw:
        system("cls");
        ShowNormalWithdrawScreen();
        GoBackToMainMenue();
        break;
    case enMainMenueOptions::eDeposits:
        system("cls");
        ShowDeposerScreen();
        GoBackToMainMenue();
        break;
    case enMainMenueOptions::eCheckBalance:
        system("cls");
        ShowSoldeScreen();
        GoBackToMainMenue();
        break;
    case enMainMenueOptions::eLogout:
        system("cls");
        Login();
        exit(0);
        break;
    }
}

void ShowMainMenue()
{
    system("cls");
    cout << "===========================================\n";
    cout << "\t\tATM Menu Principal\n";
    cout << "===========================================\n";
    cout << "\t[1] Deposer Rapide\n";
    cout << "\t[2] Deposer Normale\n";
    cout << "\t[3] Retirer\n";
    cout << "\t[4] Voir Solde\n";
    cout << "\t[5] Logout\n";
    cout << "===========================================\n";

    PerfromMainMenueOption((enMainMenueOptions)ReadMainMenueOption());
}

bool FindClientByAccountNumberAndPassword(string AccountNumber, string Password, sClient& Client)
{

    vector <sClient> vClient = LoadCleintsDataFromFile(ClientsFileName);

    for (sClient C : vClient)
    {

        if (C.AccountNumber == AccountNumber && C.PinCode == Password)
        {
            Client = C;
            return true;
        }

    }
    return false;
}

bool  LoadClientInfo(string Username, string Password)
{

    if (FindClientByAccountNumberAndPassword(Username, Password, CurrentClient))
        return true;
    else
        return false;

}


void Login()
{
    bool LoginFaild = false;

    string AccountNumber, Password;
    do
    {
        system("cls");

        cout << "\n---------------------------------\n";
        cout << "\tLogin Screen";
        cout << "\n---------------------------------\n";

        if (LoginFaild)
        {
            cout << "Invlaide Nombre de Compte/Password!\n";
        }

        cout << "Enter Nombre de compte? ";
        cin >> AccountNumber;

        cout << "Enter Password? ";
        cin >> Password;

        LoginFaild = !LoadClientInfo(AccountNumber, Password);

    } while (LoginFaild);

    ShowMainMenue();

}
int main()
{
    Login();
    system("pause>0");
    return 0;
}