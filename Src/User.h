#pragma once

class User {
public:
	int age=0, height=0;
protected:
	std::string P_username, P_password;
protected:
	static bool CheckExist(const std::string& username);
public:
	User() {}
	User(const std::string& username, const std::string& password);
	bool LoadUser();
	void UserOptions();
	bool EditInfo();
	void SaveState();
	void SaveState(const std::string& NewUsername);
	~User() { 
		SaveState();
		std::cout << P_username << " has been destroyed" << std::endl;
	}
protected:
	void ChangePassword(std::string NewPassword) { P_password = NewPassword; SaveState(); }
	void ChangeUsername(std::string NewUsername) { SaveState(NewUsername); P_username = NewUsername; }
};


