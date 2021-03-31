#include <iostream>
#include <cstring>
#include "Challenge.h"
using std::cerr;
using std::endl;

Challenge::Challenge(const char* tag, const char* status, double rating)
{
	setTag(tag);
	setStatus(status);
	setRating(rating);
}

Challenge::Challenge(const Challenge& other)
{
	copy(other);
	copyThisChallenge(other);
}

Challenge& Challenge::operator=(const Challenge& other)
{
	if (this != &other)
	{
		clear();
		clearRaitings();
		copy(other);
		copyThisChallenge(other);
	}
	return *this;
}

Challenge::~Challenge()
{
	clear();
	clearRaitings();
}

void Challenge::setTag(const char* newTag)
{
	if (newTag != nullptr)
	{
		this->tag = new char[strlen(newTag) + 1];
		strcpy(this->tag, newTag);
	}
	else
	{
		cerr << "The tag was nullptr. Please, try again!" << endl;
	}
}

const char* Challenge::getTag() const
{
	return this->tag;
}

void Challenge::setStatus(const char* newStatus)
{
	if (newStatus != nullptr)
	{
		if (strcmp(newStatus, "new") == 0 || strcmp(newStatus, "quite recently") == 0 || strcmp(newStatus, "old") == 0)
		{
			this->status = new char[strlen(newStatus) + 1];
			strcpy(this->status, newStatus);
		}
		else
		{
			cerr << "Invalid status!" << endl;
			return;
		}
	}
	else
	{
		cerr << "Status was nullptr. Please, try again!";
	}
}

const char* Challenge::getStatus() const
{
	return this->status;
}

void Challenge::setRating(double newRating)
{
	if (newRating >= -5 && newRating <= 10)
	{
		this->rating = newRating;
	}
	else
	{
		cerr << "The rating can not be less than -5 or greater than 10!" << endl;
		return; 
	}
}

double Challenge::getRating() const
{
	return this->rating;
}

void Challenge::changeStatus()
{
	if (thisChallenge.count == 1)
	{
		this->setStatus("new");
	}
	else if (thisChallenge.count >= 2 && thisChallenge.count <= 10)
	{
		this->setStatus("quite recently");
	}
	else if (thisChallenge.count >= 11)
	{
		this->setStatus("old");
	}
}

void Challenge::addRating(double newRaiting)
{
	this->thisChallenge.finished++; 
	int len = this->thisChallenge.finished;
	double* newRaitings = new double[len];
	for (int i = 0; i < (len - 1); i++)
	{
		newRaitings[i] = this->thisChallenge.raitings[i];
	}
	newRaitings[len - 1] = newRaiting;
	delete[] this->thisChallenge.raitings;
	this->thisChallenge.raitings = newRaitings;
}

void Challenge::changeRaiting()
{
	double newRaiting = this->calculateAverage();
	this->setRating(newRaiting);
}

void Challenge::copy(const Challenge& otherObject)
{
	if (otherObject.tag == nullptr)
	{
		this->tag = nullptr;
	}
	else if (otherObject.status == nullptr)
	{
		this->status = nullptr;
	}
	else
	{
		this->tag = new char[strlen(otherObject.tag) + 1];
		strcpy(this->tag, otherObject.tag);
		this->status = new char[strlen(otherObject.status) + 1];
		strcpy(this->status, otherObject.status);
	}
	this->rating = otherObject.rating;
}

void Challenge::copyThisChallenge(const Challenge& other)
{
	this->thisChallenge.count = other.thisChallenge.count;
	this->thisChallenge.finished = other.thisChallenge.finished;
	int raitingsLen = other.thisChallenge.finished;
	this->thisChallenge.raitings = new double[raitingsLen];
	for (int i = 0; i < raitingsLen; i++)
	{
		this->thisChallenge.raitings[i] = other.thisChallenge.raitings[i];
	}
}

void Challenge::clear()
{
	delete[] tag;
	tag = nullptr;
	delete[] status;
	status = nullptr;
}

void Challenge::clearRaitings()
{
	delete[] thisChallenge.raitings;
	thisChallenge.raitings = nullptr;
}

double Challenge::calculateAverage() const
{
	double sum = 0;
	for (int i = 0; i < this->thisChallenge.finished; i++)
	{
		sum = sum + this->thisChallenge.raitings[i];
	}
	double averageResult = sum / this->thisChallenge.finished;
	return averageResult;
}
