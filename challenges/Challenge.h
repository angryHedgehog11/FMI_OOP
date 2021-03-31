#pragma once

class Challenge
{
public:

	Challenge(const char* tag = "#unknown", const char* status = "new", double raitin = 0);
	Challenge(const Challenge& other);
	Challenge& operator=(const Challenge& other);
	~Challenge();

	void setTag(const char* newTag);
	const char* getTag() const; 

	void setStatus(const char* newStatus);
	const char* getStatus() const; 

	void setRating(double newRating); 
	double getRating() const; 

	struct ChallengeInfo
	{
		unsigned count = 1;
		unsigned finished = 0;
		double* raitings = new double[finished];
	};

	ChallengeInfo thisChallenge;

	void changeStatus();

	void addRating(double newRaiting);
	void changeRaiting();

private:
	void copy(const Challenge& otherObject);
	void copyThisChallenge(const Challenge& other);

	void clear();
	void clearRaitings();

	double calculateAverage() const;
private:
	char* tag;
	char* status;
	double rating;
};