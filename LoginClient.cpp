#include <iostream>
#include <string>

#include "Src/User.h"

int main()
{
	int choice;
	std::cout << "1: Register\n2: Login\n3: Login support\n\nYour Choice:"; std::cin >> choice;

	switch (choice) {
		case 1: {
			std::string Username, Password;
			std::cout << "Enter a username: "; std::cin >> Username;
			std::cout << "Enter a password: "; std::cin >> Password;
			User NewUser(Username, Password);
			NewUser.~User();
			main();
			break;
		}
		case 2: {
			User account;
			if (account.LoadUser()) {
				std::cout << "Logging in" << std::endl;
				account.UserOptions();
			}
			break;
		}
		case 3:
			LoginHelp();
			break;
		default:
			std::cout << "Invalid choice" << std::endl;
	}
}

