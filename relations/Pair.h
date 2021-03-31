#pragma once

template <typename T, typename U>
class Pair
{
public:

	Pair(const T& first, const U& second);
	Pair(const Pair& other) = default;
	Pair& operator=(const Pair& other) = default;

	T getFirst() const;
	void setFirst(const T& newFirst);

	U getSecond() const;
	void setSecond(const U& newSecond);

private:

	T first;
	U second;
};

#include "Pair.ipp"
