#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsCurrenciesListScreen.h"
#include "clsFindCurrencyScreen.h"
#include "clsUpdateCurrencyScreen.h"
#include "clsCurrencyCalculatorScreen.h"

class clsCurrencyExchangeMainScreen : protected clsScreen {
private:
	enum enCurrenciesMainMenueOptions {
		eListCurrencies = 1, eFindCurrency = 2, eUpdateCurrenyRate = 3,
		eCurrencyCalculator = 4, eMainMenue = 5
	};

	static short ReadCurrenciesMainMenueOptions() {
		cout << setw(37) << left << "" << "Choosewhat do you want to do [1 - 5]: ";
		short Choice = clsInputValidate::ReadShortNumberBetween(1, 5);
		return Choice;
	}

    static void _GoBackToCurrenciesMenue() {
        cout << "\n\nPress any key to go back to Currencies Menue...";
        system("pause>0");
        ShowCurrenciesMenue();
    }

    static void _ShowCurrenciesListScreen() {
        clsCurrenciesListScreen::ShowCurrenciesListScreen();
    }

    static void _ShowFindCurrencyScreen() {
        clsFindCurrencyScreen::ShowFindCurrencyScreen();
    }

    static void _ShowUpdateCurrencyRateScreen() {
        clsUpdateCurrencyScreen::ShowUpdateCurrencyScreen();
    }

    static void _ShowCurrencyCalculatorScreen() {
        clsCurrencyCalculatorScreen::ShowCurrencyCalculatorScreen();
    }

    static void _PerformCurrenciesMainMenueOptions(enCurrenciesMainMenueOptions CurrenciesMainMenueOptions) {

        switch (CurrenciesMainMenueOptions) {
        case enCurrenciesMainMenueOptions::eListCurrencies: {
            system("cls");
            _ShowCurrenciesListScreen();
            _GoBackToCurrenciesMenue();
            break;
        }

        case enCurrenciesMainMenueOptions::eFindCurrency: {
            system("cls");
            _ShowFindCurrencyScreen();
            _GoBackToCurrenciesMenue();
            break;
        }

        case enCurrenciesMainMenueOptions::eUpdateCurrenyRate:  {
            system("cls");
            _ShowUpdateCurrencyRateScreen();
            _GoBackToCurrenciesMenue();
            break;
        }

        case enCurrenciesMainMenueOptions::eCurrencyCalculator: {
            system("cls");
            _ShowCurrencyCalculatorScreen();
            _GoBackToCurrenciesMenue();
            break;
        }

        case enCurrenciesMainMenueOptions::eMainMenue: {
            //do nothing here the main screen will handle it :-) ;
        }
        }
    }

public:

    static void ShowCurrenciesMenue() {
        system("cls");
        _DrawScreenHeader("    Currancy Exhange Main Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t  Currency Exhange Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] List Currencies.\n";
        cout << setw(37) << left << "" << "\t[2] Find Currency.\n";
        cout << setw(37) << left << "" << "\t[3] Update Rate.\n";
        cout << setw(37) << left << "" << "\t[4] Currency Calculator.\n";
        cout << setw(37) << left << "" << "\t[5] Main Menue.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _PerformCurrenciesMainMenueOptions((enCurrenciesMainMenueOptions)ReadCurrenciesMainMenueOptions());
    }

};

