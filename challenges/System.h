#pragma once
#include "User.h"
#include "Challenge.h"
class System
{
public:
	System(const System& other) = delete; 
	System& operator=(const System& other) = delete; 
	~System();

	static System& i();

	void run();

	int getUserIndexByName(const char* name);
	int getUserIndexByID(unsigned ID);

	int getChallengeIndexByTag(const char* tag);
private: 
	void addUser(User newUser);
	void addGivenChallenge(Challenge newChallenge); 

	bool isRegistretedUserByName(const char* userName) const;  
	bool isRegistretedUserByID(unsigned userID) const;
	bool isGivenChallenge(const char* challengeTag) const; 
	
	bool isDigit(char ch);
	

	int countWords(const char* str);
private:

	System();

	int usersSize;
	int challengesSize;
	User* registretedUsers;
	Challenge* givenChallenges;
};

