#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"

class clsUpdateCurrencyScreen : protected clsScreen {
private:
	static float _ReadRate() {
		cout << "\nEnter New Rate: ";
		float NewRate = 0;

		NewRate = clsInputValidate::ReadFloatNumber();
		return NewRate;
	}

	static void _PrintCurrency(clsCurrency Currency) {
		cout << "\nCurrency Card: \n";
		cout << "-----------------------------\n";
		cout << "\nCountry    :" << Currency.Country();
		cout << "\nCode       :" << Currency.CurrencyCode();
		cout << "\nName       :" << Currency.CurrencyName();
		cout << "\nRate(1$) = :" << Currency.Rate();
		cout << "\n-----------------------------\n";
	}

public:
	static void ShowUpdateCurrencyScreen() {
		_DrawScreenHeader("\t  Update Currency Screen");
		string CurrencyCode = "";
		cout << "\nPlease Enter Currency Code: ";
		CurrencyCode = clsInputValidate::ReadString();

		while (!clsCurrency::IsCurrencyExist(CurrencyCode)) {
			cout << "\nCurrency is not found, choose another one: ";
			CurrencyCode = clsInputValidate::ReadString();
		}

		clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
		_PrintCurrency(Currency);

		cout << "Are you sure you want to update the rate of this Currency y/n? ";

		char Answer = 'n';
		cin >> Answer;
			
		if (Answer == 'y') {
			cout << "\n\nUpdate Currency Rate: ";
			cout << "\n____________________\n";

			Currency.UpdateRate(_ReadRate());

			cout << "\nCurrency Rate Updated Successfully :-)\n";
			_PrintCurrency(Currency);
		}
	}
};

