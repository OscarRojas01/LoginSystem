#include <iostream>
#include <string>

#include "Src/User.h"

int main()
{
	int choice;
	std::cout << "0: Exit\n1: Register\n2: Login\n3: Login support\n\nYour Choice:"; std::cin >> choice;

	switch (choice) {
		case 0:
			return 0;
			break;
		case 1: {
			std::string Username, Password;
			std::cout << "Enter a username: "; std::cin >> Username;
			std::cout << "Enter a password: "; std::cin >> Password;
			User* NewUser = new User(Username, Password);
			NewUser->~User();
			break;
		}
		case 2: {
			User* account = new User();
			if (account->LoadUser()) {
				std::cout << "Logging in" << std::endl;
				account->UserOptions();
			}
			break;
		}
		case 3:
			LoginHelp();
			break;
		default:
			std::cout << "Invalid choice" << std::endl;
	}
	main();
}

