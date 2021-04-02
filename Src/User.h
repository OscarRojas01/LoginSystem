#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>

class User {
public:
	int age=0, height=0;
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
	void SaveState(std::string NewUsername);
	~User() { 
		SaveState();
		std::cout << P_username << " has been destroyed" << std::endl;
	}
private:
	void ChangePassword(std::string NewPassword) { P_password = NewPassword; SaveState(); }
	void ChangeUsername(std::string NewUsername) { SaveState(NewUsername); P_username = NewUsername; }
};

//User method definitions
bool User::CheckExist(std::string username) {
	std::ifstream checkFile("UserData\\" + username + ".txt");
	if (checkFile) {
		checkFile.close();
		return true;
	}
	else {
		checkFile.close();
		return false;
	}
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
	int age, height;

	// Prompts User for Login Information
	std::cout << "Enter username: "; std::cin >> UnEntered;
	std::cout << "Enter password: "; std::cin >> PwEntered;

	std::ifstream RetreievedData("UserData\\" + UnEntered + ".txt");

	// Checks if User has entered valid information
	if (RetreievedData) {
		std::getline(RetreievedData, Un);
		std::getline(RetreievedData, Pw);
		RetreievedData >> age;
		RetreievedData >> height;
		//Updates the current User object's properties to the saved properties
		if (PwEntered == Pw) {
			P_username = Un;
			P_password = Pw;
			this->age = age;
			this->height = height;
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
	std::cout << "0: Log out\n1: Change Username\n2: Change password\n3: Update info\n\nYour choice: "; std::cin >> choice;
	switch (choice) {
	case 0:
		std::cout << "Logging out" << std::endl;
		return;
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
	case 3:
		std::cout << "0: Return to account home\n1: Set age\n 2: Set height (in inches)\n\nYour choice: "; std::cin >> choice;
		switch (choice) {
		case 0:
			return;
			break;
		case 1:
			std::cout << "Enter your age: "; std::cin >> age;
			SaveState();
			break;
		case 2:
			std::cout << "Enter your height in inches: "; std::cin >> height;
			SaveState();
			break;
		default:
			std::cout << "Not a valid choice" << std::endl;
		}
		break;
	default:
		std::cout << "Invalid choice" << std::endl;
	// end of switch
	}
	UserOptions();
}

void User::SaveState() {
	std::ifstream UserInfo("UserData\\" + P_username + ".txt");
	
	if (UserInfo) {		//Executed if the User already has saved data
		UserInfo.close();
		std::ofstream updateInfo("UserData\\" + P_username + ".txt");
		updateInfo << P_username << std::endl << P_password << std::endl << age << std::endl << height << std::endl;
		std::cout << "Save complete" << std::endl;
	}
	else {		//Executed if the User is a new User
		std::ofstream NewUserInfo("UserData\\" + P_username + ".txt");

		// Handling if the file had opened or not
		if (NewUserInfo) {
			NewUserInfo << P_username << std::endl << P_password << std::endl << age << std::endl << height << std::endl;
			NewUserInfo.close();
			std::cout << "Save Complete" << std::endl;
		}
		else {
			std::cout << "[Error] New save file could not be opened" << std::endl;
		}
	}

}

void User::SaveState(std::string NewUsername) {
	std::ifstream UserInfo("UserData\\" + P_username + ".txt");

	if (UserInfo) {		//Executed if the User's file exist and was opened
		UserInfo.close();
		//creating string representations of the file paths in order to convert to char for use in rename method
		std::string oldFileStr("UserData\\" + P_username + ".txt");
		std::string newFileStr("UserData\\" + NewUsername + ".txt");
		char* oldFileChar = &oldFileStr[0];
		char* newFileChar = &newFileStr[0];
		int result = std::rename(oldFileChar, newFileChar);
		if (!result) {
			std::ofstream updateInfo(newFileStr);
			updateInfo << NewUsername << std::endl << P_password << std::endl << age << std::endl << height << std::endl;
			std::cout << "Username successfully changed" << std::endl;
		}
		else {
			std::cout << "[Error] Could not update file name" << std::endl;
		}

	}
	else {
		std::cout << "[Error] Could not open user info" << std::endl;
	}
}

// General functions
void LoginHelp() {
	int choice;
	std::cout << "1: Username requirements\n2: Password requirements\nYour choice: "; std::cin >> choice;
	
}
