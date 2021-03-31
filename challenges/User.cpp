#include <iostream>
#include "cstring"
#include "User.h"

using std::cout;
using std::cerr; 
using std::endl;

User::User()
{
	const char* name = "Unknown";
	setName(name);
	age = 0;
	const char* email = "Unknown";
	setEmail(email);
	ID = 0;
}

User::User(const char* name, unsigned age, const char* email)
{
	setName(name);
	setAge(age);
	setEmail(email);
}

User::User(const char* name, const char* email)
{
	setName(name);
	setEmail(email);
	setAge(0);
}

User::User(const char* name, unsigned age)
{
	setName(name);
	setAge(age);
	setEmail("Unknown");
}

User::User(const char* name)
{
	setName(name);
	setAge(0);
	setEmail("Unknown");
}

User::User(const User& other)
{
	copy(other);
}

User& User::operator=(const User& other)
{
	if (this != &other)
	{
		clear();
		copy(other);
	}
	return *this; 
}

User::~User()
{
	clear();
}

void User::setName(const char* newName)
{
	if (newName != nullptr)
	{
		this->name = new char[strlen(newName) + 1];
		strcpy(this->name, newName);
	}
	else
	{
		cerr << "The given name was nullptr. Please, try again!" << endl;
		return; 
	}
}

const char* User::getName() const
{
	return this->name;
}

void User::setAge(unsigned newAge)
{
	if (newAge <= 90)
	{
		this->age = newAge;
	}
	else
	{
		cerr << "The given age must be less than 90!" << endl;
		return; 
	}
}

unsigned User::getAge() const
{
	return this->age;
}

void User::setEmail(const char* newEmail)
{
	if (newEmail != nullptr)
	{
		this->email = new char[strlen(newEmail) + 1];
		strcpy(this->email, newEmail);
	}
	else
	{
		cerr << "The given email was nullptr. Please, try again!" << endl;
		return;
	}
}

const char* User::getEmail() const
{
	return this->email;
}

void User::setID(unsigned newID) 
{
	if (newID == 0)
	{
		cerr << "The ID must be greater than 0." << endl;

	}
	else
	{
		this->ID = newID;
	}
	
}

unsigned User::getID() const
{
	return this->ID;
}

int User::getChallengeSize() const
{
	return this->sizeChallenges;
}

void User::addChallenge(Challenge newCh)
{
	this->sizeChallenges++;
	int size = this->sizeChallenges;
	Challenge* newChallenges = new Challenge[size];
	for (int i = 0; i < (size - 1); i++)
	{
		newChallenges[i] = this->challenges[i];
	}
	newChallenges[size - 1] = newCh;
	delete[] this->challenges;
	this->challenges = newChallenges;
}

void User::finishChallenge(Challenge finishedCh)
{
	int index = getChallengeIndex(finishedCh.getTag());
	for (int i = index; i < this->sizeChallenges - 1; i++)
	{
		challenges[i] = challenges[i + 1];
	}
	this->sizeChallenges--;
	int size = this->sizeChallenges;
	Challenge* newChallenges = new Challenge[size];
	for (int i = 0; i < size; i++)
	{
		newChallenges[i] = this->challenges[i];
	}
	delete[] this->challenges;
	this->challenges = newChallenges;
}

void User::seeUnfinishedChallenges()
{
	for (int i = 0; i < this->sizeChallenges; i++)
	{
		cout << this->challenges[i].getTag() << " ";
	}
}

bool User::isChallenge(const char* challengeTag) const
{
	int count = 0;
	for (int i = 0; i < sizeChallenges; i++)
	{
		if (strcmp(challengeTag, this->challenges[i].getTag()) == 0)
		{
			count++;
		}
	}
	if (count > 0)
	{
		return true; 
	}
	else
	{
		return false; 
	}
}

int User::getChallengeIndex(const char* tag) const
{
	int index = 0;
	for (int i = 0; i < this->sizeChallenges; i++)
	{
		if (strcmp(this->challenges[i].getTag(), tag) == 0)
		{
			index = i;
		}
	}
	return index;
}

void User::clear()
{
	delete[] name;
	name = nullptr;
	delete[] email; 
	email = nullptr;
	this->challenges;
	challenges = nullptr;
}

void User::copy(const User& otherObject)
{
	if (otherObject.name == nullptr)
	{
		this->name = nullptr;
	}
	else if (otherObject.email == nullptr)
	{
		this->email = nullptr;
	}
	else
	{
		this->name = new char[strlen(otherObject.name) + 1];
		strcpy(this->name, otherObject.name);
		this->email = new char[strlen(otherObject.email) + 1];
		strcpy(this->email, otherObject.email);
	}
	this->age = otherObject.age; 
	this->sizeChallenges = otherObject.sizeChallenges;
	this->challenges = otherObject.challenges;
}
