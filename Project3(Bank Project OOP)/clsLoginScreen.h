#pragma once
#include "clsUser.h"
#include <iomanip>
#include "clsMainScreen.h"
#include "Global.h"
#include "clsScreen.h"
#include <iostream>

class clsLoginScreen : protected clsScreen {
private:
	static bool _Login() {
		bool LoginFaild = false;

		string Username, Password;
		int FailedLoginCounter = 0;
		do {
			
			if (LoginFaild) {
				cout << "\nInvalid Username/Password!\n";
				FailedLoginCounter++;
				cout << "You have " << (3 - FailedLoginCounter) << " Trial(s) to login.\n\n";
			}

			if (FailedLoginCounter == 3) {
				cout << "You are Locked after 3 faild trails \n";
				return false;
			}

			cout << "Enter Username: ";
			cin >> Username;

			cout << "Enter Password: ";
			cin >> Password;

			CurrentUser = clsUser::Find(Username, Password);

			LoginFaild = CurrentUser.IsEmpty();
		} while (LoginFaild);

		CurrentUser.RegisterLogIn();
		clsMainScreen::ShowMainMenue();
		return true;
	}

public:
	static bool ShowLoginScreen() {
		system("cls");
		_DrawScreenHeader("\t  Login Screen");
		return _Login();
	}
};

