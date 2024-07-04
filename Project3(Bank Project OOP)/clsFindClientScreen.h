#pragma once
#include <iostream>
#include <iomanip>
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsUtil.h"
#include "clsScreen.h"
#include "clsClientListScreen.h"


class clsFindClientScreen : protected clsScreen {

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

public:
	static void ShowFindClientScreen() {
		if (!CheckAccessRights(clsUser::enPermissions::pFindClient)) return;
		_DrawScreenHeader("\tFind Client Screen");

		string AccountNumber;
		cout << "\nPlease Enter Account Number: ";
		AccountNumber = clsInputValidate::ReadString();

		while (!clsBankClient::IsClientExist(AccountNumber)) {
			cout << "\nAccount Number Is Not Found, Choose another one: ";
			AccountNumber = clsInputValidate::ReadString();
		}

		clsBankClient Client1 = clsBankClient::Find(AccountNumber);

		if (!Client1.IsEmpty()) {
			cout << "\nClient Found :-)\n";
			_PrintClient(Client1);
		}
		else {
			cout << "\nClient Was not Found :-(\n";
		}
	}
};

