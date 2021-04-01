#pragma once
#include <iostream>
#include <string>
#include <fstream>

class User {
public:

private:
	std::string P_username, P_password;
private:
	static bool CheckExist(std::string username);
public:
	User() {}
	User(std::string username, std::string password);
	bool LoadUser();
	void UserOptions();
	void SaveState();
	~User() { SaveState(); }
private:
	void ChangePassword(std::string NewPassword) { P_password = NewPassword; }
	void ChangeUsername(std::string NewUsername) { P_username = NewUsername; }
};

//User method definitions
bool User::CheckExist(std::string username) {
	std::ifstream checkFile("UserData\\" + username + ".txt");
	if (checkFile) {
		return true;
	}
	else {
		return false;
	}
	checkFile.close();
}

User::User(std::string username, std::string password) {
	if (User::CheckExist(username)) {
		std::cout << "Username already exist" << std::endl;
	}
	else {
		P_username = username;
		P_password = password;
		std::cout << "Registration complete" << std::endl;
	}
}

bool User::LoadUser() {
	std::string UnEntered, PwEntered, Un, Pw;

	// Prompts User for Login Information
	std::cout << "Enter username: "; std::cin >> UnEntered;
	std::cout << "Enter password: "; std::cin >> PwEntered;

	std::ifstream RetreievedData("UserData\\" + UnEntered + ".txt");

	// Checks if User has entered valid information
	if (RetreievedData) {
		std::getline(RetreievedData, Un);
		std::getline(RetreievedData, Pw);
		//Updates the current User object's properties to the saved properties
		if (PwEntered == Pw) {
			P_username = Un;
			P_password = Pw;
			RetreievedData.close();
			return true;
		}
		else {
			std::cout << "Password was incorrect" << std::endl;
			return false;
		}
	}
	else {
		std::cout << "Username was not found" << std::endl;
		return false;
	}
}

void User::UserOptions(){
	int choice;
	std::cout << "1: Change your Username\n2: Change password\nYour choice: "; std::cin >> choice;
	switch (choice) {
	case 1: {
		std::string NewUsername;
		std::cout << "Enter new username: "; std::cin >> NewUsername;
		if (User::CheckExist(NewUsername)) {
			std::cout << "[Error] Username already exist" << std::endl;
		}
		else {
			ChangeUsername(NewUsername);
		}
		break;
	}
	case 2: {
		std::string PasswordCheck, NewPassword;
		std::cout << "Enter current password: "; std::cin >> PasswordCheck;
		if (PasswordCheck == P_password) {
			std::cout << "Enter new password: "; std::cin >> NewPassword;
			ChangePassword(NewPassword);
		}
		else {
			std::cout << "Password Incorrect" << std::endl;
		}
		break;
	}
	default:
		std::cout << "Invalid choice" << std::endl;
	// end of switch
	}
}

void User::SaveState() {
	std::ifstream UserInfo("UserData\\" + P_username + ".txt");
	
	if (UserInfo) {		//Executed if the User already has saved data

	}
	else {		//Executed if the User is a new User
		std::ofstream NewUserInfo("UserData\\" + P_username + ".txt");

		// Handling if the file had opened or not
		if (NewUserInfo) {
			NewUserInfo << P_username << std::endl << P_password << std::endl;
			NewUserInfo.close();
			std::cout << "Save Complete" << std::endl;
		}
		else {
			std::cout << "[Error] File could not be opened" << std::endl;
		}
	}

}

// General functions
void LoginHelp() {
	int choice;
	std::cout << "1: Username requirements\n2: Password requirements\nYour choice: "; std::cin >> choice;
	
}
