#include <iostream>
#include <cstring>
#include "System.h"

using std::cin;
using std::cout; 
using std::cerr;
using std::endl;

const int MAX_COMMAND_LEN = 13; //най-дългите команди са profile_info и registration 
const int MAX_EMAIL_LEN = 100;
const int MAX_AGE_LEN = 3; //човек не може да е по-възрастен от 90 
const int MAX_TAG_LEN = 31; 
const long  MAX = 10000;

void System::addUser(User newUser)
{
	usersSize++; 
	User* newRegistretedUsers = new User[usersSize]; 
	for (int i = 0; i < (usersSize - 1); i++)
	{
		newRegistretedUsers[i] = registretedUsers[i];
	}
	newRegistretedUsers[usersSize - 1] = newUser; 
	delete[] registretedUsers; 
	registretedUsers = newRegistretedUsers; 
}

void System::addGivenChallenge(Challenge newChallenge)
{
	challengesSize++;
	Challenge* newGivenChallenges = new Challenge[challengesSize];
	for (int i = 0; i < (challengesSize - 1); i++)
	{
		newGivenChallenges[i] = givenChallenges[i];
	}
	newGivenChallenges[challengesSize - 1] = newChallenge;
	delete[] givenChallenges;
	givenChallenges = newGivenChallenges;
}

bool System::isRegistretedUserByName(const char* userName) const
{
	int count = 0;
	for (int i = 0; i < usersSize; i++)
	{
		if (strcmp(registretedUsers[i].getName(), userName) == 0)
		{
			count++;
		}
	}
	if(count > 0)
	{
		return true; 
	}
	else
	{
		return false;
	}
}

bool System::isRegistretedUserByID(unsigned userID) const
{
	if (userID >= 1 && userID <= usersSize)
	{
		return true;
	}
	else
	{
		return false; 
	}
}

bool System::isGivenChallenge(const char* challengeTag) const
{
	int count = 0; 
	for (int i = 0; i < challengesSize; i++)
	{
		if (strcmp(challengeTag, givenChallenges[i].getTag()) == 0)
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

bool System::isDigit(char ch)
{
	if (ch == '0' || ch == '1' || ch == '2' || ch == '3' || ch == '4' ||
		ch == '5' || ch == '6' || ch == '7' || ch == '8' || ch == '9')
	{
		return true;
	}
	else
	{
		return false;
	}	
}

int System::countWords(const char* str)
{
	int words = 0;

	while (*str)
	{
		if (*str == ' ')
		{
			words++;
		}
		str++;
	}
	int strLen = strlen(str);
	if (str[0] == ' ' || str[strLen - 1] == ' ')
	{
		return words - 1;
	}
	else
	{
		return words;
	}
}

System::System()
{
	usersSize = 0; 
	challengesSize = 0;
	registretedUsers = new User[usersSize];
	givenChallenges = new Challenge[challengesSize];
}

System::~System()
{
	delete[] registretedUsers;
	//registretedUsers = nullptr;
	delete[] givenChallenges;
	//givenChallenges = nullptr;
}

System& System::i()
{
	static System system;
	return system;
}

void System::run()
{	
		char command[MAX_COMMAND_LEN];
		cin >> command;
		while (strcmp(command, "exit") != 0)
		{ 
			if (strcmp(command, "registration") == 0)
				{
					char arguments[MAX];
					cin.getline(arguments, MAX);
					int numberOfArguments = countWords(arguments);
					cout << numberOfArguments << endl;
					if (numberOfArguments == 1)
					{
						char name[MAX];
						strcpy(name, arguments);
						User newUser(name); 
						addUser(newUser);
						registretedUsers[getUserIndexByName(newUser.getName())].setID(usersSize);
						cout << "Registration Successful." << endl;
					}
					else if (numberOfArguments == 2)
					{
						char name[MAX]; 
						char secondArg[MAX_EMAIL_LEN];
						strcpy(name, strtok(arguments, " "));
						strcpy(secondArg, strtok(nullptr, " "));
						if (isDigit(secondArg[0]))
						{
							if (atoi(secondArg) > 90)
							{
								cout << "Registration Fail. You are toо old for this App." << endl; 
							}
							else
							{
								User newUser(name, atoi(secondArg));
								addUser(newUser); 
								registretedUsers[getUserIndexByName(newUser.getName())].setID(usersSize);
								cout << "Registration Successful." << endl;
							}
						}
						else
						{
							User newUser(name, secondArg); 
							addUser(newUser);
							registretedUsers[getUserIndexByName(newUser.getName())].setID(usersSize);
							cout << "Registration Successful. Please check your email." << endl; 
						}
					}
					else if (numberOfArguments == 3)
					{
						char name[MAX];
						char ageStr[MAX_AGE_LEN];
						char email[MAX_EMAIL_LEN];
						strcpy(name, strtok(arguments, " "));
						strcpy(ageStr, strtok(nullptr, " "));
						strcpy(email, strtok(nullptr, " "));
						if (atoi(ageStr) > 90)
						{
							cout << "Registration Fail. You are toо old for this App." << endl;
						}
						else
						{
							User newUser(name, atoi(ageStr), email);
							addUser(newUser);
							registretedUsers[getUserIndexByName(newUser.getName())].setID(usersSize);
							cout << "Registration Successful.Please check your email." << endl;
						}
					} 
				} 
			else if (strcmp(command, "challenge") == 0)
			{
				char name[MAX];
				char tag[MAX_TAG_LEN];
				char name2[MAX]; 
				cin >> name >> tag >> name2;
				if (tag[0] != '#')
				{
					cout << "Invalid challenge tag!" << endl;
				}
				if (!isRegistretedUserByName(name) || !isRegistretedUserByName(name2))
				{
					cout << "Sorry, some of the users may not be registered!" << endl;
				}
				else if (!isGivenChallenge(tag))
				{
					Challenge newChallenge(tag);
					addGivenChallenge(newChallenge);
					registretedUsers[getUserIndexByName(name2)].addChallenge(givenChallenges[getChallengeIndexByTag(tag)]);
					cout << name << " successfully challenged!" << endl;
				}
				else
				{
					givenChallenges[getChallengeIndexByTag(tag)].thisChallenge.count++;
					if (givenChallenges[getChallengeIndexByTag(tag)].thisChallenge.count < 12)
					{
						givenChallenges[getChallengeIndexByTag(tag)].changeStatus();
					}
					registretedUsers[getUserIndexByName(name2)].addChallenge(givenChallenges[getChallengeIndexByTag(tag)]);
					cout << name << " successfully challenged!" << endl;
				}
			} 
			else if (strcmp(command, "finish") == 0)
			{
				char challengeTAG[MAX_TAG_LEN];
				unsigned userID;
				double raiting;
				cin >> challengeTAG >> userID >> raiting;
				if (!isRegistretedUserByID(userID))
				{
					cerr << "The given id is not valid.The user with this id does not exist." << endl;
				}
				else if (!registretedUsers[getUserIndexByID(userID)].isChallenge(challengeTAG))
				{
					cout << "This user didn't have such challenge!" << endl;
				}
				else if (raiting < -5 || raiting > 10)
				{
					cout << "Sorry. Invalid rating! The challenge is not completed, yet." << endl;
				}
				else
				{
					givenChallenges[getChallengeIndexByTag(challengeTAG)].addRating(raiting);
					registretedUsers[getUserIndexByID(userID)].finishChallenge(givenChallenges[getChallengeIndexByTag(challengeTAG)]);
					cout << "Well done! May the challenge be with you!" << endl;
				}
			}
			else if (strcmp(command, "profile_info") == 0)
			{
				char name[MAX];
				cin >> name;
				if (!isRegistretedUserByName(name))
				{
					cout << "Nothing come out! User with this name do not exist!" << endl;
				}
				else
				{
					int count = 0;
					for (int i = 0; i < usersSize; i++)
					{
						if (strcmp(name, registretedUsers[i].getName()) == 0)
						{
							count++;
							cout << count << ")" << "\t" << "Name: " << registretedUsers[i].getName() << endl;
							cout << "\t" << "Age: ";
							if (registretedUsers[i].getAge() == 0)
							{
								cout << "Unknown" << endl;
							}
							else
							{
								cout << registretedUsers[i].getAge() << endl;
							}
							cout << "\t" << "Email: " << registretedUsers[i].getEmail() << endl;
							cout << "\t" << "Id: " << i+1 << endl;
						}
					}
				}
			}
			else if (strcmp(command, "list_by") == 0)
			{
				const int MAX_LEN_LIST_BY = 6;
				char list_by[MAX_LEN_LIST_BY];
				cin >> list_by;
				if (strcmp(list_by, "newest") == 0)
				{
					for (int i = challengesSize - 1; i >= 0; i--)
					{
						cout << givenChallenges[i].getTag() << endl;
					}
				}
				else if (strcmp(list_by, "oldest") == 0)
				{
					for (int i = 0; i < challengesSize; i++)
					{
						cout << givenChallenges[i].getTag() << endl;
					}
				}
				else if (strcmp(list_by, "most_popular") == 0)
				{
					//selection sort за givenChallenges[i].thisChallenge.count;
				}
				else
				{
					cout << "Invalid method for listing challenges!" << endl;
				}
			}
			else
			{
				cout << "Not such command available" << endl;
		    } 
		cin >> command; 
		}
}

int System::getUserIndexByName(const char* name)
{
	int index = 0;
	for (int i = 0; i < usersSize; i++)
	{
		if (strcmp(name, registretedUsers[i].getName()) == 0)
		{
			index = i;
		}
	}
	return index;
}

int System::getUserIndexByID(unsigned ID)
{
	return (ID - 1);
}

int System::getChallengeIndexByTag(const char* tag)
{
	int index = 0; 
	for (int i = 0; i < challengesSize; i++)
	{
		if (strcmp(tag, givenChallenges[i].getTag()) == 0)
		{
			index = i;
		}
	}
	return index; 
}
