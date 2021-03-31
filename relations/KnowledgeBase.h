#pragma once
#include "Pair.h"
#include "BinaryRelation.h"
#include <string>
#include <vector>

using std::pair;
using std::cout;
using std::endl;
using std::string;
using std::vector;

template <typename T, typename U>
class KnowledgeBase
{
public:

	KnowledgeBase() = default;

	void addNewRelation(const string& relationName, const BinaryRelation<T, U>& newRelation);
	void addMemberToRealation(const string& name, const Pair<T, U>& newMember);

	bool r(const string& name, const Pair<T, U> checkRelation) const;

	vector<T> operator()(U u) const;
	vector<U> operator[](T t) const;
	
	std::vector<T> dom() const;
	std::vector<U> ran() const;
	bool function() const;
	bool injection() const;


	KnowledgeBase<U, T> operator!() const;

	KnowledgeBase<T, U> operator+(const KnowledgeBase& other);
	KnowledgeBase<T, U> operator^(const KnowledgeBase<T, U>& other);
	KnowledgeBase<T, U>& operator+=(const KnowledgeBase<T, U>& other);
	KnowledgeBase<T, U>& operator^=(const KnowledgeBase& other);
	

private:

	vector<pair<string, BinaryRelation<T, U>>> knowledgeVector;
};

#include "KnowledgeBase.ipp""
