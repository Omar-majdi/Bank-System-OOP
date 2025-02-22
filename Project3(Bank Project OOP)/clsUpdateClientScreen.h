#pragma once
#include <iostream>
#include <iomanip>
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsUtil.h"
#include "clsScreen.h"


class clsUpdateClientScreen : protected clsScreen {
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

	static void _ReadClientInfo(clsBankClient& Client) {
		cout << "\nEnter FirstName: ";
		Client.FirstName = clsInputValidate::ReadString();

		cout << "\nEnter LastName: ";
		Client.LastName = clsInputValidate::ReadString();

		cout << "\nEnter Email: ";
		Client.Email = clsInputValidate::ReadString();

		cout << "\nEnter Phone: ";
		Client.Phone = clsInputValidate::ReadString();

		cout << "\nEnter PinCode: ";
		Client.PinCode = clsInputValidate::ReadString();

		cout << "\nEnter Account Balance: ";
		Client.AccountBalance = clsInputValidate::ReadDblNumber();
	}


public:

	static void ShowUpdateClientScreen() {
		if (!CheckAccessRights(clsUser::enPermissions::pUpdateClients)) return;
		_DrawScreenHeader("\tUpdate Client Screen");

		string AccountNumber = "";

		cout << "\nPlease Enter Client Account Number: ";
		AccountNumber = clsInputValidate::ReadString();

		while (!clsBankClient::IsClientExist(AccountNumber)) {
			cout << "\nAccount number not found, choose another one: ";
			AccountNumber = clsInputValidate::ReadString();
		}

		clsBankClient Client1 = clsBankClient::Find(AccountNumber);
		_PrintClient(Client1);


		cout << "\nAre you sure you want to update this client y/n? ";
		char Answer = 'n';
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y') {
			cout << "\n\nUpdate Client Info:";
			cout << "\n____________________\n";
			_ReadClientInfo(Client1);

			clsBankClient::enSaveResults SaveResult;

			SaveResult = Client1.Save();

			switch (SaveResult) {

			case clsBankClient::enSaveResults::svFaildEmptyObject:
				cout << "\nError account was not saved because it's Empty";
				break;

			case clsBankClient::enSaveResults::svSucceeded:
				cout << "\nAccount Updated Successfully :-)\n";
				Client1.Print();
				break;
			}
		}
		else {
			cout << "\n\t\t\t\tThank You :-)\n";
		}
	}
};

