#include <iostream>
#include <string>
#include <vector>
#include <fstream> 

using namespace std;
void Login();
void ShowMenueScreen();
string ClientFile = "Clients.txt";
void ShowScreenQuickWhithDraw();
struct sClient
{
	string AccountNumber = "";
	string PinCode = "";
	string Name = "";
	string Phone = "";
	double AccountBalance = 0;
	bool MarketForDelete = false;
};

enum eATMmenue
{
	QuickWithDraw = 1, NormalWithDraw = 2,
	Deposite = 3, CheackBalance = 4,
	Logout = 5
};

enum eWithDraw
{
	Twenty = 1, Fifty = 2,
	OneHundred = 3, TwoHundred = 4,
	FourHundred = 5, SixHundred = 6,
	EightHundred = 7, OneThousand = 8,
	Exit = 9
};

sClient stClientATM;

vector <string> SplingData(string Line , string Delim)
{
	string Sword;
	short Pos;
	vector <string> LoadData;
	while ((Pos = Line.find(Delim)) != std::string::npos)
	{
		Sword = Line.substr(0, Pos);
		if (Sword != "")
		{
			LoadData.push_back(Sword);
		}
		Line.erase(0, Pos + Delim.length());
	}
	if (Line != "")
	{
		LoadData.push_back(Line);
	}
	return LoadData;
}

sClient DataFileTosClient (string Line , string Delim = "#//#")
{
	vector <string>DataToSpling = SplingData(Line , Delim);
	sClient Client;

	Client.AccountNumber = DataToSpling[0];
	Client.PinCode = DataToSpling[1];
	Client.Name = DataToSpling[2];
	Client.Phone = DataToSpling[3];
	Client.AccountBalance = stoi(DataToSpling[4]);

	return Client;
}

vector <sClient> LoadDataFromFile (string FileName)
{
	fstream Myfile;
	sClient Client;
	Myfile.open(FileName, ios::in);

	vector <sClient> LoadData;
	if (Myfile.is_open())
	{
		string Line;
		while (getline(Myfile, Line))
		{
			Client = DataFileTosClient(Line);
			LoadData.push_back(Client);
		}
		Myfile.close();
	}
	return LoadData;
}

string ReadUserNameAndPassword(string Massage)
{
	string PassAnUser;
	cout << Massage;
	getline(cin >> ws, PassAnUser);
	return PassAnUser;
}

short GetNumber(string Massage)
{
	short Number;
	cout << Massage;
	cin >> Number;
	return Number;
}

bool IsRightUserAndPassword (string UserName , string Password , sClient& DataUser)
{
	vector <sClient>Data = LoadDataFromFile(ClientFile);
	for (sClient& Temp : Data)
	{
		if (Temp.AccountNumber == UserName && Temp.PinCode == Password)
		{
			DataUser = Temp;
			return true;
		}
	}

	return false;
}

void ShowCheackBalance ()
{
	cout << "=====================================\n";
	cout << "\tCheack Balance Screen\n";
	cout << "=====================================\n";
	cout << "Your Balance is " << stClientATM.AccountBalance << endl;
}

void GoBacktoMainMenue()
{
	cout << "\nPress any Key to Go Back to Main Menue...";
	system("pause>0");
	ShowMenueScreen();
}

bool TrueOrFalse (string Massage)
{
	char YesOrNo = 'n';
	cout << Massage;
	cin >> YesOrNo;

	return YesOrNo == 'y';
}

string DataToLoine (sClient Data , string Sepretor = "#//#")
{
	string Line;
	Line += Data.AccountNumber + Sepretor;
	Line += Data.PinCode + Sepretor;
	Line += Data.Name + Sepretor;
	Line += Data.Phone + Sepretor;
	Line += to_string(Data.AccountBalance);
	return Line;
}

void SaveDataToFile (string FileName , sClient ClientToUpdatingBalance)
{
	vector <sClient>LoadData = LoadDataFromFile(FileName);
	fstream Myfile;
	Myfile.open(FileName, ios::out);
	for (sClient& s : LoadData)
	{
		if (s.AccountNumber == ClientToUpdatingBalance.AccountNumber)
		{
			Myfile << DataToLoine(ClientToUpdatingBalance) << endl;
		}
		else
		{
			Myfile << DataToLoine(s) << endl;
		}
	}
}

void QuickWhithDraw (eWithDraw WithDraw)
{
	int Balance = 0;
	if (WithDraw == eWithDraw::Exit)
		GoBacktoMainMenue();
	 if (WithDraw == eWithDraw::Twenty)
		Balance = 20;
	 if (WithDraw == eWithDraw::Fifty)
		Balance = 50;
	 if (WithDraw == eWithDraw::OneHundred)
		Balance = 100;
	 if (WithDraw == eWithDraw::TwoHundred)
		Balance = 200;
	 if (WithDraw == eWithDraw::FourHundred)
		Balance = 400;
	 if (WithDraw == eWithDraw::SixHundred)
		Balance = 600;
	 if (WithDraw == eWithDraw::EightHundred)
		Balance = 800;
	 if (WithDraw == eWithDraw::OneThousand)
		Balance = 1000;

	 Balance = (stClientATM.AccountBalance - Balance);

	if (Balance > 0)
	{
		stClientATM.AccountBalance = Balance;
		if (TrueOrFalse("\nAre You Sure You Want Perform this transaction? y/n? "))
		{
			SaveDataToFile(ClientFile , stClientATM);
			cout << "\nDone Successfully. new balance is: " << stClientATM.AccountBalance;
			GoBacktoMainMenue();
		}
		else
		{
			GoBacktoMainMenue();
		}
	}
	else
	{
		cout << "\nThe Amount exceeds your balance, make another choice.\n";
		cout << "Press AnyKey To Continue...";
		system("pause>0");
		ShowScreenQuickWhithDraw();
	}
}

void ShowScreenQuickWhithDraw ()
{
	system("cls");
	cout << "=======================================\n";
	cout << "\t     Quick WithDraw\n";
	cout << "=======================================\n";
	cout << "\t[1] 20   \t  [2] 50\n";
	cout << "\t[3] 100 \t  [4] 200\n";
	cout << "\t[5] 400 \t  [6] 600\n";
	cout << "\t[7] 800 \t  [8] 1000\n";
	cout << "\t[9] Exit \n";
	cout << "=======================================\n";
	cout << "Your Balance is " << stClientATM.AccountBalance << endl;
	
	QuickWhithDraw((eWithDraw)GetNumber("Choose What to WithDraw From[1] to [8]? "));
}

void ScreenNormalWhithDraw ()
{
	system("cls");
	cout << "======================================\n";
	cout << "\tNormal WithDraw Screen\n";
	cout << "======================================\n";
}

void SaveDataDraw (sClient Client)
{
	if (TrueOrFalse("\n\nAre You Sure You Want Perform this transaction? y/n ? "))
	{
		SaveDataToFile(ClientFile, stClientATM);
		cout << "Done Successfully. New Balance is: " << stClientATM.AccountBalance << endl;
		GoBacktoMainMenue();
	}
	else
	{
		GoBacktoMainMenue();
	}

}

void ShowScreenNormalWhithDraw ()
{
	ScreenNormalWhithDraw();
	int NumberToWithDraw = 0;
	do
	{
		cout << "\nEnter an amount multiple of 5's ? ";
		cin >> NumberToWithDraw;
		if (NumberToWithDraw > stClientATM.AccountBalance)
		{
			cout << "\nThe Amount exceeds your balance, Make another choice.\n";
			cout << "Press AnyKey to Continue...";
			system("pause>0");
			ShowScreenNormalWhithDraw();
		}

	} while (NumberToWithDraw % 5 != 0);

	stClientATM.AccountBalance = stClientATM.AccountBalance - NumberToWithDraw;
	 
	SaveDataDraw(stClientATM);
}

void ShowScreenDepostie ()
{
	system("cls");	
	int Deposite = 0;
	cout << "==================================\n";
	cout << "\t Deposit Screen\n";
	cout << "==================================\n";
	cout << "\nEnter a Positive Deposit Amount? ";
	cin >> Deposite;
	if (TrueOrFalse("\nAre You Sure you want perfrom this transaction? Y/N ? "))
	{
		stClientATM.AccountBalance += Deposite;
		SaveDataToFile(ClientFile , stClientATM);
		cout << "\nDone Successfully. New Balance is: " << stClientATM.AccountBalance << endl;
	}
	GoBacktoMainMenue();
}

void perfromClientOption (eATMmenue Client)
{
	switch (Client)
	{
	case QuickWithDraw:
	{
		ShowScreenQuickWhithDraw();
		break;
	}
	case NormalWithDraw:
		ShowScreenNormalWhithDraw();
		break;
	case Deposite:
		ShowScreenDepostie();
		break;

	case CheackBalance:
	{
		system("cls");
		ShowCheackBalance();
		GoBacktoMainMenue();
		break;
	}

	case Logout:
		{
			Login();
		}
		break;
	}
}

void ShowMenueScreen ()
{
	system("cls");
	cout << "=====================================\n";
	cout << "\t ATM Main Menue Screen\n";
	cout << "=====================================\n";
	cout << "\t[1] Quick WithDraw.\n";
	cout << "\t[2] Normal WithDraw.\n";
	cout << "\t[3] Deposit.\n";
	cout << "\t[4] Check Balance.\n";
	cout << "\t[5] Logout.\n";
	cout << "=====================================\n";

	perfromClientOption((eATMmenue)GetNumber("Choose What Do You Want To Do? [1 to 5]? "));
}

void ScreenLogIn ()
{
	system("cls");
	cout << "\n----------------------------------\n";
	cout << "\t   Login Screen\n";
	cout << "----------------------------------\n";
}

void Login ()
{
	ScreenLogIn();
	string UeserName;
	string Password;

	UeserName = ReadUserNameAndPassword("Enter Account Number? ");
	Password = ReadUserNameAndPassword("Enter Pin? ");

	while (!(IsRightUserAndPassword(UeserName, Password , stClientATM)))
	{
		ScreenLogIn();
		cout << "Invalid Account Number/PinCode!\n";
		UeserName = ReadUserNameAndPassword("Enter Account Number? ");
		Password = ReadUserNameAndPassword("Enter Pin? ");
	}
	ShowMenueScreen();
}


int main()
{
	Login();
}
