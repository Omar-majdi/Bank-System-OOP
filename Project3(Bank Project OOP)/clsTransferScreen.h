#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsBankClient.h"

class clsTransferScreen : protected clsScreen {
private:
    static void _PrintClient(clsBankClient& Client) {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFull Name   : " << Client.FullName();
        cout << "\nAcc. Number : " << Client.AccountNumber();
        cout << "\nBalance     : " << Client.AccountBalance;
        cout << "\n___________________\n";
    }

	static string _ReadAccountNumber(bool From = true) {
		string AccountNumber;
		if (From)
			cout << "\nPlease Enter Account Number to Transfer From: ";
		else 
			cout << "\nPlease Enter Account Number to Transfer To: ";

		AccountNumber = clsInputValidate::ReadString();
		while (!clsBankClient::IsClientExist(AccountNumber)) {
			cout << "\nAccount number is not found, choose another one: ";
			AccountNumber = clsInputValidate::ReadString();
		}
		return AccountNumber;
	}

	static float ReadAmount(clsBankClient SourceClient) {
		float Amount;
		cout << "\nEnter Transfer Amount: ";
		Amount = clsInputValidate::ReadFloatNumber();

		while (Amount > SourceClient.AccountBalance) {
			cout << "\nAmount Exeeds the available Balance, Enter another amount: ";
			Amount = clsInputValidate::ReadFloatNumber();
		}
		return Amount;
	}

public:
	static void ShowTransferScreen() {

		string Title = "\tTransfer Screen";
		_DrawScreenHeader(Title);

		clsBankClient SourceClient = clsBankClient::Find(_ReadAccountNumber());
		_PrintClient(SourceClient);

		clsBankClient DestinationClient = clsBankClient::Find(_ReadAccountNumber(false));
		while (SourceClient.AccountNumber() == DestinationClient.AccountNumber()) {
			cout << "The Destinatin Client Shouldn't be the same as the Source client!\n";
			DestinationClient = clsBankClient::Find(_ReadAccountNumber());
		}
		_PrintClient(DestinationClient);

		float Amount = ReadAmount(SourceClient);

		cout << "\nAre you sure you want to perform this operation? y/n";
		char Answer = 'n';
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y') {
			if (SourceClient.Transfer(Amount, DestinationClient, CurrentUser.UserName))
				cout << "\nTransfer done successfully\n";
			else
				cout << "\nTransfer Faild \n";
		}
		_PrintClient(SourceClient);
		_PrintClient(DestinationClient);
	}


};

