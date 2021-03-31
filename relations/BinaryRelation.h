#pragma once

#include <vector>
#include <iostream>
#include "Pair.h"

using std::string;
using std::vector;
using std::istream;
using std::ostream;

template <typename T, typename U>
class BinaryRelation
{
public:

	BinaryRelation() = default;
	BinaryRelation(const BinaryRelation& other) = default;
	BinaryRelation& operator=(const BinaryRelation& other) = default;

	Pair<T, U> getPair(int index) const;
	int getSize() const;

	void addRelation(const Pair<T, U>& newRelation);

	bool r(T t, U u) const;

	BinaryRelation<U, T> operator!();

	BinaryRelation<T, U> operator+(BinaryRelation<T, U>& otherRelation);
	BinaryRelation<T, U> operator^(BinaryRelation<T, U>& otherRelation);
	BinaryRelation<T, U>& operator+=(BinaryRelation<T, U>& otherRelation);
	BinaryRelation<T, U>& operator^=(BinaryRelation<T, U>& otherRelation);
	BinaryRelation<T, U>& operator*=(BinaryRelation<U, U>& otherRelation);

	vector<U> operator[](const T& element);
	vector<T> operator()(const U& element);
	vector<T> dom();
	vector<U> ran();

	bool function() const;
	bool injection() const;

	template<typename T, typename U>
	friend std::ostream& operator<<(std::ostream& out, const BinaryRelation<T, U>& relation);
	
private:

	bool checkRelation(const Pair<T, U>& pair) const;

private:

	vector<Pair<T, U>> elementsOfRelation;
};

template<typename T, typename U, typename V>
BinaryRelation<T, V> operator*(BinaryRelation<T, U>& lhs, BinaryRelation<U, V>& rhs);

#include "BinaryRelation.ipp"
