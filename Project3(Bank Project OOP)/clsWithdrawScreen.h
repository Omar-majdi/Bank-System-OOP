#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsBankClient.h"

class clsWithdrawScreen : protected clsScreen {
private:
	static void _PrintClient(clsBankClient& Client) {
		cout << "\nClient Card: ";
		cout << "\n___________________";
		cout << "\nFirstName    : " << Client.FirstName;
		cout << "\nLastName     : " << Client.LastName;
		cout << "\nFull Name    : " << Client.FullName();
		cout << "\nEmail        : " << Client.Email;
		cout << "\nPhone        : " << Client.Phone;
		cout << "\nAcc. Number  : " << Client.AccountNumber();
		cout << "\nPassword     : " << Client.PinCode;
		cout << "\nBalance      : " << Client.AccountBalance;
		cout << "\n___________________\n";
	}

	static string _ReadAccountNumber() {
		cout << "Please Enter Account Number: ";
		string AccountNumber; cin >> AccountNumber;
		return AccountNumber;
	}

public:
	static void ShowWithdrawScreen() {
		_DrawScreenHeader("\t  WithDraw Screen");

		string AccountNumber = _ReadAccountNumber();

		while (!clsBankClient::IsClientExist(AccountNumber)) {
			cout << "Client with [" << AccountNumber << "] does not exist.\n";
			AccountNumber = _ReadAccountNumber();
		}

		clsBankClient Client1 = clsBankClient::Find(AccountNumber);
		_PrintClient(Client1);

		double Amount = 0;
		cout << "\nPlease enter withdraw amount: ";
		Amount = clsInputValidate::ReadDblNumber();

		cout << "\nAre you sure you want to perform this transaction? y/n\n";
		char Answer = 'n';
		cin >> Answer;

		if (Answer == 'Y' || Answer == 'y') {
			if (Client1.Withdraw(Amount)) {
				cout << "\nAmount Withdrew Successfully.\n";
				cout << "\nNew Balance Is: " << Client1.AccountBalance;
			}
			else {
				cout << "\nCannot Withdraw, Insuffecient Balance!\n";
				cout << "\nAmount to withdraw is: " << Amount;
				cout << "\nYour Balance is: " << Client1.AccountBalance;
			}
		}
		else {
			cout << "\nOperation was cancelled.\n";
		}
	}
};

