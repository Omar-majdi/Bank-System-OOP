#include <iostream>
#include "clsLoginScreen.h"

int main() {
	//clsMainScreen::ShowMainMenue();
	
	while (true) {
		//the Show Login screen will return false after 3 faild logins so we will break the loop
		if (!clsLoginScreen::ShowLoginScreen()) 
			break;
	}
}
