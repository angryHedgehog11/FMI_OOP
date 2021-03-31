#pragma once
#include "Challenge.h"

class User
{
public:
	User();
	User(const char* name, unsigned age, const char* email);
	User(const char* name, unsigned age);
	User(const char* name, const char* email);
	User(const char* name);
	User(const User& other);
	User& operator=(const User& other);
	~User();

	void setName(const char* newName);
	const char* getName() const;

	void setAge(unsigned newAge);
	unsigned getAge() const;

	void setEmail(const char* newEmail);
	const char* getEmail() const;

	void setID(unsigned newID); 
	unsigned getID() const; 

	int getChallengeSize() const; 
	void addChallenge(Challenge newCh);
	void finishChallenge(Challenge finishedCh);
	void seeUnfinishedChallenges();

	bool isChallenge(const char* challengeTag) const;
private:
	void clear();
	void copy(const User& otherObject);

	int getChallengeIndex(const char* tag) const;
private:
	char* name;
	unsigned age;
	char* email;
	unsigned ID; 
	int sizeChallenges = 0;
	Challenge* challenges = new Challenge[sizeChallenges];
};